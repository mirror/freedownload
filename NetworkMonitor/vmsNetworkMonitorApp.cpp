/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#include "stdafx.h"
#include "vmsNetworkMonitorApp.h"
#include "vmsWinDivertTcpTrafficMonitorAdapter.h"
#include "vmsConnectionKnownProtocolDetector.h"
#include "vmsHttpProtocolValidator.h"
#include "vmsFdmHttpDownloadsCatcher.h"

vmsNetworkMonitorApp::vmsNetworkMonitorApp ()
{
}

vmsNetworkMonitorApp::~vmsNetworkMonitorApp ()
{
	shutdown ();
}

bool vmsNetworkMonitorApp::initialize ()
{
	assert (IsUserAnAdmin ());
	if (!IsUserAnAdmin ())
		return false;

	m_connectionsManager = 
		std::make_shared <vmsWinDivertConnectionsManager> ();

	auto prot_detector = std::make_shared <vmsConnectionKnownProtocolDetector> ();
	prot_detector->add_detector (
		std::make_unique <vmsSingleConnectionProtocolDetector <
		vmsHttpProtocolValidator, vmsFdmHttpDownloadsCatcher>> ());

	m_trafficMonitor = 
		std::make_shared <vmsKnownTrafficMonitor> (prot_detector);

	return true;
}

int vmsNetworkMonitorApp::run ()
{
	m_windivert = std::make_unique <vmsWinDivert> ();
	if (!m_windivert->status_ok ())
		return 1;
	
	return process_packets ();
}

int vmsNetworkMonitorApp::process_packets ()
{
	vmsWinDivertTcpTrafficMonitorAdapter mon (
		m_windivert->handle (), 
		m_connectionsManager, 
		m_trafficMonitor);

	while (!m_shutting_down)
	{
		mon.process_packet ();
	}

	return 0;
}
