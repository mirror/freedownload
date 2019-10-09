/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#include "stdafx.h"
#include "vmsAppGenericInfoManager.h"
#include "mfchelp.h"

namespace
{
	static const auto InfoFileName = L"appinfo.json";
}

vmsAppGenericInfoManager::vmsAppGenericInfoManager ()
{
	if (!readFromFile())
	{
		initialize();
		writeToFile();
	}
}

vmsAppGenericInfoManager::~vmsAppGenericInfoManager ()
{
}

bool vmsAppGenericInfoManager::readFromFile ()
{
	auto filename = fsGetDataFilePath(InfoFileName);
	HANDLE file = CreateFile (filename, GENERIC_READ, 0, nullptr, OPEN_EXISTING, 0, 0);
	bool ok = false;
	if (file != INVALID_HANDLE_VALUE)
	{
		std::string str;
		str.resize(GetFileSize (file, nullptr));
		if (!str.empty ())
		{
			DWORD dw = 0;
			ReadFile (file, &str.front (), str.size (), &dw, nullptr);
			ok = dw && vmsJsonSerializeObject (m_info, str);
		}
		CloseHandle(file);
	}
	return ok;
}

bool vmsAppGenericInfoManager::writeToFile ()
{
	auto str = vmsJsonSerializeObject(m_info);
	auto filename = fsGetDataFilePath(InfoFileName);
	HANDLE file = CreateFile (filename, GENERIC_WRITE, 0, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_HIDDEN, 0);
	if (file == INVALID_HANDLE_VALUE)
		return false;
	DWORD dw;
	WriteFile(file, &str.front(), str.size(), &dw, 0);
	CloseHandle(file);
	return dw == str.size();
}

void vmsAppGenericInfoManager::initialize()
{
	GUID guid;
	if (FAILED (CoCreateGuid (&guid)))
	{
		assert(!"expected");
		return;
	}
	wchar_t wszGuid [100] = L"";
	StringFromGUID2 (guid, wszGuid, _countof (wszGuid));
	m_info.m_appGuid = wszGuid;
}

const vmsAppGenericInfo& vmsAppGenericInfoManager::info() const
{
	return m_info;
}