#include "stdafx.h"
#include "AppBrowser.h"
#include "Client.h"

CefRefPtr<CefBrowserProcessHandler> AppBrowser::GetBrowserProcessHandler()
{
    return this;
}

void AppBrowser::OnContextInitialized()
{
    CefWindowInfo info;
    info.SetAsPopup(NULL, "CEF Window");

    CefRefPtr<CefClient> client(new Client());

    CefBrowserSettings browserSettings;

    CefString url = "https://www.streamlet.org/";
    CefBrowserHost::CreateBrowser(info, client, url, browserSettings, nullptr);
}
