#pragma once 

#include <Windows.h>
#include <WinInet.h>

#pragma comment(lib, "Wininet.lib")

extern "C" {

HINTERNET __declspec(dllexport) __stdcall _httpOpenRequestA(
    _In_ HINTERNET hConnect,
    _In_opt_ LPCSTR lpszVerb,
    _In_opt_ LPCSTR lpszObjectName,
    _In_opt_ LPCSTR lpszVersion,
    _In_opt_ LPCSTR lpszReferrer,
    _In_opt_z_ LPCSTR FAR * lplpszAcceptTypes,
    _In_ DWORD dwFlags,
    _In_opt_ DWORD_PTR dwContext
    );

HINTERNET __declspec(dllexport) __stdcall _httpOpenRequestW(
    _In_ HINTERNET hConnect,
    _In_opt_ LPCWSTR lpszVerb,
    _In_opt_ LPCWSTR lpszObjectName,
    _In_opt_ LPCWSTR lpszVersion,
    _In_opt_ LPCWSTR lpszReferrer,
    _In_opt_z_ LPCWSTR FAR * lplpszAcceptTypes,
    _In_ DWORD dwFlags,
    _In_opt_ DWORD_PTR dwContext
    );
};