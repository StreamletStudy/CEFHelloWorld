#include "stdafx.h"
#include "App.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    CefMainArgs cefMainArgs(hInstance);
    int nExitCode = CefExecuteProcess(cefMainArgs, nullptr, nullptr);
    if (nExitCode >= 0)
    {
        return nExitCode;
    }

    CefSettings cefSettings;
    cefSettings.no_sandbox = true;

    CefRefPtr<CefApp> cefApp = new App();

    CefInitialize(cefMainArgs, cefSettings, cefApp, nullptr);

    CefRunMessageLoop();

    CefShutdown();

    return 0;
}
