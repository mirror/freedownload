#pragma once
#include "vmsLockable.h"
#include "win/vmsWinCriticalSection.h"

// todo: move all classes from vmsThreadSafe to this vmsThreadSafe2 and remove "2" from its name then.

class vmsThreadSafe2 : public vmsLockable
{
public:
	vmsThreadSafe2 () {}
protected:
	vmsWinCriticalSection m_objectLock;
public:
	vmsLockable_ImplementDelegatedTo (m_objectLock);
private:
	vmsThreadSafe2 (const vmsThreadSafe2&);
	vmsThreadSafe2& operator = (const vmsThreadSafe2&);
};

#define vmsThreadSafe2Scope auto spLock = LockAuto ()
#define vmsThreadSafe2ScopeUnlock spLock = nullptr