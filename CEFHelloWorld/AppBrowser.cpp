#include "stdafx.h"
#include "AppBrowser.h"
#include "Client.h"
#include "MainFrame.h"

CefRefPtr<CefBrowserProcessHandler> AppBrowser::GetBrowserProcessHandler()
{
    return this;
}

void AppBrowser::OnContextInitialized()
{
    HWND hWndHolder = m_pMainFrame->GetPageHolder();
    CRect rect;
    ::GetClientRect(hWndHolder, &rect);

    CefWindowInfo info;
    info.SetAsChild(hWndHolder, rect);

    m_Client = new Client(m_pMainFrame);

    CefBrowserSettings browserSettings;

    CefString url = L"about:blank";
    CefBrowserHost::CreateBrowser(info, m_Client, url, browserSettings, nullptr);

    m_pMainFrame->SetClient(m_Client);
}
