#pragma once

// interfaces which are used to bind serialization stream with a target stream (file / memory buffer / etc.)

class vmsSerializationInputStreamBinding
{
public:
	vmsSerializationInputStreamBinding ()
	{

	}

	virtual ~vmsSerializationInputStreamBinding ()
	{

	}

	// NULL to unbind from stream
	virtual bool BindToStream (std::shared_ptr <std::istream> spStream)
	{
		m_spBoundStream = spStream;
		return true;
	}
	
protected:
	std::shared_ptr <std::istream> m_spBoundStream;
};


class vmsSerializationOutputStreamBinding
{
public:
	vmsSerializationOutputStreamBinding () : m_bFlushedToBoundStream (false)
	{

	}

	virtual ~vmsSerializationOutputStreamBinding ()
	{

	}

	virtual bool BindToStream (std::shared_ptr <std::ostream> spStream)
	{
		m_spBoundStream = spStream;
		m_bFlushedToBoundStream = false;
		return true;
	}

	// flush all data from serialization stream to bound stream
	virtual bool Flush ()
	{
		m_bFlushedToBoundStream = true;
		return true;
	}

protected:
	std::shared_ptr <std::ostream> m_spBoundStream;
	bool m_bFlushedToBoundStream;
};