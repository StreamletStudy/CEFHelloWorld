#pragma once

class AddressBar : public CWindowImpl<AddressBar, CEdit>
{
public:
    DECLARE_WND_CLASS(L"CEFAddressBar")

    BEGIN_MSG_MAP(AddressBar)
        MESSAGE_HANDLER(WM_CHAR, OnKeyDown)
    END_MSG_MAP()

    LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
};
