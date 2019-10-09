/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
#include "vmsConnectionInfo.h"
class vmsConnectionTrafficMonitor
{
public:
	struct data_in
	{
		bool direction_in = true;
		const uint8_t *data = nullptr;
		uint32_t data_len = 0;
	};

	struct data_out
	{
		
		
		uint32_t data_len_not_processed = 0;
		
		std::vector <uint8_t> modified_data;

		enum e_flags
		{
			close_connection = 1
		};
		uint32_t flags = 0; 
	};

	struct on_data_parameters
	{
		data_in data;
		data_out data_result;
	};

	
	
	virtual bool on_data (on_data_parameters &params) = 0;
	
	virtual void report_connection_state (
		std::shared_ptr <const vmsConnectionInfo> info) = 0;

	virtual ~vmsConnectionTrafficMonitor () {}
};

