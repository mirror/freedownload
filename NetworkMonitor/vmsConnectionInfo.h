/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
class vmsConnectionInfo
{
public:
	enum class direction { in, out };
	enum class state { initiating, connected, closed };

	vmsConnectionInfo (direction original_dir, 
		state s = state::initiating) :
		m_original_direction (original_dir),
		m_state (s)
	{
	}

	virtual ~vmsConnectionInfo () {}

	direction original_direction () const
	{
		return m_original_direction;
	}

	state connection_state () const
	{
		return m_state;
	}
	void set_connection_state (state s)
	{
		m_state = s;
	}

protected:
	direction m_original_direction;
	state m_state;
};

