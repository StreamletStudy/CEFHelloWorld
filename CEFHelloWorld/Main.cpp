#include "stdafx.h"
#include "App.h"
#include "AppBrowser.h"
#include "AppRenderer.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    CefMainArgs cefMainArgs(hInstance);
    CefRefPtr<CefCommandLine> cefCommandLine = CefCommandLine::CreateCommandLine();
    cefCommandLine->InitFromString(::GetCommandLine());

    CefRefPtr<CefApp> cefApp = nullptr;
    if (!cefCommandLine->HasSwitch("type"))
    {
        cefApp = new AppBrowser;
    }
    else
    {
        CefString strType = cefCommandLine->GetSwitchValue("type");
        if (strType == "renderer")
        {

            cefApp = new AppRenderer;
        }
        else
        {
            cefApp = new App;
        }
    }
    
    int nExitCode = CefExecuteProcess(cefMainArgs, cefApp, nullptr);
    if (nExitCode >= 0)
    {
        return nExitCode;
    }

    CefSettings cefSettings;
    cefSettings.no_sandbox = true;
    
    CefInitialize(cefMainArgs, cefSettings, cefApp, nullptr);

    CefRunMessageLoop();

    CefShutdown();

    return 0;
}
