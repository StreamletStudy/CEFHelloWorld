#include "stdafx.h"
#include "Client.h"

CefRefPtr<CefLifeSpanHandler> Client::GetLifeSpanHandler()
{
    return this;
}

void Client::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
    CefQuitMessageLoop();
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
