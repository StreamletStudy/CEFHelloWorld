#pragma once

#include "AddressBar.h"
#include "PageHolder.h"

const int ID_BUTTON_BACK = 101;
const int ID_BUTTON_FORWARD = 102;

class MainFrame : public CWindowImpl<MainFrame>
{
public:
    static bool CreateAndNavigate(CefRefPtr<CefApp> pApp, const std::wstring &strUrl);

public:
    bool PopupAndNavigate(const std::wstring &strUrl);

private:
    MainFrame(CefRefPtr<CefApp> pApp, const std::wstring &strUrl) : m_App(pApp), m_strUrlOnCreate(strUrl)
    {
    }

public:
    void SetBrowser(CefRefPtr<CefBrowser> browser);

public:
    DECLARE_WND_CLASS(L"CEFMainFrame")

    BEGIN_MSG_MAP(MainFrame)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_CLOSE, OnClose)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
        MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBankground)
        MESSAGE_HANDLER(WM_CONTEXT_INITIALIZED, OnAppContextInitialized)
        MESSAGE_HANDLER(WM_ADDRESS_BAR_ENTERED, OnAddressBarEntered)
        COMMAND_HANDLER(ID_BUTTON_BACK, BN_CLICKED, OnBackClicked)
        COMMAND_HANDLER(ID_BUTTON_FORWARD, BN_CLICKED, OnForwardClicked)
    END_MSG_MAP()

    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
    virtual void OnFinalMessage(_In_ HWND /*hWnd*/) override;
    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
    LRESULT OnEraseBankground(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
    LRESULT OnAppContextInitialized(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
    LRESULT OnAddressBarEntered(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
    LRESULT OnBackClicked(WORD code, WORD id, HWND hControl, BOOL &bHandled);
    LRESULT OnForwardClicked(WORD code, WORD id, HWND hControl, BOOL &bHandled);

public:
    void OnAddressChange(const CefString& url);
    void OnTitleChange(const CefString& title);
    void OnLoadingStart(bool bCanBack, bool bCanForward);
    void OnLoadingProgressChange(double progress);

private:
    CefRefPtr<CefApp> m_App;
    CefRefPtr<CefClient> m_Client;
    CefRefPtr<CefBrowser> m_Browser;

    std::wstring m_strUrlOnCreate;

    CFont m_Font;
    AddressBar m_AddressBar;
    CButton m_Back;
    CButton m_Forward;
    CProgressBarCtrl m_ProgressBar;
    PageHolder m_PageHolder;

};
