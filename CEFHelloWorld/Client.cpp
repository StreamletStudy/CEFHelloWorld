#include "stdafx.h"
#include "res/resource.h"
#include "Client.h"


CefRefPtr<CefLifeSpanHandler> Client::GetLifeSpanHandler()
{
    return this;
}

bool Client::OnBeforePopup(CefRefPtr<CefBrowser> browser,
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
    bool* no_javascript_access)
{
    switch (target_disposition)
    {
    case WOD_NEW_FOREGROUND_TAB:
    case WOD_NEW_BACKGROUND_TAB:
    case WOD_NEW_POPUP:
    case WOD_NEW_WINDOW:
        m_pMainFrame->PopupAndNavigate(target_url);
        return true; //cancel create
    }

    return false;
}

void Client::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
    m_pMainFrame->SetBrowser(browser);
}

void Client::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
    m_pMainFrame->SetBrowser(nullptr);
    m_pMainFrame->SendMessage(WM_CLOSE);
}

CefRefPtr<CefContextMenuHandler> Client::GetContextMenuHandler()
{
    return this;
}

void Client::OnBeforeContextMenu(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
    CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model)
{
    if ((params->GetTypeFlags() & (CM_TYPEFLAG_PAGE | CM_TYPEFLAG_FRAME)) != 0)
    {
        if (model->GetCount() > 0)
        {
            model->Clear();
        }
    }
}

CefRefPtr<CefLoadHandler> Client::GetLoadHandler()
{
    return this;
}

void Client::OnLoadingStateChange(CefRefPtr<CefBrowser> browser,
    bool isLoading, bool canGoBack, bool canGoForward)
{
    m_pMainFrame->OnLoadingStart(canGoBack, canGoForward);
}

void Client::OnLoadEnd(CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame, int httpStatusCode)
{
    if (frame->IsMain())
    {
        HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(IDR_JS), L"JS");
        assert(hRes != nullptr);
        HGLOBAL hGlobal = LoadResource(NULL, hRes);
        assert(hGlobal != nullptr);
        DWORD dwSize = SizeofResource(NULL, hRes);
        assert(dwSize != 0);
        LPCWSTR p = (LPCWSTR)LockResource(hGlobal);
        assert(p != nullptr);
        CefString strScript;
        strScript.FromString(p + 1, dwSize / 2 - 1, false);

        frame->ExecuteJavaScript(strScript, frame->GetURL(), 0);
    }
}

CefRefPtr<CefDisplayHandler> Client::GetDisplayHandler()
{
    return this;
}

void Client::OnAddressChange(CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame, const CefString& url)
{
    m_pMainFrame->OnAddressChange(url);
}

void Client::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title)
{
    m_pMainFrame->OnTitleChange(title);
}

void Client::OnLoadingProgressChange(CefRefPtr<CefBrowser> browser, double progress)
{
    m_pMainFrame->OnLoadingProgressChange(progress);
}

CefRefPtr<CefKeyboardHandler> Client::GetKeyboardHandler()
{
    return this;
}

bool Client::OnKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& event, CefEventHandle os_event)
{
    if (event.type != KEYEVENT_KEYUP || event.windows_key_code != VK_F12)
    {
        return false;
    }

    if (browser->GetHost()->HasDevTools())
    {
        return false;
    }

    CefWindowInfo window_info;
    window_info.SetAsPopup(browser->GetHost()->GetWindowHandle(), L"DevTools");

    RECT rect = {};
    ::GetWindowRect(browser->GetHost()->GetWindowHandle(), &rect);
    window_info.width = max(rect.right - rect.left, 800);
    window_info.height = max(rect.bottom - rect.top, 600);

    if (m_DevToolsClient == nullptr)
    {
        m_DevToolsClient = new ClientDevTools();
    }

    CefBrowserSettings settings;
    browser->GetHost()->ShowDevTools(window_info, m_DevToolsClient, settings, CefPoint());

    return true;
}
