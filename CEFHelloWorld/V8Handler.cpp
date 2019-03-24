#include "stdafx.h"
#include "V8Handler.h"
#include "MainFrame.h"

bool V8Handler::Execute(const CefString& name,
    CefRefPtr<CefV8Value> object,
    const CefV8ValueList& arguments,
    CefRefPtr<CefV8Value>& retval,
    CefString& exception)
{
    if (name == FUNCTION_NAMES[FUNCTION_ABOUT])
    {
        HWND hModalOwner = FindWindow(MainFrame::GetWndClassInfo().m_wc.lpszClassName, nullptr);
        ::MessageBox(hModalOwner, L"这是一只使用 CEF 框架写的浏览器。", L"关于", MB_OK | MB_ICONINFORMATION);
        return true;
    }
    else if (name == FUNCTION_NAMES[FUNCTION_SUM])
    {
        double result = 0.0;
        for (auto argument : arguments)
        {
            result += argument->GetDoubleValue();
        }
        retval = CefV8Value::CreateDouble(result);
        return true;
    }

    return false;
}
