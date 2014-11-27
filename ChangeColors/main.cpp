#include "main.h"

COLORREF  __stdcall MyTextColor(HDC hdc, COLORREF crColor)
{
    srand (time(NULL));
    DWORD colorBuf = rand();

    return SetTextColor(hdc, colorBuf);
}

BOOL WINAPI DllMain (HANDLE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
 
    return TRUE;
}
 

