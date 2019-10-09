/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#include "stdafx.h"
#include "Fdm5BannerWindow.h"
#include "../common/vms_sifdm_cl/win/vmsWinRect.h"
#include "../common/vms_sifdm_cl/win/gdiplus/util.h"
#include "../common/vms_sifdm_cl/win/gdiutil.h"

CFdm5BannerWindow::CFdm5BannerWindow(
	std::function<void(bool offerAccepted)> onClose) :
	m_onClose(onClose)
{
	auto tryit = std::make_pair(CRect(265, 425, 533, 481), 
		[=]()
	{
		fsOpenUrlInBrowser(L"http://freedownloadmanager.org/landing.htm");
		_App.ShowFdm5Banner(FALSE);
		close(true);
	});
	m_mouseActions.push_back(tryit);

	auto nothanks = std::make_pair(CRect(303, 513, 368, 526),
		[=]()
	{
		_App.ShowFdm5Banner(FALSE);
		close(false);
	});
	m_mouseActions.push_back(nothanks);

	auto remindlater = std::make_pair(CRect(390, 513, 495, 526),
		[=] ()
	{
		close(false);
	});
	m_mouseActions.push_back(remindlater);
}

CFdm5BannerWindow::~CFdm5BannerWindow()
{
}

void CFdm5BannerWindow::Create(HWND parent)
{
	assert(m_imgBg);
	if (!m_imgBg)
		return;

	CRect rc(0, 0, m_imgBg->GetWidth (), m_imgBg->GetHeight ()); 

	CWindowImpl::Create(parent, rc);

	CenterWindow();

	UpdateLW();
}

void CFdm5BannerWindow::UpdateLW()
{
	HDC hdcScreen = ::GetDC(NULL);
	HDC hDC = CreateCompatibleDC(hdcScreen);
	HBITMAP hBmp = vmsCreateX32Bitmap(m_imgBg->GetWidth(), m_imgBg->GetHeight());
	HBITMAP hBmpOld = (HBITMAP)SelectObject(hDC, hBmp);

	Gdiplus::Graphics g(hDC);
	g.DrawImage(m_imgBg.get(), 0, 0, 0, 0, m_imgBg->GetWidth(), m_imgBg->GetHeight(),
		Gdiplus::UnitPixel);

	BLENDFUNCTION blend = {0};
	blend.BlendOp = AC_SRC_OVER;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;
	POINT ptSrc = {0, 0};
	RECT rc; GetWindowRect(&rc);
	POINT ptPos = {rc.left, rc.top};
	SIZE sizeWnd = {m_imgBg->GetWidth (), m_imgBg->GetHeight ()};
	UpdateLayeredWindow (m_hWnd, hdcScreen, &ptPos, &sizeWnd, hDC, &ptSrc, 0, &blend, ULW_ALPHA);

	SelectObject(hDC, hBmpOld);
	DeleteObject(hBmp);
	DeleteDC(hDC);
	::ReleaseDC(NULL, hdcScreen);
}

bool CFdm5BannerWindow::initialize()
{
	if (m_imgBg)
		return true;
	auto bgfile = vmsGetModulePath() + L"\\fdm5_banner.png";
	m_imgBg = std::make_unique<Gdiplus::Image>(bgfile.c_str());
	if (m_imgBg->GetLastStatus() != Gdiplus::Ok)
	{
		m_imgBg.reset();
		return false;
	}
	return true;
}

LRESULT CFdm5BannerWindow::OnLButtonUp(
	UINT uMsg, 
	WPARAM wParam, 
	LPARAM lParam, 
	BOOL& bHandled)
{
	auto x = LOWORD(lParam);
	auto y = HIWORD(lParam);

	auto action = mouseAction(CPoint(x,y));
	if (action)
		action();
	else
		close(false);

	return 0;
}

LRESULT CFdm5BannerWindow::OnDestroy(
	UINT uMsg, 
	WPARAM wParam, 
	LPARAM lParam, 
	BOOL& bHandled)
{
	_App.Fdm5BannerLastTime(std::time(nullptr));
	AfxGetMainWnd()->EndModalState();
	AfxGetMainWnd()->SetForegroundWindow();
	return 0;
}

LRESULT CFdm5BannerWindow::OnSetCursor(
	UINT uMsg, 
	WPARAM wParam, 
	LPARAM lParam, 
	BOOL& bHandled)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(&pt);
	auto action = mouseAction(pt);
	if (action)
		SetCursor(LoadCursor(nullptr, IDC_HAND));
	else
		SetCursor(LoadCursor(nullptr, IDC_ARROW));
	bHandled = TRUE;
	return 0;
}

CFdm5BannerWindow::mouse_action_t CFdm5BannerWindow::mouseAction(
	const POINT &pt)
{
	for (auto&& item : m_mouseActions)
	{
		if (PtInRect(&item.first, pt))
			return item.second;
	}
	return mouse_action_t();
}

void CFdm5BannerWindow::close(bool offerAccepted)
{
	DestroyWindow();
	if (m_onClose)
		m_onClose(offerAccepted);
}