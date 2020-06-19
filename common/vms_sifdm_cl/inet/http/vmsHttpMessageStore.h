#pragma once
#include "vmsHttpProtocol.h"

class vmsHttpMessageStoreBase
{
public:
	enum State
	{
		NeedMoreData,
		ParsingError,
		Completed
	};
	State getState () const {return m_enState;}

	// append data to the store
	// piLen - in/out - length of buffer provided, out - amount of data used
	virtual bool AppendData (LPBYTE pbData, int *piLen) = NULL;

	// do the all parsing etc. except real storing the content, if true
	// must not be changed after appending any data
	virtual void setDontStoreContent (bool b) {m_bDontStoreContent = b;}

	vmsHttpMessageStoreBase () : m_enState (NeedMoreData), m_bDontStoreContent (false) {}
	virtual ~vmsHttpMessageStoreBase () {}

protected:
	State m_enState;
	bool m_bDontStoreContent;
};

class vmsHttpMessageHeaderStore : public vmsHttpMessageStoreBase
{
public:
	const std::string& getHeader () const {return m_strHeader;}

	// returns false in case of parsing error
	bool AppendData (LPBYTE pbData, int *piLen)
	{
		assert (m_enState == NeedMoreData);
		if (m_enState != NeedMoreData)
			return false;
		if (!*piLen)
			return true;
		std::string str; 
		str.append ((char*)pbData, *piLen);
		LPCSTR psz = strstr (str.c_str (), "\r\n\r\n");
		if (psz)
		{
			int len = psz - str.c_str () + 4;
			m_strHeader.append (str.c_str (), len);
			m_enState = Completed;
			// amount used
			*piLen = len;
		}
		else
		{
			if (str.length () != strlen (str.c_str ())) // not a string buffer?
			{
				m_enState = ParsingError;
				return false;
			}
			m_strHeader += str;
		}
		return true;
	}

protected:
	std::string m_strHeader;
};

class vmsHttpMessageBodyStore : public vmsHttpMessageStoreBase
{
public:
	// rfc2068, 4.4
	enum BodyLengthDetectionAlgorithm
	{
		LA_Unknown,
		// 1xx, 204, and 304 responses and any response to a HEAD request
		// does not have a response body
		LA_NoBody,
		// Transfer-Encoding header field is present and
		// indicates that the "chunked" transfer coding has been applied
		// the length is defined by the chunked encoding
		LA_Chunked,
		// Content-Length header field is present. Its
		// value in bytes represents the length of the message-body
		LA_ContentLength,
		// the message uses the media type "multipart/byteranges"
		// that defines the length (Content-Range header field).
		LA_ContentRange,
		// the length is determined by the server closing the connection
		LA_ConnectionClosure,
	};
	BodyLengthDetectionAlgorithm getBodyLengthDetectionAlgorithm () const {return m_enLA;}
protected:
	BodyLengthDetectionAlgorithm m_enLA;
public:
	bool AppendData (LPBYTE pbData, int *piLen)
	{
		assert (m_enState == NeedMoreData);

		if (m_enLA == LA_Unknown)
		{
			if (!DetermineBodyLengthDetectionAlgorithm ())
			{
				m_enState = ParsingError;
				return false;
			}
		}

		assert (m_enLA != LA_Unknown);

		if (m_enLA == LA_NoBody || 
				((m_enLA == LA_ContentLength || m_enLA == LA_ContentRange) && m_uContentLength == 0))
		{
			m_enState = Completed;
			*piLen = 0;
			return true;
		}

		if (!*piLen)
			return true;

		switch (m_enLA)
		{
		case LA_Chunked:
			return AppendData_Chunked (pbData, piLen);

		case LA_ContentLength:
		case LA_ContentRange:
			return AppendData_ContentLength (pbData, piLen);

		case LA_ConnectionClosure:
			return AppendDataToBody (pbData, *piLen);

		default:
			assert (false);
			return false;
		}
	}

protected:
	UINT64 m_nNotCompletedChunkSizeLeftToPass; // used by AppendData_Chunked function
	std::vector <BYTE> m_vbDataFromPrevAppendDataCall; // sometimes we can't process data without more data; so we store data here and wait the recent data
	bool AppendData_Chunked (LPBYTE pbData, int *piLen)
	{
		int iLenAvail = *piLen;

		if (m_nNotCompletedChunkSizeLeftToPass)
		{
			assert (m_vbDataFromPrevAppendDataCall.empty ());
			int iLen = iLenAvail;
			if (iLen > m_nNotCompletedChunkSizeLeftToPass)
				iLen = (int)m_nNotCompletedChunkSizeLeftToPass;
			if (!AppendDataToBody (pbData, iLen))
				return false;
			m_nNotCompletedChunkSizeLeftToPass -= iLen;
			if (m_nNotCompletedChunkSizeLeftToPass)
				return true;
			pbData += iLen;
			iLenAvail -= iLen;
		}

		if (!m_vbDataFromPrevAppendDataCall.empty ())
		{
			m_vbDataFromPrevAppendDataCall.resize (m_vbDataFromPrevAppendDataCall.size () + iLenAvail);
			CopyMemory (&m_vbDataFromPrevAppendDataCall [m_vbDataFromPrevAppendDataCall.size () - iLenAvail], pbData, iLenAvail);
			pbData = &m_vbDataFromPrevAppendDataCall [0];
			iLenAvail = m_vbDataFromPrevAppendDataCall.size ();
		}

		// buff points exactly to start position of a chunk

		vmsHttpBuffer buff (m_vbDataFromPrevAppendDataCall.empty () ? pbData : &m_vbDataFromPrevAppendDataCall [0], 
			m_vbDataFromPrevAppendDataCall.empty () ? iLenAvail : m_vbDataFromPrevAppendDataCall.size ());
		vmsHttpChunkedTransferEncoding cte;
		bool bParsedCompletely = false;

		try 
		{
			cte.Read (buff);
			bParsedCompletely = true;
		}
		catch (...) 
		{
			assert (buff.getThrowReason () != buff.ParseError);
			if (buff.getThrowReason () == buff.ParseError)
			{
				m_enState = ParsingError;
				return false;
			}
		}

		// process all completely received chunks

		for (size_t i = 0; i < cte.getChunkCount (); i++)
		{
			const vmsHttpChunkedTransferEncoding::Chunk* p = cte.getChunk (i);
			size_t nChunkTotalLen = p->pbData - pbData + (size_t)p->uSize + 2; // 2 - each chunk ends with CRLF
			if (!AppendDataToBody (pbData, nChunkTotalLen))
				return false;
			pbData += nChunkTotalLen;
			iLenAvail -= nChunkTotalLen;
		}

		// now pbData points to the end of last completely processed chunk

		// check if there is not completely processed chunk

		if (cte.getLastNotCompletelyProcessedChunk ().pbData)
		{
			assert (!bParsedCompletely);
			assert (cte.getLastNotCompletelyProcessedChunk ().uSize);
			size_t nChunkTotalLen = cte.getLastNotCompletelyProcessedChunk ().pbData - pbData + (size_t)cte.getLastNotCompletelyProcessedChunk ().uSize + 2; // 2 - each chunk ends with CRLF
			assert (nChunkTotalLen > (size_t)iLenAvail);
			if (!AppendDataToBody (pbData, iLenAvail))
				return false;
			m_nNotCompletedChunkSizeLeftToPass = nChunkTotalLen - iLenAvail;
			iLenAvail = 0;
			m_vbDataFromPrevAppendDataCall.clear ();
		}
		else if (!bParsedCompletely)
		{
			if (iLenAvail)
			{
				// we need more data to process this chunk
				if (m_vbDataFromPrevAppendDataCall.empty ())
				{
					// first buffer initialization
					m_vbDataFromPrevAppendDataCall.resize (iLenAvail);
					CopyMemory (&m_vbDataFromPrevAppendDataCall [0], pbData, iLenAvail);
					iLenAvail = 0;
				}
			}
		}

		if (bParsedCompletely)
		{
			// iLenAvailDelta is amount of data we did not write to the body from pbData
			int iLenAvailDelta = iLenAvail - (int)buff.getSizeAvail ();
			if (!AppendDataToBody (pbData, iLenAvailDelta))
				return false;
			iLenAvail = buff.getSizeAvail ();
			m_vbDataFromPrevAppendDataCall.clear ();
			m_enState = Completed;
		}

		assert (*piLen >= iLenAvail);
		if (*piLen >= iLenAvail)
		{
			*piLen -= iLenAvail;
		}
		else
		{
			m_enState = ParsingError;
			return false;
		}
		
		return true;
	}
	bool AppendData_ContentLength (LPBYTE pbData, int *piLen)
	{
		int iLen = *piLen;
		if (iLen)
		{
			if (m_uContentLength - getBodySize () < iLen)
				iLen = (int)(m_uContentLength - getBodySize ());
			if (!AppendDataToBody (pbData, iLen))
				return false;
			*piLen = iLen;
		}
		if (m_uContentLength == getBodySize ())
			m_enState = Completed;
		return true;
	}
	bool AppendDataToBody (const LPBYTE pbData, int iLen)
	{
		assert (iLen != 0);
		if (!iLen)
			return true;
		if (!m_bDontStoreContent)
		{
			try {
				m_vbBody.resize (m_vbBody.size () + iLen);
			}catch (...) {return false;} // memory error
			CopyMemory (&m_vbBody [m_vbBody.size () - iLen], pbData, iLen);
		}
		else
		{
			m_uBodySize += iLen;
		}
		return true;
	}
	bool DetermineBodyLengthDetectionAlgorithm ()
	{
		if (m_pRequestMsgHdr)
		{
			vmsHttpRequestParser req (m_pRequestMsgHdr->getHeader ().c_str ());
			if (!_stricmp ("HEAD", req.getMethod ().c_str ()))
			{
				m_enLA = LA_NoBody;
				return true;
			}

			vmsHttpResponseParser resp (m_pHdr->getHeader ().c_str ());
			if ((int)(resp.getStatusCode () / 100) == 1 || resp.getStatusCode () == 204 || resp.getStatusCode () == 304)
			{
				m_enLA = LA_NoBody;
				return true;
			}
		}

		vmsHttpResponseParser resp;
		vmsHttpRequestParser req;
		vmsHttpHeaderParser *phdr = m_pRequestMsgHdr ? (vmsHttpHeaderParser*)&resp : (vmsHttpHeaderParser*)&req;

		if (!phdr->ReadHeader (m_pHdr->getHeader ().c_str ()))
			return false;

		const vmsHttpGenericHeaderField *pcl = phdr->FieldByName ("Transfer-Encoding");
		if (pcl && !_stricmp (pcl->getValueWoExtraSpaces ().c_str (), "chunked"))
		{
			m_enLA = LA_Chunked;
			return true;
		}

		pcl = phdr->FieldByName ("Content-Length");
		if (pcl)
		{
			m_enLA = LA_ContentLength;
			m_uContentLength = _atoi64 (pcl->getValueWoExtraSpaces ().c_str ());
			return true;
		}

		pcl = phdr->FieldByName ("Content-Range");
		if (pcl)
		{
			vmsHttpContentRangeHeaderField cr (pcl);
			if (!cr.m_uFirstBytePos || !cr.m_uLastBytePos)
				return false;
			if (cr.m_uLastBytePos < cr.m_uFirstBytePos)
				return false;
			m_enLA = LA_ContentRange;
			m_uContentLength = cr.m_uLastBytePos - cr.m_uFirstBytePos + 1;
			return true;
		}


		// request message body's length must be specified
		// if not - treat it as not having a body
		if (!m_pRequestMsgHdr)
		{
			m_enLA = LA_NoBody;
			return true;
		}

		m_enLA = LA_ConnectionClosure;
		return true;
	}

public:
	UINT64 getBodySize () const {return m_bDontStoreContent ? m_uBodySize : m_vbBody.size ();}
	const std::vector <BYTE>& getBody () const {assert (!m_bDontStoreContent); return m_vbBody;}

	vmsHttpMessageBodyStore (vmsHttpMessageHeaderStore* pHdr = NULL, vmsHttpMessageHeaderStore* pRequestMsgHdr = NULL) : m_pHdr (pHdr), m_pRequestMsgHdr (pRequestMsgHdr),
		m_enLA (LA_Unknown), m_uBodySize (0), m_uContentLength (0), m_nNotCompletedChunkSizeLeftToPass (0)
	{
		
	}

	void setHeaders (vmsHttpMessageHeaderStore* pHdr, vmsHttpMessageHeaderStore* pRequestMsgHdr = NULL)
	{
		assert (pHdr != NULL); // must be specified for proper parsing
		// if pRequestHdr is not NULL, - this body is the body of a server's response
		assert (pRequestMsgHdr == NULL || pRequestMsgHdr != pHdr);
		m_pHdr = pHdr;
		m_pRequestMsgHdr = pRequestMsgHdr;
	}

protected:
	vmsHttpMessageHeaderStore *m_pHdr;
	vmsHttpMessageHeaderStore *m_pRequestMsgHdr; // pointer to request message's header (used by response message parser)
	std::vector <BYTE> m_vbBody;
	UINT64 m_uBodySize; // used in "don't store body" mode
	UINT64 m_uContentLength; // valid for LA_ContentLength and LA_ContentRange only
};

class vmsHttpMessageStore : public vmsHttpMessageStoreBase
{
public:
	bool AppendData (LPBYTE pbData, int *piLen)
	{
		assert (m_enState == NeedMoreData);
		
		int iLenAvail = *piLen;

		if (m_hdr.getState () != Completed)
		{
			if (!AppendDataToStore (&m_hdr, pbData, iLenAvail))
				return false;
			if (m_hdr.getState () != Completed)
				return true;
		}

		if (!AppendDataToStore (&m_body, pbData, iLenAvail))
			return false;

		if (m_body.getState () == Completed)
			m_enState = Completed;

		// amount used
		*piLen -= iLenAvail;

		return true;
	}

protected:
	bool AppendDataToStore (vmsHttpMessageStoreBase* pStore, LPBYTE &pbData, int &iLenAvail)
	{
		assert (pStore->getState () != Completed);
		int iLenUsed = iLenAvail;
		if (!pStore->AppendData (pbData, &iLenUsed))
		{
			m_enState = pStore->getState ();
			return false;
		}

		iLenAvail -= iLenUsed;
		pbData += iLenUsed;

		assert (iLenAvail == 0 || pStore->getState () == Completed);

		if (iLenAvail && pStore->getState () != Completed)
		{
			m_enState = ParsingError;
			return false;
		}

		return true;
	}

public:
	const vmsHttpMessageHeaderStore& getHeader () const {return m_hdr;}
	const vmsHttpMessageBodyStore& getBody () const {return m_body;}
	vmsHttpMessageHeaderStore& getHeader () {return m_hdr;}
	vmsHttpMessageBodyStore& getBody () {return m_body;}

	vmsHttpMessageStore(vmsHttpMessageStore *pRequestMsg = NULL) 
	{
		m_body.setHeaders (&m_hdr, pRequestMsg ? &pRequestMsg->m_hdr : NULL);
	}

	void setRequestMsg (vmsHttpMessageStore *pRequestMsg)
	{
		assert (pRequestMsg != NULL);
		if (!pRequestMsg)
			return;
		m_body.setHeaders (&m_hdr, &pRequestMsg->m_hdr);
	}

	virtual ~vmsHttpMessageStore(void) {}

	vmsHttpMessageHeaderStore m_hdr;
	vmsHttpMessageBodyStore m_body;
};

// store for both request and response messages
class vmsHttpDialogStore
{
public:
	const vmsHttpMessageStore& getRequest () const {return m_request;}
	const vmsHttpMessageStore& getResponse () const {return m_response;}
	vmsHttpMessageStore& getRequest () {return m_request;}
	vmsHttpMessageStore& getResponse () {return m_response;}

	vmsHttpDialogStore ()
	{
		m_response.setRequestMsg (&m_request);
	}
protected:
	vmsHttpMessageStore m_request;
	vmsHttpMessageStore m_response;
};
