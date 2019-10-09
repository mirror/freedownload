/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
#include "vmsTrafficMonitor.h"
#include "vmsConnectionTrafficMonitor.h"
#include "vmsConnectionProtocolDetector.h"
class vmsKnownTrafficMonitor :
	public vmsTrafficMonitor,
	public vmsThreadSafe4
{
public:
	vmsKnownTrafficMonitor (
		std::shared_ptr <vmsConnectionProtocolDetector> prot_detector);
	~vmsKnownTrafficMonitor ();

	virtual void report_connection_state (
		std::shared_ptr <const vmsConnectionId> connection_id,
		std::shared_ptr <const vmsConnectionInfo> info) override;

	virtual bool on_data (
		std::shared_ptr <const vmsConnectionId> connection_id,
		vmsConnectionTrafficMonitor::on_data_parameters &params) override;

protected:
	std::shared_ptr <vmsConnectionProtocolDetector> m_prot_detector;

protected:
	struct connection_record
	{
		std::shared_ptr <const vmsConnectionInfo> info;
		std::shared_ptr <vmsConnectionTrafficMonitor> monitor;
		bool ignore = false;
	};

	std::unordered_map <
		std::shared_ptr <const vmsConnectionId>, 
		connection_record> m_connections;
};

