/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
class vmsWinDivertPassThru
{
public:
	vmsWinDivertPassThru (HANDLE windivert) :
		m_windivert (windivert),
		m_packet (10000)
	{
	}

	virtual ~vmsWinDivertPassThru ()
	{
	}

	bool process_packet ()
	{
		UINT packet_len;
		WINDIVERT_ADDRESS addr;

		if (!recv_packet (addr, packet_len))
			return false;

		if (!process_modify_packet (addr, packet_len))
			send_packet (addr, packet_len);

		return true;
	}

protected:
	HANDLE m_windivert;
	std::vector <uint8_t> m_packet;

protected:
	
	virtual bool process_modify_packet (WINDIVERT_ADDRESS addr, 
		UINT &packet_len) = 0;

protected:
	bool recv_packet (WINDIVERT_ADDRESS &addr, UINT &packet_len,
		std::vector <uint8_t> *packet = nullptr)
	{
		auto &&pack = packet ? *packet : m_packet;
		
		if (!WinDivertRecv (m_windivert,
			&pack.front (), pack.size (), &addr, &packet_len))
		{
			ATLTRACE (L"warning: failed to read packet (%d)\n",
				GetLastError ());
			return false;
		}
		return true;
	}

	bool send_packet (WINDIVERT_ADDRESS addr, UINT packet_len,
		std::vector <uint8_t> *packet = nullptr)
	{
		auto &&pack = packet ? *packet : m_packet;
		
		if (!WinDivertSend (m_windivert,
			&pack.front (), packet_len, &addr, nullptr))
		{
			ATLTRACE (L"warning: failed to reinject packet (%d)\n",
				GetLastError ());
			return false;
		}
		return true;
	}
};

