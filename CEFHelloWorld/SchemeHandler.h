#pragma once

class SchemeHandlerFactory : public CefSchemeHandlerFactory
{
public:
    virtual CefRefPtr<CefResourceHandler> Create(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame, const CefString& scheme_name, CefRefPtr<CefRequest> request) override;

    IMPLEMENT_REFCOUNTING(SchemeHandlerFactory);
};

class ResourceHandler : public CefResourceHandler
{
public:
    ResourceHandler();

public:
    virtual bool Open(CefRefPtr<CefRequest> request, bool& handle_request, CefRefPtr<CefCallback> callback) override;
    virtual void GetResponseHeaders(CefRefPtr<CefResponse> response, int64& response_length, CefString& redirectUrl) override;
    virtual bool Read(void* data_out, int bytes_to_read, int& bytes_read, CefRefPtr<CefResourceReadCallback> callback) override;
    virtual void Cancel() override;

    IMPLEMENT_REFCOUNTING(ResourceHandler);

private:
    LPCSTR m_lpszHomepage;
    DWORD m_dwSize;
    DWORD m_dwSizeRead;
};
