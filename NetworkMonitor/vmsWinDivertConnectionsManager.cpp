/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#include "stdafx.h"
#include "vmsWinDivertConnectionsManager.h"

vmsWinDivertConnectionsManager::vmsWinDivertConnectionsManager ()
{
}

vmsWinDivertConnectionsManager::~vmsWinDivertConnectionsManager ()
{
}

vmsWinDivertConnectionsManager::connection_record_t 
vmsWinDivertConnectionsManager::on_packet (
	WINDIVERT_ADDRESS addr, 
	const vmsWinDivertParsedPacket &packet,
	bool &connection_info_changed)
{
	connection_info_changed = false;

	if (!packet.m_iphdr || !packet.m_tcphdr)
		return {}; 

	connection_record_t result;

	const vmsTcpConnectionId::ipv4_connection_id conn_id = 
		addr.Direction == WINDIVERT_DIRECTION_OUTBOUND ? 
		std::make_tuple (packet.m_iphdr->SrcAddr, packet.m_iphdr->DstAddr,
		packet.m_tcphdr->SrcPort, packet.m_tcphdr->DstPort) :
		std::make_tuple (packet.m_iphdr->DstAddr, packet.m_iphdr->SrcAddr,
		packet.m_tcphdr->DstPort, packet.m_tcphdr->SrcPort);

	vmsThreadSafe4Scope;

	auto itConnection = m_tcpConnections.find (conn_id);
	bool have_connection = itConnection != m_tcpConnections.end ();
	if (have_connection)
		result = itConnection->second;

	if (packet.m_tcphdr->Syn)
	{
		

		auto conn_dir = addr.Direction == WINDIVERT_DIRECTION_INBOUND ?
			vmsConnectionInfo::direction::in :
			vmsConnectionInfo::direction::out;

		if (have_connection)
		{
			auto conn_info = result.second;
			switch (conn_info->connection_state ())
			{
			case vmsConnectionInfo::state::initiating:
				
				return result;

			case vmsConnectionInfo::state::connected:
				assert (!"expected");
				break; 

			default:
				break;
			}

			m_tcpConnections.erase (itConnection);
			have_connection = false;
		}			

		result = connection_record_t (
			std::make_shared <vmsTcpConnectionId> (conn_id),
			std::make_shared <vmsConnectionInfo> (conn_dir));

		itConnection = m_tcpConnections.insert (
			std::make_pair (conn_id, result)).first;

		have_connection = true;
		connection_info_changed = true;
	}
	else if (packet.m_tcphdr->Fin || packet.m_tcphdr->Rst)
	{
		

		if (have_connection)
		{
			result.second->set_connection_state (
				vmsConnectionInfo::state::closed);
			connection_info_changed = true;
			m_tcpConnections.erase (itConnection);
			return result;
		}
	}

	if (!have_connection)
		return {};

	if (packet.m_data_len)
	{
		if (result.second->connection_state () != 
			vmsConnectionInfo::state::connected)
		{
			result.second->set_connection_state (
				vmsConnectionInfo::state::connected);
			connection_info_changed = true;
		}
	}

	return result;
}
