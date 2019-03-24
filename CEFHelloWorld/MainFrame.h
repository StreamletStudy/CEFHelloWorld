#pragma once

#include "AddressBar.h"
#include "PageHolder.h"

class MainFrame : public CWindowImpl<MainFrame>
{
public:
    bool Create();
    HWND GetPageHolder();
    void SetClient(CefRefPtr<CefClient> client);
    void SetBrowser(CefRefPtr<CefBrowser> browser);

public:
    DECLARE_WND_CLASS(L"CEFMainFrame")

    BEGIN_MSG_MAP(MainFrame)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        MESSAGE_HANDLER(WM_CLOSE, OnClose)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
        MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBankground)
        MESSAGE_HANDLER(WM_ADDRESS_BAR_ENTERED, OnAddressBarEntered)
    END_MSG_MAP()

    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
    LRESULT OnEraseBankground(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
    LRESULT OnAddressBarEntered(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);

public:
    void OnAddressChange(const CefString& url);
    void OnTitleChange(const CefString& title);
    void OnLoadingProgressChange(double progress);

private:
    CFont m_Font;
    AddressBar m_AddressBar;
    CProgressBarCtrl m_ProgressBar;
    PageHolder m_PageHolder;

    CefRefPtr<CefClient> m_Client;
    CefRefPtr<CefBrowser> m_Browser;
};
