#include "stdafx.h"
#include "AppBrowser.h"
#include "MainFrame.h"

CefRefPtr<CefBrowserProcessHandler> AppBrowser::GetBrowserProcessHandler()
{
    return this;
}

void AppBrowser::OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar)
{
    registrar->AddCustomScheme(L"res", CEF_SCHEME_OPTION_STANDARD | CEF_SCHEME_OPTION_SECURE | CEF_SCHEME_OPTION_CORS_ENABLED | CEF_SCHEME_OPTION_FETCH_ENABLED);
}

void AppBrowser::OnContextInitialized()
{
    m_bInitialized = true;
    for (auto pMainFrame : m_setMainFrames)
    {
        pMainFrame->PostMessage(WM_CONTEXT_INITIALIZED);
    }
}

void AppBrowser::OnMainFrameCreated(MainFrame *pMainFrame)
{
    m_setMainFrames.insert(pMainFrame);
    if (m_bInitialized)
    {
        pMainFrame->PostMessage(WM_CONTEXT_INITIALIZED);
    }
}

void AppBrowser::OnMainFrameDestroyed(MainFrame *pMainFrame)
{
    m_setMainFrames.erase(pMainFrame);
    delete pMainFrame;

    if (m_setMainFrames.empty())
    {
        CefQuitMessageLoop();
    }
}
