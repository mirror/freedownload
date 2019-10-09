/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
class vmsProtocolValidator
{
public:
	virtual bool valid_data (const uint8_t *data, uint32_t data_len) = 0;
	virtual ~vmsProtocolValidator () {}
};

