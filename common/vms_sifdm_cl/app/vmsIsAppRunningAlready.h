#pragma once

class vmsIsAppRunningAlreadyBase
{
public:
	vmsIsAppRunningAlreadyBase (const std::wstring& wstrAppName) :
	  m_wstrAppName (wstrAppName)
	{
	}

	virtual bool isAnotherInstanceRunning () = NULL;
	// set the calling app visible to other apps as running
	virtual void inidicateMeRunning () = NULL;
	// cancels the effect of calling to inidicateMeRunning ()
	virtual void inidicateMeNotRunning () = NULL;
	// app should use this method if it wants to be a single instance
	// returns false in case another instance is running already
	// in this case app may just exit
	virtual bool incicateMeRunningIfSingle () = 0;
	// is indicateXXX method called successfully
	virtual bool isInstanceRegistered () = 0;

protected:
	std::wstring m_wstrAppName;
};

#ifdef _WIN32
#include "win/vmsIsWinAppRunningAlready.h"
typedef vmsIsWinAppRunningAlready vmsIsAppRunningAlready;
#endif