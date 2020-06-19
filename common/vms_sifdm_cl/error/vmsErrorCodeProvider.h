#pragma once
#include "vmsError.h"
class vmsErrorCodeProvider
{
public:
	// provides information about the last error occurred
	// generally, must be called right after the moment when the error happened
	virtual vmsError last_error () const = 0;
	virtual ~vmsErrorCodeProvider () {}
};