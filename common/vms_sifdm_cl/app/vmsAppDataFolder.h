#pragma once

class vmsAppDataFolderBase
{
public:
	// wstrCompanyName can be empty
	// are you sure it's required to be empty? :)
	vmsAppDataFolderBase (const std::wstring& wstrCompanyName, const std::wstring& wstrAppName) : 
		m_wstrAppName (wstrAppName),
		m_wstrCompanyName (wstrCompanyName)
	{

	}
 
	virtual std::wstring path (bool bCommon = false) = NULL;

	virtual std::wstring filePath (const std::wstring& wstrFileName, bool bCommon = false)
	{
		return path (bCommon) + L"\\" + wstrFileName;
	}

protected:
	std::wstring m_wstrAppName;
	std::wstring m_wstrCompanyName;
};


#ifdef _WIN32
#include "win/vmsWinAppDataFolder.h"
typedef vmsWinAppDataFolder vmsAppDataFolder;
#endif