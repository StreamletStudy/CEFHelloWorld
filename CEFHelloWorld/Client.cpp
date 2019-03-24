#include "stdafx.h"
#include "Client.h"
#include "resource.h"

CefRefPtr<CefLifeSpanHandler> Client::GetLifeSpanHandler()
{
    return this;
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
