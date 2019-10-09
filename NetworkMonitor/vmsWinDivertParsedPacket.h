/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
class vmsWinDivertParsedPacket
{
public:
	vmsWinDivertParsedPacket (
		LPVOID packet, 
		UINT packet_len)
	{
		WinDivertHelperParsePacket (packet, packet_len,
			&m_iphdr, nullptr, nullptr, nullptr, &m_tcphdr, nullptr,
			&m_data, &m_data_len);
	}

	~vmsWinDivertParsedPacket ()
	{
	}

public:
	PWINDIVERT_IPHDR m_iphdr = nullptr;
	PWINDIVERT_TCPHDR m_tcphdr = nullptr;
	PVOID m_data = nullptr;
	UINT m_data_len = 0;
};

