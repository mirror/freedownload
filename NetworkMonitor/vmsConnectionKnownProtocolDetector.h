/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
#include "vmsConnectionProtocolDetector.h"
class vmsConnectionKnownProtocolDetector :
	public vmsConnectionProtocolDetector
{
public:
	vmsConnectionKnownProtocolDetector ()
	{
	}

	~vmsConnectionKnownProtocolDetector ()
	{
	}

	virtual std::shared_ptr <vmsConnectionTrafficMonitor>
		get_traffic_monitor (const uint8_t *data, uint32_t data_len) override
	{
		for (auto &&detector : m_detectors)
		{
			auto result = detector->get_traffic_monitor (data, data_len);
			if (result)
				return result;
		}
		return {};
	}

	void add_detector (std::unique_ptr <vmsConnectionProtocolDetector> detector)
	{
		m_detectors.push_back (std::move (detector));
	}

protected:
	std::vector <std::unique_ptr <vmsConnectionProtocolDetector>> m_detectors;
};

