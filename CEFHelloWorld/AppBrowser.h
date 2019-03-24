#pragma once

#include "MainFrame.h"

class AppBrowser : public CefApp, public CefBrowserProcessHandler
{
public:
    AppBrowser(MainFrame *pMainFrame) : m_pMainFrame(pMainFrame)
    {
    }

public:
    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override;
    virtual void OnContextInitialized() override;

private:
    MainFrame *m_pMainFrame;
    CefRefPtr<CefClient> m_Client;

    IMPLEMENT_REFCOUNTING(AppBrowser);
};

