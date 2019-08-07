#pragma once

class V8Handler : public CefV8Handler
{
public:
    enum FUNCTIONS
    {
        FUNCTION_ABOUT,
        FUNCTION_SUM,

        FUNCTION_COUNT,
    };
    LPCTSTR const FUNCTION_NAMES[FUNCTION_COUNT] =
    {
        L"about",
        L"sum",
    };

public:
    virtual bool Execute(const CefString& name,
        CefRefPtr<CefV8Value> object,
        const CefV8ValueList& arguments,
        CefRefPtr<CefV8Value>& retval,
        CefString& exception) override;

    IMPLEMENT_REFCOUNTING(V8Handler);
};
