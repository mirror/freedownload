#pragma once
class vmsOsVersionBase
{
public:
	virtual std::string os_name () const = 0;
	virtual unsigned major_version () const = 0;
	virtual unsigned minor_version () const = 0;
	virtual unsigned build_number () const = 0;
	virtual ~vmsOsVersionBase () {}
};