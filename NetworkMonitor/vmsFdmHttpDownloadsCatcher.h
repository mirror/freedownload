/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
#include "vmsResourceCatcherHttpConnectionTrafficMonitor.h"
class vmsFdmHttpDownloadsCatcher :
	public vmsResourceCatcherHttpConnectionTrafficMonitor
{
public:
	vmsFdmHttpDownloadsCatcher ();
	~vmsFdmHttpDownloadsCatcher ();

protected:
	virtual bool on_resource_headers_rcvd () override;
};

