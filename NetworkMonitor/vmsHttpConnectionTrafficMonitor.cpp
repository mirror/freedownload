/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#include "stdafx.h"
#include "vmsHttpConnectionTrafficMonitor.h"

vmsHttpConnectionTrafficMonitor::vmsHttpConnectionTrafficMonitor ()
{
}

vmsHttpConnectionTrafficMonitor::~vmsHttpConnectionTrafficMonitor ()
{
}

bool vmsHttpConnectionTrafficMonitor::on_data (
	on_data_parameters &params)
{
	auto len_remained = params.data.data_len;

	if (m_httpDialog.getResponse ().getState () != 
		vmsHttpMessageStoreBase::Completed)
	{
		auto &store = params.data.direction_in ?
			m_httpDialog.getResponse () :
			m_httpDialog.getRequest ();

		int len_used = (int)params.data.data_len;
		auto result = store.AppendData ((LPBYTE)params.data.data, &len_used);
		assert (result);
		if (!result)
			return false;

		assert (len_used <= (int)len_remained);
		len_remained -= (uint32_t)len_used;
	}

	assert (len_remained >= 0);

	if (len_remained)
	{
		
		assert (m_httpDialog.getResponse ().getState () == 
			vmsHttpMessageStoreBase::Completed);
		params.data_result.data_len_not_processed = len_remained;
	}

	return true;
}

void vmsHttpConnectionTrafficMonitor::report_connection_state (
	std::shared_ptr <const vmsConnectionInfo> info)
{
	if (!m_connectionInfo)
		m_connectionInfo = info;
	assert (m_connectionInfo = info);
}