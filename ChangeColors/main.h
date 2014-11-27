#include <windows.h>
#include <stdio.h>
#include <time.h>

extern "C" {
    COLORREF  __declspec(dllexport) __stdcall MyTextColor(HDC hdc, COLORREF crColor);
};
