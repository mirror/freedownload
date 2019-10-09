/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
#include "vmsProtocolValidator.h"
class vmsHttpProtocolValidator :
	public vmsProtocolValidator
{
public:
	vmsHttpProtocolValidator ()
	{
	}

	~vmsHttpProtocolValidator ()
	{
	}

	virtual bool valid_data (const uint8_t *data, uint32_t data_len) override
	{
		if ((data_len >= 4 && !_strnicmp ((char*)data, "GET ", 4)) || 
			(data_len >= 5 && !_strnicmp ((char*)data, "POST ", 5)))
		{
			return true;
		}

		return false;
	}
};

