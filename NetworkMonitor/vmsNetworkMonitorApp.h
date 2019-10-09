/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
#include "vmsWinDivert.h"
#include "vmsWinDivertConnectionsManager.h"
#include "vmsKnownTrafficMonitor.h"
class vmsNetworkMonitorApp :
	public vmsCreatesThreads2
{
public:
	vmsNetworkMonitorApp ();
	~vmsNetworkMonitorApp ();
	bool initialize ();
	int run ();

protected:
	std::unique_ptr <vmsWinDivert> m_windivert;
	std::shared_ptr <vmsWinDivertConnectionsManager> m_connectionsManager;
	std::shared_ptr <vmsKnownTrafficMonitor> m_trafficMonitor;
	
	int process_packets ();
};

