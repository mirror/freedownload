/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
#include "vmsConnectionId.h"
#include "vmsConnectionInfo.h"
#include "vmsConnectionTrafficMonitor.h"
class vmsTrafficMonitor
{
public:
	virtual void report_connection_state (
		std::shared_ptr <const vmsConnectionId> connection_id,
		std::shared_ptr <const vmsConnectionInfo> info) = 0;

	virtual bool on_data (
		std::shared_ptr <const vmsConnectionId> connection_id,
		vmsConnectionTrafficMonitor::on_data_parameters &params) = 0;

	virtual ~vmsTrafficMonitor () {}
};

