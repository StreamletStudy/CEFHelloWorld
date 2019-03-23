#include "stdafx.h"
#include "App.h"
#include "Client.h"

CefRefPtr<CefBrowserProcessHandler> App::GetBrowserProcessHandler()
{
    return this;
}

void App::OnContextInitialized()
{
    CefWindowInfo info;
    info.SetAsPopup(NULL, "CEF Window");

    CefRefPtr<CefClient> client(new Client());

    CefBrowserSettings browserSettings;

    CefString url = "https://www.streamlet.org/";
    CefBrowserHost::CreateBrowser(info, client, url, browserSettings, nullptr);
}
