/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
class CFdm5BannerWindow :
	public CWindowImpl<CFdm5BannerWindow, CWindow, 
		CWinTraits<WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, WS_EX_LAYERED | WS_EX_TOOLWINDOW>>
{
public:
	CFdm5BannerWindow(
		std::function<void(bool offerAccepted)> onClose = {});
	~CFdm5BannerWindow();

	bool initialize();

	void Create(HWND parent);

	DECLARE_WND_CLASS(NULL)

	BEGIN_MSG_MAP(CFdm5BannerWindow)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
	END_MSG_MAP()

protected:
	using mouse_action_t = std::function<void()>;
	void UpdateLW();
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	mouse_action_t mouseAction(const POINT &pt);
	void close(bool offerAccepted);

protected:
	std::unique_ptr<Gdiplus::Image> m_imgBg;
	std::function<void(bool offerAccepted)> m_onClose;
	std::vector<std::pair<RECT, mouse_action_t>> m_mouseActions;
};

