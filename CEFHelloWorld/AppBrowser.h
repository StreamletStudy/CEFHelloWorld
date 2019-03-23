#pragma once

class AppBrowser : public CefApp, public CefBrowserProcessHandler
{
    IMPLEMENT_REFCOUNTING(AppBrowser);

public:
    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override;
    virtual void OnContextInitialized() override;
};

