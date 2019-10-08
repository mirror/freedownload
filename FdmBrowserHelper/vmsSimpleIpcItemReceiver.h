/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
#include "vmsSimpleIpcStringItem.h"
class vmsSimpleIpcItemReceiver
{
public:
	enum 
	{
		rcv_uri_encoded = 1,
		rcv_base64_encoded = 1 << 1,
		rcv_data_len_as_string = 1 << 2,
	};

public:
	vmsSimpleIpcItemReceiver ()
	{
	}

	virtual ~vmsSimpleIpcItemReceiver ()
	{
	}

	void set_flags (uint32_t flags, bool set = true)
	{
		if (set)
			m_flags |= flags;
		else
			m_flags &= ~flags;
	}

	std::unique_ptr <vmsSimpleIpcItem> receive ()
	{
		std::unique_ptr <vmsSimpleIpcItem> result;

		uint32_t size = 0;
		bool hasSize = false;

		if (m_flags & rcv_data_len_as_string)
		{
			std::string str;
			char ch;
			while (1 == fread (&ch, 1, 1, stdin) &&
				ch != ' ')
				str += ch;
			size = atoi (str.c_str ());
			hasSize = size != 0;
		}
		else
		{
			hasSize = 1 == fread (&size, 4, 1, stdin);
		}

		if (hasSize)
		{
			assert (size);

			std::string str;
			str.resize (size);

			auto read = fread (&str.front (), 1, size, stdin);

			if (size == read)
			{
				if (m_flags & rcv_base64_encoded)
					str = base64::decode (str);
				else if (m_flags & rcv_uri_encoded)
					str = UriDecode (str);
				result = createIpcItem (str);
			}
			else
			{
				assert (!"expected");
			}
		}		

		return std::move (result);
	}

protected:
	uint32_t m_flags = 0;
	
protected:
	virtual std::unique_ptr <vmsSimpleIpcItem> createIpcItem (
		const std::string &content)
	{
		auto result = std::make_unique <vmsSimpleIpcStringItem> ();
		result->content (content);
		return std::move (result);
	}
};

