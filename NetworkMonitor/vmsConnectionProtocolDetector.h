/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
#include "vmsConnectionTrafficMonitor.h"
class vmsConnectionProtocolDetector
{
public:
	virtual std::shared_ptr <vmsConnectionTrafficMonitor> 
		get_traffic_monitor (const uint8_t *data, uint32_t data_len) = 0;
	virtual ~vmsConnectionProtocolDetector () {}
};

#include "vmsProtocolValidator.h"
template <class TValidator, class TMonitor>
class vmsSingleConnectionProtocolDetector :
	public vmsConnectionProtocolDetector
{
public:
	virtual std::shared_ptr <vmsConnectionTrafficMonitor>
		get_traffic_monitor (const uint8_t *data, uint32_t data_len) override
	{
		TValidator v; 
		if (static_cast <vmsProtocolValidator&> (v).valid_data (data, data_len))
			return std::make_shared <TMonitor> ();
		return {};
	}
};
