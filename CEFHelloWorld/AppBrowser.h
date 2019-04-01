#pragma once

#include <set>

class MainFrame;
class AppBrowser : public CefApp, public CefBrowserProcessHandler
{
public:
    AppBrowser() : m_bInitialized(false)
    {
    }

public:
    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override;
    virtual void OnContextInitialized() override;

public:
    void OnMainFrameCreated(MainFrame *pMainFrame);
    void OnMainFrameDestroyed(MainFrame *pMainFrame);

private:
    bool m_bInitialized;
    std::set<MainFrame *> m_setMainFrames;

    IMPLEMENT_REFCOUNTING(AppBrowser);
};

