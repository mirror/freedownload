/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
#include "vmsConnectionTrafficMonitor.h"
class vmsHttpConnectionTrafficMonitor :
	public vmsConnectionTrafficMonitor
{
public:
	vmsHttpConnectionTrafficMonitor ();
	~vmsHttpConnectionTrafficMonitor ();

	virtual bool on_data (
		vmsConnectionTrafficMonitor::on_data_parameters &params) override;

	virtual void report_connection_state (
		std::shared_ptr <const vmsConnectionInfo> info) override;

protected:
	vmsHttpDialogStore m_httpDialog;
	std::shared_ptr <const vmsConnectionInfo> m_connectionInfo;
};

