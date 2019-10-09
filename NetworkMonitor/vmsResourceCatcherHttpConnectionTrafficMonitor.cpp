/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#include "stdafx.h"
#include "vmsResourceCatcherHttpConnectionTrafficMonitor.h"

vmsResourceCatcherHttpConnectionTrafficMonitor::vmsResourceCatcherHttpConnectionTrafficMonitor ()
{
}

vmsResourceCatcherHttpConnectionTrafficMonitor::~vmsResourceCatcherHttpConnectionTrafficMonitor ()
{
}

bool vmsResourceCatcherHttpConnectionTrafficMonitor::on_data (
	vmsConnectionTrafficMonitor::on_data_parameters &params)
{
	if (m_connectionInfo->original_direction () != 
		vmsConnectionInfo::direction::out)
	{
		return false;
	}

	auto result = vmsHttpConnectionTrafficMonitor::on_data (params);
	if (!result)
		return false;

	if (!m_headersRcvd)
	{
		auto &&hdr = m_httpDialog.getResponse ().getHeader ();
		if (hdr.getState () == vmsHttpMessageStoreBase::Completed)
		{
			m_headersRcvd = true;
			if (on_resource_headers_rcvd ())
			{
				std::string resp = 
					"HTTP/1.1 204 OK\r\n"
					"Content-Length: 0\r\n"
					"Connection: close\r\n"
					"\r\n";
				params.data_result.modified_data.assign (resp.begin (), resp.end ());
				params.data_result.flags |= params.data_result.close_connection;
			}
		}
	}

	return result;
}