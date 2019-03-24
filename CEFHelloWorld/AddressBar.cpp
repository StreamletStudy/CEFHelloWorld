#include "stdafx.h"
#include "AddressBar.h"

LRESULT AddressBar::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
    if (wParam == VK_RETURN)
    {
        ::PostMessage(GetParent(), WM_ADDRESS_BAR_ENTERED, 0, 0L);
    }
    else
    {
        bHandled = FALSE;
    }

    return 0;
}
