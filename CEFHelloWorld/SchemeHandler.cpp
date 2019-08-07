#include "stdafx.h"
#include "res/resource.h"
#include "SchemeHandler.h"

CefRefPtr<CefResourceHandler> SchemeHandlerFactory::Create(CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame, const CefString& scheme_name, CefRefPtr<CefRequest> request)
{
    return new ResourceHandler;
}

ResourceHandler::ResourceHandler() : m_lpszHomepage(nullptr), m_dwSize(0), m_dwSizeRead(0)
{
    HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(IDR_HOMEPAGE), RT_HTML);
    assert(hRes != nullptr);
    HGLOBAL hGlobal = LoadResource(NULL, hRes);
    assert(hGlobal != nullptr);
    m_dwSize = SizeofResource(NULL, hRes);
    assert(m_dwSize != 0);
    m_lpszHomepage = (LPCSTR)LockResource(hGlobal);
    assert(m_lpszHomepage != nullptr);
}

bool ResourceHandler::Open(CefRefPtr<CefRequest> request, bool& handle_request, CefRefPtr<CefCallback> callback)
{
    m_dwSizeRead = 0;
    handle_request = true;
    return true;
}

void ResourceHandler::GetResponseHeaders(CefRefPtr<CefResponse> response, int64& response_length, CefString& redirectUrl)
{
    response->SetStatus(200);
    response->SetMimeType(L"text/html");
    response_length = m_dwSize;
}

void ResourceHandler::Cancel()
{

}

bool ResourceHandler::Read(void* data_out, int bytes_to_read, int& bytes_read, CefRefPtr<CefResourceReadCallback> callback)
{
    bytes_read = min(m_dwSize - m_dwSizeRead, (DWORD)bytes_to_read);
    memcpy(data_out, m_lpszHomepage, bytes_read);
    m_dwSizeRead += bytes_read;
    return true;
}
