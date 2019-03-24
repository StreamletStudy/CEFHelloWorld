#pragma once

#include "MainFrame.h"

class Client:
    public CefClient,
    public CefLifeSpanHandler,
    public CefContextMenuHandler,
    public CefLoadHandler,
    public CefDisplayHandler
{
public:
    Client(MainFrame *pMainFrame) : m_pMainFrame(pMainFrame)
    {
    }

public:
    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;
    virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
    virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

    virtual CefRefPtr<CefContextMenuHandler> GetContextMenuHandler() override;
    virtual void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
        CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model) override;

    virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override;
    virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame, int httpStatusCode) override;

    virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() override;
    virtual void OnAddressChange(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame, const CefString& url)override;

private:
    MainFrame *m_pMainFrame;

    IMPLEMENT_REFCOUNTING(Client)
};
