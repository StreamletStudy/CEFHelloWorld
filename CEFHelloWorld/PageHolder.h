#pragma once

class PageHolder : public CWindowImpl<PageHolder>
{
public:
    DECLARE_WND_CLASS(L"CEFPageHolder")

    BEGIN_MSG_MAP(PageHolder)
        MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBankground)
    END_MSG_MAP()

    LRESULT OnEraseBankground(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
};
