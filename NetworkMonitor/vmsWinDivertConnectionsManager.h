/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
#include "vmsTcpConnectionId.h"
#include "vmsWinDivertParsedPacket.h"
#include "vmsConnectionInfo.h"
class vmsWinDivertConnectionsManager :
	protected vmsThreadSafe4
{
public:
	using connection_record_t = 
		std::pair <std::shared_ptr <vmsTcpConnectionId>, std::shared_ptr <vmsConnectionInfo>>;

	vmsWinDivertConnectionsManager ();
	~vmsWinDivertConnectionsManager ();

	connection_record_t on_packet (
		WINDIVERT_ADDRESS addr, 
		const vmsWinDivertParsedPacket &packet,
		bool &connection_info_changed);

protected:
	
	std::map <vmsTcpConnectionId::ipv4_connection_id, 
		connection_record_t> m_tcpConnections;
};

