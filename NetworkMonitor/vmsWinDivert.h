/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
#include "windivert/windivert.h"
class vmsWinDivert
{
public:
	vmsWinDivert (const char *filter = "tcp")
	{
		m_handle = WinDivertOpen (filter,
			WINDIVERT_LAYER_NETWORK, 0, 0);
		assert (m_handle != INVALID_HANDLE_VALUE);
	}

	~vmsWinDivert ()
	{
		if (m_handle != INVALID_HANDLE_VALUE)
			WinDivertClose (m_handle);
	}

	bool status_ok () const
	{
		return m_handle != INVALID_HANDLE_VALUE;
	}

	HANDLE handle () const 
	{
		return m_handle;
	}

protected:
	HANDLE m_handle = INVALID_HANDLE_VALUE;
};

