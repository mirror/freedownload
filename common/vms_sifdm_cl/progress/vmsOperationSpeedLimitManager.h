#pragma once
class vmsOperationSpeedLimitManager
{
public:
	// request rights to perform an operation
	// amount - requested amount
	// amount,out - allowed amount (can be 0)
	virtual void onNeedOperation (uint32_t &amount, bool waitNonZeroAmount) = 0;
	// each onNeedOperation call must has the corresponding onDoneOperation one
	// (excluding the case allowed amount was 0)
	virtual void onDoneOperation (uint32_t amountAcquired, uint32_t amountPerformed) = 0;
	virtual ~vmsOperationSpeedLimitManager () {}
};