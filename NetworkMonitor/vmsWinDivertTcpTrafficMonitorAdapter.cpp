/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#include "stdafx.h"
#include "vmsWinDivertTcpTrafficMonitorAdapter.h"
#include "vmsTcpConnectionId.h"

vmsWinDivertTcpTrafficMonitorAdapter::vmsWinDivertTcpTrafficMonitorAdapter (
	HANDLE windivert,
	std::shared_ptr <vmsWinDivertConnectionsManager> connectionsManager,
	std::shared_ptr <vmsTrafficMonitor> traff_mon) :
	vmsWinDivertPassThru (windivert),
	m_connectionsManager (connectionsManager),
	m_traff_mon (traff_mon)
{
	assert (m_connectionsManager);
	assert (m_traff_mon);
}

vmsWinDivertTcpTrafficMonitorAdapter::~vmsWinDivertTcpTrafficMonitorAdapter ()
{
}

bool vmsWinDivertTcpTrafficMonitorAdapter::process_modify_packet (
	WINDIVERT_ADDRESS addr,
	UINT &packet_len)
{
	vmsWinDivertParsedPacket packet (
		&m_packet.front (), packet_len);

	assert (packet.m_tcphdr);
	if (!packet.m_tcphdr)
		return false;

	bool connection_info_changed;
	auto conn_rec = m_connectionsManager->on_packet (
		addr, packet, connection_info_changed);

	if (!conn_rec.first)
		return false;

	if (connection_info_changed)
	{
		m_traff_mon->report_connection_state (
			conn_rec.first, conn_rec.second);
	}

	bool packet_modified = false;

	if (packet.m_data_len)
	{
		vmsConnectionTrafficMonitor::on_data_parameters dp;
		dp.data.direction_in = addr.Direction == WINDIVERT_DIRECTION_INBOUND;
		dp.data.data = (const uint8_t*)packet.m_data;
		dp.data.data_len = packet.m_data_len;
		
		do 
		{
			if (dp.data_result.data_len_not_processed)
			{
				const auto data_len_processed = dp.data.data_len - 
					dp.data_result.data_len_not_processed;
				dp.data.data += data_len_processed;
				dp.data.data_len = dp.data_result.data_len_not_processed;
				dp.data_result = vmsConnectionTrafficMonitor::data_out ();
			}

			m_traff_mon->on_data (conn_rec.first, dp);

			if (!dp.data_result.modified_data.empty () ||
				(dp.data_result.flags & dp.data_result.close_connection))
			{
				
				
				assert ("!implemented" || 
					(dp.data_result.flags & dp.data_result.close_connection));

				verify (send_modified_data_and_close_connection (
					addr, packet, dp.data_result.modified_data));

				packet_modified = true;
			}
		}
		while (dp.data_result.data_len_not_processed);
	}

	return packet_modified;
}

#pragma warning(disable : 4200)

typedef struct
{
	WINDIVERT_IPHDR  ip;
	WINDIVERT_TCPHDR tcp;
} PACKET, *PPACKET;
typedef struct 
{
	PACKET header;
	uint8_t data[];
} DATAPACKET, *PDATAPACKET;

bool vmsWinDivertTcpTrafficMonitorAdapter::send_modified_data_and_close_connection (
	WINDIVERT_ADDRESS addr,
	const vmsWinDivertParsedPacket &packet, 
	const std::vector <uint8_t> &modified_data)
{
	assert (packet.m_iphdr && packet.m_tcphdr);

	std::vector <uint8_t> raw_packet (modified_data.size () + 1000);
	PDATAPACKET new_packet = (PDATAPACKET) &raw_packet.front ();

	new_packet->header.ip = *packet.m_iphdr;
	new_packet->header.tcp = *packet.m_tcphdr;

	

	uint16_t new_packet_len = sizeof (DATAPACKET) +
		(uint16_t)modified_data.size ();

	new_packet->header.ip.Length = htons (new_packet_len);

	if (!modified_data.empty ())
	{
		memcpy (new_packet->data, &modified_data.front (), modified_data.size ());
	}
	else
	{
		new_packet->header.tcp.Fin = 1;
		new_packet->header.tcp.Ack = 1;
	}

	WinDivertHelperCalcChecksums (new_packet, new_packet_len, 0);

	if (!send_packet (addr, new_packet_len, &raw_packet))
	{
		ATLTRACE ("warning: failed to send modified data (%d)\n",
			GetLastError ());
		return false;
	}

	
	if (!modified_data.empty ())
	{
		new_packet->header.tcp.SeqNum += (uint32_t)modified_data.size ();

		new_packet_len = sizeof (DATAPACKET);
		new_packet->header.ip.Length = htons (new_packet_len);

		new_packet->header.tcp.Fin = 1;
		new_packet->header.tcp.Ack = 1;

		WinDivertHelperCalcChecksums (new_packet, new_packet_len, 0);

		if (!send_packet (addr, new_packet_len, &raw_packet))
		{
			ATLTRACE ("warning: failed to send modified data (%d)\n",
				GetLastError ());
			return false;
		}
	}

	

	new_packet_len = sizeof (DATAPACKET);

	memset (&new_packet->header, 0, sizeof (PACKET));
	new_packet->header.ip.Version = 4;
	new_packet->header.ip.HdrLength = sizeof (WINDIVERT_IPHDR) / sizeof (UINT32);
	new_packet->header.ip.Length = htons (new_packet_len);
	new_packet->header.ip.TTL = 64;
	new_packet->header.ip.Protocol = IPPROTO_TCP;
	new_packet->header.tcp.HdrLength = sizeof (WINDIVERT_TCPHDR) / sizeof (UINT32);
	new_packet->header.tcp.Rst = 1;
	new_packet->header.tcp.Ack = 1;

	new_packet->header.ip.SrcAddr = packet.m_iphdr->DstAddr;
	new_packet->header.ip.DstAddr = packet.m_iphdr->SrcAddr;
	new_packet->header.tcp.SrcPort = packet.m_tcphdr->DstPort;
	new_packet->header.tcp.DstPort = packet.m_tcphdr->SrcPort;

	new_packet->header.tcp.SeqNum = packet.m_tcphdr->AckNum;
	new_packet->header.tcp.AckNum = packet.m_tcphdr->SeqNum + 
		packet.m_data_len;

	WinDivertHelperCalcChecksums (new_packet, new_packet_len, 0);

	auto reverse_addr = addr;
	reverse_addr.Direction = !reverse_addr.Direction;

	if (!send_packet (reverse_addr, new_packet_len, &raw_packet))
	{
		ATLTRACE ("warning: failed to send modified data (%d)\n",
			GetLastError ());
		return false;
	}

	return true;
}
