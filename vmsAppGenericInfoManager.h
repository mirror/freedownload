/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
#include "vmsAppGenericInfo.h"
class vmsAppGenericInfoManager
{
public:
	vmsAppGenericInfoManager ();
	~vmsAppGenericInfoManager ();

	const vmsAppGenericInfo& info() const;

protected:
	bool readFromFile();
	bool writeToFile();
	void initialize();

protected:
	vmsAppGenericInfo m_info;
};

