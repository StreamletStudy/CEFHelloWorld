#include "stdafx.h"
#include "AppRenderer.h"

CefRefPtr<CefRenderProcessHandler> AppRenderer::GetRenderProcessHandler()
{
    return this;
}

void AppRenderer::OnContextCreated(CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{

}
