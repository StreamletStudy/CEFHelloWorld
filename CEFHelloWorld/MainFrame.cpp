#include "stdafx.h"
#include "AppBrowser.h"
#include "MainFrame.h"
#include "Client.h"

const int ADDRESS_BAR_HEIGHT = 36;
const int ADDRESS_BAR_MARGIN = 10;
const int NAVIGATE_BUTTON_WIDTH = 40;
const int PROGRESS_BAR_HEIGHT = 4;

bool MainFrame::CreateAndNavigate(CefRefPtr<CefApp> pApp, const std::wstring &strUrl)
{
    MainFrame *pMainFrame = new MainFrame(pApp, strUrl);

    CRect rcWindow(CW_USEDEFAULT, CW_USEDEFAULT, 0, 0);
    HWND hWnd = pMainFrame->Create(nullptr, &rcWindow, L"CEF Browser", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE);
    assert(hWnd != nullptr);
    return true;
}

bool MainFrame::PopupAndNavigate(const std::wstring &strUrl)
{
    return CreateAndNavigate(m_App, strUrl);
}

void MainFrame::SetBrowser(CefRefPtr<CefBrowser> browser)
{
    m_Browser = browser;
}

LRESULT MainFrame::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
    CRect rcDummy(CW_USEDEFAULT, CW_USEDEFAULT, 0, 0);

    m_Back.Create(m_hWnd, &rcDummy, L"<", WS_CHILD | WS_VISIBLE | BS_FLAT, 0L, ID_BUTTON_BACK);
    m_Forward.Create(m_hWnd, &rcDummy, L">", WS_CHILD | WS_VISIBLE | BS_FLAT, 0L, ID_BUTTON_FORWARD);

    m_AddressBar.Create(m_hWnd, &rcDummy, nullptr, WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | ES_WANTRETURN);
    
    m_ProgressBar.Create(m_hWnd, &rcDummy, nullptr, WS_CHILD | WS_VISIBLE | PBS_SMOOTH);
    m_ProgressBar.ModifyStyleEx(WS_EX_STATICEDGE, 0);
    m_ProgressBar.SetRange(0, 100);
    m_ProgressBar.SetBarColor(RGB(0, 0x80, 0));

    m_PageHolder.Create(m_hWnd, &rcDummy, nullptr, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

    m_Font.CreateFont(-24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Consolas");
    SetFont(m_Font);
    m_AddressBar.SetFont(m_Font);
    m_PageHolder.SetFont(m_Font);

    dynamic_cast<AppBrowser *>(m_App.get())->OnMainFrameCreated(this);

    return 0;
}

void MainFrame::OnFinalMessage(_In_ HWND /*hWnd*/)
{
    dynamic_cast<AppBrowser *>(m_App.get())->OnMainFrameDestroyed(this);
}

LRESULT MainFrame::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
    if (m_Browser != nullptr)
    {
        m_PageHolder.SendMessage(WM_CLOSE);
        bHandled = TRUE;
    }
    else
    {
        bHandled = FALSE;
    }
    return 0;
}

LRESULT MainFrame::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
    CRect rect;
    GetClientRect(rect);

    CRect rcButton = rect;
    rcButton.bottom = rcButton.top + ADDRESS_BAR_HEIGHT;
    rcButton.DeflateRect(ADDRESS_BAR_MARGIN, 0);
    rcButton.right = rcButton.left + NAVIGATE_BUTTON_WIDTH;
    m_Back.MoveWindow(&rcButton);
    m_Back.EnableWindow(FALSE);

    rcButton.OffsetRect(NAVIGATE_BUTTON_WIDTH - 1, 0);
    m_Forward.MoveWindow(&rcButton);
    m_Forward.EnableWindow(FALSE);

    CRect rcAddressBar = rect;
    rcAddressBar.bottom = rcAddressBar.top + ADDRESS_BAR_HEIGHT;
    rcAddressBar.left = rcButton.right;
    rcAddressBar.DeflateRect(ADDRESS_BAR_MARGIN, 0);
    m_AddressBar.MoveWindow(&rcAddressBar);

    CRect rcProgressBar = rect;
    rcProgressBar.top = rcAddressBar.bottom;
    rcProgressBar.bottom = rcProgressBar.top + PROGRESS_BAR_HEIGHT;
    rcProgressBar.left = rcButton.right;
    rcProgressBar.DeflateRect(ADDRESS_BAR_MARGIN, 0);
    m_ProgressBar.MoveWindow(&rcProgressBar);

    CRect rcPageHolder = rect;
    rcPageHolder.top = rcProgressBar.bottom;
    m_PageHolder.MoveWindow(&rcPageHolder);

    if (m_Browser != nullptr) {
        ::MoveWindow(m_Browser->GetHost()->GetWindowHandle(), 0, 0, rcPageHolder.Width(), rcPageHolder.Height(), TRUE);
    }

    return 0;
}

LRESULT MainFrame::OnEraseBankground(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
    return TRUE;
}

LRESULT MainFrame::OnAppContextInitialized(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
    CRect rect;
    m_PageHolder.GetClientRect(&rect);

    CefWindowInfo info;
    info.SetAsChild(m_PageHolder, rect);

    m_Client = new Client(this);

    CefBrowserSettings browserSettings;
    CefBrowserHost::CreateBrowser(info, m_Client, m_strUrlOnCreate, browserSettings, nullptr, nullptr);

    return 0;
}

LRESULT MainFrame::OnAddressBarEntered(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
    CString url;
    m_AddressBar.GetWindowText(url);
    m_Browser->GetMainFrame()->LoadURL((LPCTSTR)url);

    return 0;
}

LRESULT MainFrame::OnBackClicked(WORD code, WORD id, HWND hControl, BOOL &bHandled)
{
    m_Browser->GoBack();
    return 0;
}

LRESULT MainFrame::OnForwardClicked(WORD code, WORD id, HWND hControl, BOOL &bHandled)
{
    m_Browser->GoForward();
    return 0;
}

void MainFrame::OnAddressChange(const CefString& url)
{
    m_AddressBar.SetWindowText(url.c_str());
}

void MainFrame::OnTitleChange(const CefString& title)
{
    SetWindowText(title.c_str());
}

void MainFrame::OnLoadingStart(bool bCanBack, bool bCanForward)
{
    m_Back.EnableWindow(bCanBack);
    m_Forward.EnableWindow(bCanForward);
}

void MainFrame::OnLoadingProgressChange(double progress)
{
    m_ProgressBar.SetPos((int)(progress * 100));
}
