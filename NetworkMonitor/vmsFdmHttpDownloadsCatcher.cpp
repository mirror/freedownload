/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#include "stdafx.h"
#include "vmsFdmHttpDownloadsCatcher.h"
#include "fdm/utils.h"

HRESULT AdjustThreadIntegrityLevel (HANDLE *phThread)
{
	HANDLE  hProcToken = NULL;
	TOKEN_MANDATORY_LABEL TML = {0};
	HANDLE  hMICToken = NULL;
	HRESULT hr = S_OK;
	BOOL bOpenProcToken = FALSE;
	BOOL bDuplicateToken = FALSE;
	BOOL bSetToken = FALSE;
	BOOL bPILToken = FALSE;

	HWND hwndDesktop = GetShellWindow ();
	if (!hwndDesktop)
		return E_FAIL;
	DWORD dwDesktopPID = 0;
	GetWindowThreadProcessId (hwndDesktop, &dwDesktopPID);
	if (!dwDesktopPID)
		return false;

	auto hProcess = OpenProcess (PROCESS_QUERY_INFORMATION, FALSE, dwDesktopPID);

	bOpenProcToken = OpenProcessToken (hProcess, MAXIMUM_ALLOWED, &hProcToken);
	if (bOpenProcToken)
	{
		bDuplicateToken = DuplicateTokenEx (hProcToken,
			MAXIMUM_ALLOWED,
			NULL,
			SecurityImpersonation,
			TokenImpersonation,
			&hMICToken);
		if (bDuplicateToken)
		{
			bSetToken = SetThreadToken (phThread, hMICToken);
			CloseHandle (hMICToken);
		}
		CloseHandle (hProcToken);
	}

	if (!bOpenProcToken || !bDuplicateToken || !bSetToken)
	{
		hr = HRESULT_FROM_WIN32 (GetLastError ());
	}

	return hr;
}

DWORD WINAPI _threadTransferDownloadToFdm (LPVOID url)
{
	if (!ImpersonateSelf (SecurityImpersonation))
		return 1;

	auto hThread = GetCurrentThread ();
	if (FAILED (AdjustThreadIntegrityLevel (&hThread)))
		return 1;

	LPWSTR wurl = reinterpret_cast <LPWSTR> (url);

	CoInitialize (0);
	vmsFdmShowAddDownloadDialog (
		wurl, false, false);
	CoUninitialize ();

	delete [] wurl;

	return 0;
}

vmsFdmHttpDownloadsCatcher::vmsFdmHttpDownloadsCatcher ()
{
}

vmsFdmHttpDownloadsCatcher::~vmsFdmHttpDownloadsCatcher ()
{
}

bool vmsFdmHttpDownloadsCatcher::on_resource_headers_rcvd ()
{
	auto &&hdr = m_httpDialog.getResponse ().getHeader ();
	vmsHttpResponseParser resp (hdr.getHeader ().c_str ());
	auto ct = resp.FieldByName ("Content-Type");
	if (ct)
	{
		if (!_stricmp (ct->getValue ().c_str (), "application/octet-stream"))
		{
			auto &&hdrReq = m_httpDialog.getRequest ().getHeader ();
			vmsHttpRequestParser req (hdrReq.getHeader ().c_str ());

			std::wstringstream wss;
			wss << L"http://";

			auto phost = req.FieldByName ("Host");
			assert (phost);
			if (!phost)
				return false;

			wss << wideFromUtf8 (phost->getValueWoExtraSpaces ());

			

			wss << wideFromUtf8 (req.getURI ());

			auto url = wss.str ();

			LPWSTR wurl = new wchar_t [url.length () + 1];
			memcpy (wurl, &url.front (), url.size () * sizeof (wchar_t));
			wurl [url.size ()] = 0;

			CloseHandle (CreateThread (nullptr, 0, 
				_threadTransferDownloadToFdm, wurl, 0, nullptr));

			return true;
		}
	}
	return false;
}