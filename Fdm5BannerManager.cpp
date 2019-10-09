/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#include "stdafx.h"
#include "Fdm5BannerManager.h"
#include "Fdm5BannerWindow.h"
#include "../common/fdm5util.h"

Fdm5BannerManager::Fdm5BannerManager()
{
}

Fdm5BannerManager::~Fdm5BannerManager()
{
}

bool Fdm5BannerManager::showBanner(
	std::function<void(bool offerAccepted)> onClose)
{
	if (bannerActive())
		m_bannerWindow->DestroyWindow();
	
	m_bannerWindow = std::make_unique<CFdm5BannerWindow>(onClose);
	if (!m_bannerWindow->initialize())
		return false;

	auto mainWindow = AfxGetMainWnd();
	
	mainWindow->BeginModalState();

	m_bannerWindow->Create(mainWindow->m_hWnd);
	m_bannerWindow->ShowWindow(SW_SHOW);
	m_bannerWindow->BringWindowToTop();
	m_bannerWindow->SetFocus();

	return true;
}

bool Fdm5BannerManager::bannerEnabled() const
{
	vmsWinOsVersion ver;
	if (!ver.isWin7OrHigher())
		return false;
	return _App.ShowFdm5Banner() != FALSE && 
		!fdm5installed();
}

bool Fdm5BannerManager::bannerActive() const
{
	return m_bannerWindow && 
		m_bannerWindow->IsWindow();
}