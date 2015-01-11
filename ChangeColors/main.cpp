#include "main.h"
#include <map>
using namespace std;

map<DWORD,DWORD> g_IndexToColor;

COLORREF  __stdcall MyTextColor(HDC hdc, COLORREF crColor)
{
    srand (time(NULL));
    DWORD colorBuf = rand();

    return SetTextColor(hdc, colorBuf);
}

void readColors()
{
    FILE *fp = fopen("colors.cfg", "r");
    if (fp == NULL) return;

    const size_t strSize = 101;
    char mystring[strSize];
    DWORD index = 0;
    DWORD color = 0;

    while (!feof(fp)) {

        if (fgets (mystring , strSize - 1 , fp) == NULL) continue;

        sscanf(mystring, "%d:%x", &index, &color);

        DWORD red = (color & 0xFF0000) >> 16;
        DWORD green = (color & 0x00FF00) >> 8;
        DWORD blue = (color & 0x0000FF);

        color = RGB(red, green, blue);
        g_IndexToColor[index] = color;
    }
    fclose(fp);
    return;
}

COLORREF __stdcall MySysColor(int nIndex)
{
    if (g_IndexToColor.find(nIndex) != g_IndexToColor.end()) {
        return g_IndexToColor[nIndex];
    }
    return GetSysColor(nIndex);
}

BOOL WINAPI DllMain (HANDLE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            {
                readColors();
                break;
            }
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;   
    }
 
    return TRUE;
}
 

