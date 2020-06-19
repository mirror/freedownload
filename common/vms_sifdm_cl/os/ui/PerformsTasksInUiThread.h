#pragma once
// some tasks can be done in a specific thread only
// e.g. Windows UI controls can be manipulated only from the thread created them
class PerformsTasksInUiThread
{
public:
	virtual void performTasksInUiThread () = 0;
	virtual ~PerformsTasksInUiThread () {}
};