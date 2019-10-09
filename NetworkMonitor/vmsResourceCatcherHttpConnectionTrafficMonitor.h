/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
#include "vmsHttpConnectionTrafficMonitor.h"
class vmsResourceCatcherHttpConnectionTrafficMonitor :
	public vmsHttpConnectionTrafficMonitor
{
public:
	vmsResourceCatcherHttpConnectionTrafficMonitor ();
	~vmsResourceCatcherHttpConnectionTrafficMonitor ();

	virtual bool on_data (
		vmsConnectionTrafficMonitor::on_data_parameters &params) override;

protected:
	
	virtual bool on_resource_headers_rcvd () {return false;}

protected:
	bool m_headersRcvd = false;
};

