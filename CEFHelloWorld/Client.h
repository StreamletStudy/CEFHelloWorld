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
    virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        const CefString& target_url,
        const CefString& target_frame_name,
        WindowOpenDisposition target_disposition,
        bool user_gesture,
        const CefPopupFeatures& popupFeatures,
        CefWindowInfo& windowInfo,
        CefRefPtr<CefClient>& client,
        CefBrowserSettings& settings,
        CefRefPtr<CefDictionaryValue>& extra_info,
        bool* no_javascript_access) override;
    virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
    virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

    virtual CefRefPtr<CefContextMenuHandler> GetContextMenuHandler() override;
    virtual void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
        CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model) override;

    virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override;
    virtual void OnLoadingStateChange(CefRefPtr<CefBrowser> browser,
        bool isLoading, bool canGoBack, bool canGoForward) override;
    virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame, int httpStatusCode) override;

    virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() override;
    virtual void OnAddressChange(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame, const CefString& url)override;
    virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) override;
    virtual void OnLoadingProgressChange(CefRefPtr<CefBrowser> browser, double progress) override;

private:
    MainFrame *m_pMainFrame;

    IMPLEMENT_REFCOUNTING(Client);
};
