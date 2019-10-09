/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
#include "vms_sifdm_cl/win/vmsWinUtil.h"

inline bool fdm5installed()
{
	HKEY key;

	auto keypath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{43781dff-e0df-49ce-a6d2-47da96a485e7}}_is1";

	if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, keypath, 0, KEY_READ, &key) ||
		(vmsWinUtil::IsWow64() && ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, keypath, 0, KEY_READ | KEY_WOW64_64KEY, &key)))
	{
		RegCloseKey(key);
		return true;
	}

#ifdef _WIN64
#error "not implemented - need to check 32bit key also"
#endif

	return false;
}