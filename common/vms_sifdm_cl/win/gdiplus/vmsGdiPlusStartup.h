#pragma once

class vmsGdiPlusStartup
{
public:
	vmsGdiPlusStartup ()
	{
		Gdiplus::GdiplusStartup (&m_puGdiplusToken, &m_GdiplusStartupInput, NULL);
	}

	~vmsGdiPlusStartup ()
	{
		Gdiplus::GdiplusShutdown (m_puGdiplusToken);
	}

public:
	ULONG_PTR m_puGdiplusToken;
	Gdiplus::GdiplusStartupInput m_GdiplusStartupInput;
};