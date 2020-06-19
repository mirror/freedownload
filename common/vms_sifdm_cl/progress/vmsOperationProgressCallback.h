#pragma once
class vmsOperationProgressCallback
{
public:
	// return false to abort operation
	virtual bool onOperationProgressPercentage (double) = 0;
	virtual ~vmsOperationProgressCallback () {}
};