/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
#include <comutil.h>
#include <comdef.h>
#include "fdm.h"

#ifndef IWGUrlReceiverPtr
	_COM_SMARTPTR_TYPEDEF(IWGUrlReceiver, __uuidof(IWGUrlReceiver));
#endif

#ifndef IWGUrlListReceiverPtr
	_COM_SMARTPTR_TYPEDEF (IWGUrlListReceiver, __uuidof(IWGUrlListReceiver));
#endif

#ifndef IFdmUiWindowPtr
	_COM_SMARTPTR_TYPEDEF (IFdmUiWindow, __uuidof(IFdmUiWindow));
#endif

#ifndef IFDMFlashVideoDownloadsPtr
	_COM_SMARTPTR_TYPEDEF (IFDMFlashVideoDownloads, __uuidof(IFDMFlashVideoDownloads));
#endif

template <class TWgRcvr>
inline HRESULT vmsFdmBhDownloadInfoToWgRcvr (
	const std::wstring &url,
	TWgRcvr *rcvr)
{
	assert (rcvr);

	HRESULT hr;

	if (FAILED (hr = rcvr->put_Url (_bstr_t (url.c_str ()))))
		return hr;

	return hr;
}

inline HRESULT vmsFdmBhDownloadInfoToWgUrlRcvr (
	const std::wstring &url,
	IWGUrlReceiver *rcvr)
{
	HRESULT hr = vmsFdmBhDownloadInfoToWgRcvr (url, rcvr);
	return hr;
}

inline HRESULT vmsFdmShowAddDownloadDialog (
	const std::wstring &url,
	bool catchedDownload, 
	bool waitResponse)
{
	IWGUrlReceiverPtr rcvr;
	HRESULT hr = rcvr.CreateInstance (__uuidof (WGUrlReceiver), nullptr, CLSCTX_ALL | CLSCTX_ENABLE_CLOAKING);
	assert (rcvr);
	if (!rcvr)
		return hr;

	hr = vmsFdmBhDownloadInfoToWgUrlRcvr (url, rcvr);
	if (FAILED (hr))
		return hr;

	if (catchedDownload)
		rcvr->put_IgnoreSize (FALSE);

	hr = rcvr->ShowAddDownloadDialog ();
	if (FAILED (hr))
		return hr;

	if (!waitResponse)
		return hr;

	IServiceProviderPtr servProv (rcvr);
	assert (servProv);
	IFdmUiWindowPtr uiWindow;
	if (servProv)
		servProv->QueryService (__uuidof (IFdmUiWindow), __uuidof (IFdmUiWindow), (void**)&uiWindow);
	assert (uiWindow);
	if (uiWindow)
	{
		uiWindow->WaitForWindowCreation (5000);
		ULONG u = 0;
		uiWindow->get_Handle (&u);
		if (u)
		{
			SetForegroundWindow ((HWND)u);
			BringWindowToTop ((HWND)u);
		}
	}

	BSTR bstrState = nullptr;
	do 
	{
		if (bstrState)
		{
			SysFreeString (bstrState);
			bstrState = nullptr;
		}
		Sleep (5);
		rcvr->get_UIState (&bstrState);
		assert (bstrState);
		if (!bstrState)
			return E_UNEXPECTED;
	} 
	while (_wcsicmp (bstrState, L"in_progress") == 0);

	bool added = !_wcsicmp (bstrState, L"added");
	SysFreeString (bstrState);

	return added ? S_OK : S_FALSE;
}

