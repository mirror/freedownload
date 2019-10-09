/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#include "stdafx.h"
#include "vmsKnownTrafficMonitor.h"
#include "vmsHttpProtocolValidator.h"
#include "vmsHttpConnectionTrafficMonitor.h"

vmsKnownTrafficMonitor::vmsKnownTrafficMonitor (
	std::shared_ptr <vmsConnectionProtocolDetector> prot_detector) :
	m_prot_detector (prot_detector)
{
	assert (m_prot_detector);
}

vmsKnownTrafficMonitor::~vmsKnownTrafficMonitor ()
{
}

void vmsKnownTrafficMonitor::report_connection_state (
	std::shared_ptr <const vmsConnectionId> connection_id,
	std::shared_ptr <const vmsConnectionInfo> info)
{
	vmsThreadSafe4Scope;
	
	auto itConnection = m_connections.find (connection_id);

	if (itConnection == m_connections.end ())
	{
		if (info->connection_state () == 
			vmsConnectionInfo::state::initiating)
		{
			connection_record rec;
			rec.info = info;
			m_connections.insert (std::make_pair (connection_id, rec));
		}
		return;
	}

	auto &&rec = itConnection->second;

	assert (rec.info == info);

	if (rec.monitor)
		rec.monitor->report_connection_state (info);

	if (info->connection_state () == vmsConnectionInfo::state::closed)
		m_connections.erase (itConnection);
}

bool vmsKnownTrafficMonitor::on_data (
	std::shared_ptr <const vmsConnectionId> connection_id,
	vmsConnectionTrafficMonitor::on_data_parameters &params)
{
	vmsThreadSafe4Scope;

	auto itConnection = m_connections.find (connection_id);
	
	if (itConnection == m_connections.end ())
		return false;

	auto &&rec = itConnection->second;

	if (rec.ignore)
		return true;

	if (!rec.monitor)
	{
		rec.monitor = m_prot_detector->get_traffic_monitor (
			params.data.data, params.data.data_len);
		if (!rec.monitor)
		{
			rec.ignore = true;
			return true;
		}
		rec.monitor->report_connection_state (rec.info);
	}

	if (!rec.monitor->on_data (params))
	{
		rec.ignore = true;
		return true;
	}

	if (params.data_result.data_len_not_processed)
	{
		rec.monitor = nullptr; 
	}

	return true;
}

