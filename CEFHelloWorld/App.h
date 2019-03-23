#pragma once

class App : public CefApp, public CefBrowserProcessHandler
{
    IMPLEMENT_REFCOUNTING(App);

public:
    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override;
    virtual void OnContextInitialized() override;
};

