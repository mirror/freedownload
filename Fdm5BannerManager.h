/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
class CFdm5BannerWindow;
class Fdm5BannerManager
{
public:
	Fdm5BannerManager();
	~Fdm5BannerManager();

	bool showBanner(std::function<void(bool offerAccepted)> onClose = {});
	bool bannerEnabled() const;
	bool bannerActive() const;

protected:
	std::unique_ptr<CFdm5BannerWindow> m_bannerWindow;
};

