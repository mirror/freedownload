#pragma once
#include "../../os_types.h"
class vmsOsClipboardBase
{
public:
	vmsOsClipboardBase (vmsOsWindowHandle window_handle) :
		m_windowHandle (window_handle) {}
	virtual ~vmsOsClipboardBase () {}

	virtual bool text (const std::wstring& text) = 0;
	virtual std::wstring text () = 0;

protected:
	vmsOsWindowHandle m_windowHandle;
};