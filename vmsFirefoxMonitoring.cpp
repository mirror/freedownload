/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#include "stdafx.h"
#include "FdmApp.h"
#include "vmsFirefoxMonitoring.h"
#include "common/vmsFirefoxExtensionInstaller.h"
#include "vmsAppGlobalObjects.h"
#include "common/vmsFirefoxUtil.h"
#include "vmsFirefoxExtensionInfo.h"
#include "vmsTmpFileName.h"
#include "vmsRegisteredApp.h"
#include "common/vms_sifdm_cl/win/apps/util.h"

#define FDM_NEW_CID			_T("fdm_ffext2@freedownloadmanager.org")
#define FDM_LEGACY_CID		_T("fdm_ffext@freedownloadmanager.org")

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

vmsFirefoxMonitoring::vmsFirefoxMonitoring()
{

}

vmsFirefoxMonitoring::~vmsFirefoxMonitoring()
{

}

bool vmsFirefoxMonitoring::IsInstalled()
{
	return vmsFirefoxExtensionInstaller::IsInstalledInProfile(
		FDM_NEW_CID,
		true,
		(LPCTSTR)_App.Firefox_PortableVersionPath());
}

bool vmsFirefoxMonitoring::Install(bool bInstall)
{
	if (bInstall)
	{
		auto ee = vmsGetAppAbsolutePath(L"firefox.exe");
		if (ee.empty() ||
			GetFileAttributes(ee.c_str()) == DWORD(-1))
		{
			ee = L"firefox.exe";
		}
		vmsCommandLine cl;
		cl.setExe(ee.c_str());
		cl.setArgs(_T("https://addons.mozilla.org/en-US/firefox/addon/free-download-manager-addon/"));
		return cl.Execute();
	}
	else
	{
		return vmsFirefoxExtensionInstaller::RemoveXpiInstalledInProfile(
			FDM_NEW_CID,
			true,
			(LPCTSTR)_App.Firefox_PortableVersionPath());
	}
}

bool vmsFirefoxMonitoring::IsInstalled_OLDWAY2()
{
	return vmsFirefoxExtensionInstaller::IsInstalledInProfile(
		FDM_LEGACY_CID, 
		true, 
		(LPCTSTR)_App.Firefox_PortableVersionPath ());
}

bool vmsFirefoxMonitoring::Install_OLDWAY2(bool bInstall)
{
	if (bInstall)
	{
		CString strPath = ((CFdmApp*)AfxGetApp())->m_strAppPath;
		strPath += "Firefox\\extension.xpi";
		auto ee = vmsGetAppAbsolutePath(L"firefox.exe");
		if (ee.empty() ||
			GetFileAttributes(ee.c_str()) == DWORD(-1))
		{
			ee = L"firefox.exe";
		}
		vmsCommandLine cl;
		cl.setExe(ee.c_str());
		cl.setArgs(CString("\"") + strPath + "\"");
		return cl.Execute();
	}
	else
	{
		return vmsFirefoxExtensionInstaller::RemoveXpiInstalledInProfile(
			FDM_LEGACY_CID,
			true,
			(LPCTSTR)_App.Firefox_PortableVersionPath());
	}
}

bool vmsFirefoxMonitoring::IsInstalled_OLDWAY()
{
	return vmsFirefoxExtensionInstaller::IsInstalledUsingRegistry(FDM_LEGACY_CID) ||
		vmsFirefoxExtensionInstaller::IsInstalledInProfile (FDM_LEGACY_CID, true, (LPCTSTR)_App.Firefox_PortableVersionPath (), false);
}

bool vmsFirefoxMonitoring::Install_OLDWAY(bool bInstall)
{
	CString strPath = ((CFdmApp*)AfxGetApp ())->m_strAppPath;
	strPath += "Firefox\\Extension";
	if ( bInstall )
		return vmsFirefoxExtensionInstaller::DoUsingRegistry (FDM_LEGACY_CID, strPath, bInstall);
	else{
		bool bResult1 = vmsFirefoxExtensionInstaller::DoUsingRegistry (FDM_LEGACY_CID, strPath, bInstall) ;
		bool bResult2 = vmsFirefoxExtensionInstaller::Do (FDM_LEGACY_CID, strPath, 
			(LPCTSTR)_App.Firefox_PortableVersionPath (), bInstall) ;
		return bResult1 && bResult2;
	}
}

bool vmsFirefoxMonitoring::IsEnabledInFirefox(bool &bEnabled)
{
	TCHAR tszPath [MAX_PATH] = _T ("");
	if (!vmsFirefoxUtil::GetDefaultProfilePath (tszPath))
		return false;
	if (!*tszPath)
		return false;

	vmsFirefox26ExtensionInfo fei26;
	if(CheckEnabled(fei26, tszPath, _T ("\\extensions.json"), bEnabled))
		return true;

	vmsFirefoxExtensionInfo fei;
	if(CheckEnabled(fei, tszPath, _T ("\\extensions.sqlite"), bEnabled))
		return true;

	return false;
}

bool vmsFirefoxMonitoring::CheckEnabled(vmsFirefoxExtensionInfo& fei,
		LPCTSTR profile, LPCTSTR file, bool& bEnabled)
{
	BOOL enabled1 = FALSE, enabled2 = FALSE;
	bool result = CheckEnabled(fei, profile, file, FDM_NEW_CID, bEnabled);
	if (result && bEnabled)
		return true;
	if (CheckEnabled(fei, profile, file, FDM_LEGACY_CID, bEnabled))
		result = true;
	return result;
}

bool vmsFirefoxMonitoring::CheckEnabled(vmsFirefoxExtensionInfo& fei,
	LPCTSTR profile, LPCTSTR file, LPCTSTR extensionID, bool& bEnabled)
{
	bEnabled = false;
	TCHAR tszPath [MAX_PATH];
	_tcsncpy(tszPath, profile, MAX_PATH);
	_tcsncat(tszPath, file, MAX_PATH);

	if (!fei.Read(tszPath, extensionID))
	{
		vmsTmpFileName tmpFile;
		if (!CopyFile(tszPath, tmpFile, FALSE))
			return false;
		if (!fei.Read(tmpFile, extensionID))
			return false;
	}

	bEnabled = !fei.m_iAppDisabled && !fei.m_iSoftDisabled && !fei.m_iUserDisabled;

	return true;
}

bool vmsFirefoxMonitoring::IsFFInstalled ()
{
	CString str = _App.Firefox_PortableVersionPath ();
	if (!str.IsEmpty ())
	{
		str += _T("\\firefox.exe");
		return GetFileAttributes (str) != DWORD (-1);
	}
	else
	{
		if(vmsRegisteredApp::GetFullPath(_T("firefox.exe")).GetLength() == 0)
			return false;
		return true;
	}
}

bool vmsFirefoxMonitoring::ProfileExists(){
	CString str = _App.Firefox_PortableVersionPath ();
	if (!str.IsEmpty ())
	{
		return true;
	}
	FU_STRINGLIST v; int nDefProf;
	vmsFirefoxUtil::GetProfilesPathes (v, nDefProf);
	return ( v.size() > 0 );
}