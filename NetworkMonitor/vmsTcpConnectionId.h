/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
#include "vmsIpConnectionId.h"
class vmsTcpConnectionId :
	public vmsIpConnectionId
{
public:
	
	using ipv4_connection_id = std::tuple <UINT, UINT, UINT16, UINT16>;

public:
	vmsTcpConnectionId (ipv4_connection_id id) :
		vmsIpConnectionId (std::get<0> (id), std::get<1> (id)),
		m_SrcPort (std::get<2> (id)),
		m_DstPort (std::get<3> (id))
	{
	}

	~vmsTcpConnectionId ()
	{
	}

protected:
	UINT16 m_SrcPort;
	UINT16 m_DstPort;
};

