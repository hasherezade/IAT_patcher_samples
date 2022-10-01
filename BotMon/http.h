#pragma once 

#include <windows.h>
#include <winhttp.h>

#pragma comment(lib, "WinHttp.lib")

#define BOTMON_API __declspec(dllexport)

extern "C" {

    HINTERNET BOTMON_API __stdcall _winHttpConnect(
        IN HINTERNET hSession,
        IN LPCWSTR pswzServerName,
        IN INTERNET_PORT nServerPort,
        _Reserved_ DWORD dwReserved
    );

    HINTERNET BOTMON_API __stdcall _winHttpOpenRequest(
        IN HINTERNET hConnect,
        IN LPCWSTR pwszVerb,
        IN LPCWSTR pwszObjectName,
        IN LPCWSTR pwszVersion,
        IN LPCWSTR pwszReferrer OPTIONAL,
        IN LPCWSTR FAR * ppwszAcceptTypes OPTIONAL,
        IN DWORD dwFlags
    );

    BOOL BOTMON_API __stdcall _winHttpSendRequest(
        IN HINTERNET hRequest,
        _In_reads_opt_(dwHeadersLength) LPCWSTR lpszHeaders,
        IN DWORD dwHeadersLength,
        _In_reads_bytes_opt_(dwOptionalLength) LPVOID lpOptional,
        IN DWORD dwOptionalLength,
        IN DWORD dwTotalLength,
        IN DWORD_PTR dwContext
    );

    BOOL BOTMON_API __stdcall _winHttpReadData(
        IN HINTERNET hRequest,
        OUT LPVOID lpBuffer,
        IN DWORD dwNumberOfBytesToRead,
        OUT LPDWORD lpdwNumberOfBytesRead
    );

    BOOL BOTMON_API __stdcall _winHttpReceiveResponseFromFile(
        IN HINTERNET hRequest,
        IN LPVOID    lpReserved
    );

    BOOL BOTMON_API __stdcall _winHttpQueryDataAvailableFromFile(
        IN  HINTERNET hRequest,
        OUT LPDWORD   lpdwNumberOfBytesAvailable
    );

    BOOL BOTMON_API __stdcall _winHttpReadDataFromFile(
        IN  HINTERNET hRequest,
        OUT LPVOID    lpBuffer,
        IN  DWORD     dwNumberOfBytesToRead,
        OUT LPDWORD   lpdwNumberOfBytesRead
    );

};
