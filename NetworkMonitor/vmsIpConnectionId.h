/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
#include "vmsConnectionId.h"
class vmsIpConnectionId :
	public vmsConnectionId
{
public:
	vmsIpConnectionId (UINT32 SrcAddr, UINT32 DstAddr) :
		m_SrcAddr (SrcAddr),
		m_DstAddr (DstAddr)
	{
	}

	~vmsIpConnectionId ()
	{
	}

	bool v6 () const
	{
		return m_v6;
	}

protected:
	bool m_v6 = false;
	UINT32 m_SrcAddr;
	UINT32 m_DstAddr;
};

