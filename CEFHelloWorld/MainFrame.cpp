#include "stdafx.h"
#include "MainFrame.h"

const int ADDRESS_BAR_HEIGHT = 36;
const int ADDRESS_BAR_MARGIN = 10;
const int PROGRESS_BAR_HEIGHT = 6;

bool MainFrame::Create()
{
    CRect rcWindow(CW_USEDEFAULT, CW_USEDEFAULT, 0, 0);
    HWND hWnd = CWindowImpl<MainFrame>::Create(nullptr, &rcWindow, L"CEF Browser", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE);
    assert(hWnd != nullptr);
    return true;
}

HWND MainFrame::GetPageHolder()
{
    return m_PageHolder;
}

void MainFrame::SetClient(CefRefPtr<CefClient> client)
{
    m_Client = client;
}

void MainFrame::SetBrowser(CefRefPtr<CefBrowser> browser)
{
    m_Browser = browser;
}

LRESULT MainFrame::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
    CRect rect;
    GetClientRect(rect);

    CRect rcAddressBar = rect;
    rcAddressBar.bottom = rcAddressBar.top + ADDRESS_BAR_HEIGHT;
    rcAddressBar.DeflateRect(ADDRESS_BAR_MARGIN, 0);
    m_AddressBar.Create(m_hWnd, &rcAddressBar, nullptr, WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | ES_WANTRETURN);
    
    CRect rcProgressBar = rect;
    rcProgressBar.top = rcAddressBar.bottom;
    rcProgressBar.bottom = rcProgressBar.top + PROGRESS_BAR_HEIGHT;
    rcProgressBar.DeflateRect(ADDRESS_BAR_MARGIN, 0);
    m_ProgressBar.Create(m_hWnd, &rcProgressBar, nullptr, WS_CHILD | WS_VISIBLE | PBS_SMOOTH);
    m_ProgressBar.ModifyStyleEx(WS_EX_STATICEDGE, 0);
    m_ProgressBar.SetRange(0, 100);
    m_ProgressBar.SetBarColor(RGB(0, 0x80, 0));

    CRect rcPageHolder = rect;
    rcPageHolder.top = rcProgressBar.bottom;
    m_PageHolder.Create(m_hWnd, &rcPageHolder, nullptr, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

    m_Font.CreateFont(-24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Consolas");
    SetFont(m_Font);
    m_AddressBar.SetFont(m_Font);
    m_PageHolder.SetFont(m_Font);

    return 0;
}

LRESULT MainFrame::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
    CefQuitMessageLoop();
    return 0;
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

    CRect rcAddressBar = rect;
    rcAddressBar.bottom = rcAddressBar.top + ADDRESS_BAR_HEIGHT;
    rcAddressBar.DeflateRect(ADDRESS_BAR_MARGIN, 0);
    m_AddressBar.MoveWindow(&rcAddressBar);

    CRect rcProgressBar = rect;
    rcProgressBar.top = rcAddressBar.bottom;
    rcProgressBar.bottom = rcProgressBar.top + PROGRESS_BAR_HEIGHT;
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

LRESULT MainFrame::OnAddressBarEntered(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
    CString url;
    m_AddressBar.GetWindowText(url);
    m_Browser->GetMainFrame()->LoadURL((LPCTSTR)url);

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

void MainFrame::OnLoadingProgressChange(double progress)
{
    m_ProgressBar.SetPos((int)(progress * 100));
}
