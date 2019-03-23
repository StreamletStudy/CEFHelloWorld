#pragma once

class AppRenderer : public CefApp, public CefRenderProcessHandler
{
    IMPLEMENT_REFCOUNTING(AppRenderer);

public:

    virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override;
    virtual void OnContextCreated(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) override;
};

