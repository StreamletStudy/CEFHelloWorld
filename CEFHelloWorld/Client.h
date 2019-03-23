#pragma once

class Client: public CefClient, public CefLifeSpanHandler, public CefContextMenuHandler
{
    IMPLEMENT_REFCOUNTING(Client)

public:
    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;
    virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

    virtual CefRefPtr<CefContextMenuHandler> GetContextMenuHandler() override;
    virtual void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
        CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model) override;
};
