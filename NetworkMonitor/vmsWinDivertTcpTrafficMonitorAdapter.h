/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
#include "vmsWinDivertPassThru.h"
#include "vmsTrafficMonitor.h"
#include "vmsWinDivertConnectionsManager.h"
class vmsWinDivertTcpTrafficMonitorAdapter :
	public vmsWinDivertPassThru
{
public:
	vmsWinDivertTcpTrafficMonitorAdapter (
		HANDLE windivert,
		std::shared_ptr <vmsWinDivertConnectionsManager> connectionsManager,
		std::shared_ptr <vmsTrafficMonitor> traff_mon);
	~vmsWinDivertTcpTrafficMonitorAdapter ();

protected:
	std::shared_ptr <vmsWinDivertConnectionsManager> m_connectionsManager;
	std::shared_ptr <vmsTrafficMonitor> m_traff_mon;

protected:
	virtual bool process_modify_packet (WINDIVERT_ADDRESS addr,
		UINT &packet_len) override;
	bool send_modified_data_and_close_connection (
		WINDIVERT_ADDRESS addr,
		const vmsWinDivertParsedPacket &packet,
		const std::vector <uint8_t> &modified_data);
};

