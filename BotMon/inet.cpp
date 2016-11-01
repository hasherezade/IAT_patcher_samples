#include "inet.h"
#include "logger.h"

HINTERNET __declspec(dllexport) __stdcall _httpOpenRequestA(
    _In_ HINTERNET hConnect,
    _In_opt_ LPCSTR lpszVerb,
    _In_opt_ LPCSTR lpszObjectName,
    _In_opt_ LPCSTR lpszVersion,
    _In_opt_ LPCSTR lpszReferrer,
    _In_opt_z_ LPCSTR FAR * lplpszAcceptTypes,
    _In_ DWORD dwFlags,
    _In_opt_ DWORD_PTR dwContext
    )
{
    if (lpszVerb) Logger::append("[HTTP][verb] %S", lpszVerb);
    if (lpszVersion) Logger::append("[HTTP][vers] %S", lpszVersion);
    if (lpszObjectName) Logger::append("[HTTP][obj ] %S", lpszObjectName);

    HINTERNET res = HttpOpenRequestA(hConnect, lpszVerb, lpszObjectName, lpszVersion, lpszReferrer, lplpszAcceptTypes, dwFlags, dwContext);
    if (res == FALSE) {
        Logger::append("[HTTP] Failed");
    }
    return res;
}

HINTERNET __declspec(dllexport) __stdcall _httpOpenRequestW(
    _In_ HINTERNET hConnect,
    _In_opt_ LPCWSTR lpszVerb,
    _In_opt_ LPCWSTR lpszObjectName,
    _In_opt_ LPCWSTR lpszVersion,
    _In_opt_ LPCWSTR lpszReferrer,
    _In_opt_z_ LPCWSTR FAR * lplpszAcceptTypes,
    _In_ DWORD dwFlags,
    _In_opt_ DWORD_PTR dwContext
    )
{
    if (lpszVerb) Logger::append("[HTTP][verb] %S", lpszVerb);
    if (lpszVersion) Logger::append("[HTTP][vers] %S", lpszVersion);
    if (lpszObjectName) Logger::append("[HTTP][obj ] %S", lpszObjectName);

    HINTERNET res = HttpOpenRequestW(hConnect, lpszVerb, lpszObjectName, lpszVersion, lpszReferrer, lplpszAcceptTypes, dwFlags, dwContext);
    if (res == FALSE) {
        Logger::append("[HTTP] Failed");
    }
    return res;
}