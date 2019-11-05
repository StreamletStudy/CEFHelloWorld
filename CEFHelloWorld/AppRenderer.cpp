#include "stdafx.h"
#include "AppRenderer.h"
#include "V8Handler.h"

CefRefPtr<CefRenderProcessHandler> AppRenderer::GetRenderProcessHandler()
{
    return this;
}

void AppRenderer::OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar)
{
    registrar->AddCustomScheme(L"res", CEF_SCHEME_OPTION_STANDARD | CEF_SCHEME_OPTION_SECURE | CEF_SCHEME_OPTION_CORS_ENABLED | CEF_SCHEME_OPTION_FETCH_ENABLED);
}

void AppRenderer::OnContextCreated(CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
    CefRefPtr<CefV8Value> object = context->GetGlobal();

    auto v8Handler = new V8Handler;
    for (LPCTSTR lpszFunc : v8Handler->FUNCTION_NAMES)
    {
        CefRefPtr<CefV8Value> func = CefV8Value::CreateFunction(lpszFunc, v8Handler);
        object->SetValue(lpszFunc, func, V8_PROPERTY_ATTRIBUTE_NONE);
    }
}
