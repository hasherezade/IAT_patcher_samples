#include "http.h"
#include <stdio.h>

#include "logger.h"

using namespace std;

HINTERNET __stdcall _winHttpConnect(
    IN HINTERNET hSession,
    IN LPCWSTR pswzServerName,
    IN INTERNET_PORT nServerPort,
    _Reserved_ DWORD dwReserved)
{
    Logger::append("Connecting...");
    Logger::append("[CONN]   %S:%u", pswzServerName, static_cast<unsigned int>(nServerPort));
    return WinHttpConnect(hSession, pswzServerName, nServerPort, dwReserved);
}

HINTERNET __stdcall _winHttpOpenRequest(IN HINTERNET hConnect,
    IN LPCWSTR pwszVerb,
    IN LPCWSTR pwszObjectName, //url
    IN LPCWSTR pwszVersion,
    IN LPCWSTR pwszReferrer OPTIONAL,
    IN LPCWSTR FAR * ppwszAcceptTypes OPTIONAL,
    IN DWORD dwFlags)
{
    if (pwszVerb) Logger::append("[VERB]   %S", pwszVerb);
    if (pwszVersion) Logger::append("[VERSIO] %S", pwszVersion);
    if (pwszObjectName) Logger::append("[OBJECT] %S", pwszObjectName);

    HINTERNET res = WinHttpOpenRequest(hConnect, pwszVerb, pwszObjectName, pwszVersion, pwszReferrer, ppwszAcceptTypes, dwFlags);
     //TODO: log the result
    return res;
}

BOOL __stdcall _winHttpSendRequest(IN HINTERNET hRequest,
    _In_reads_opt_(dwHeadersLength) LPCWSTR lpszHeaders,
    IN DWORD dwHeadersLength,
    _In_reads_bytes_opt_(dwOptionalLength) LPVOID lpOptional,
    IN DWORD dwOptionalLength,
    IN DWORD dwTotalLength,
    IN DWORD_PTR dwContext)
{
    if (dwHeadersLength != 0 && lpszHeaders != NULL) {
        Logger::append("[HEADER] %S", lpszHeaders);
    }
    if (dwOptionalLength != 0) {
        Logger::append("[OPTIONAL]");
        Logger::append_raw(lpOptional, dwOptionalLength);
        Logger::append("[/OPTIONAL]");
    }
    BOOL res = WinHttpSendRequest(hRequest, lpszHeaders, dwHeadersLength, lpOptional, dwOptionalLength, dwTotalLength, dwContext);
    //TODO: log the result
    return res;
}

BOOL  __declspec(dllexport) __stdcall _winHttpReadData(
    IN HINTERNET hRequest,
    OUT LPVOID lpBuffer,
    IN DWORD dwNumberOfBytesToRead,
    OUT LPDWORD lpdwNumberOfBytesRead)
{
    BOOL res = WinHttpReadData(hRequest, lpBuffer, dwNumberOfBytesToRead, lpdwNumberOfBytesRead);
    if (res == FALSE) return FALSE;

    char out_filename[MAX_PATH];
    make_out_filename(L"responses", out_filename);
    dump_binary(out_filename, (BYTE*) lpBuffer, *lpdwNumberOfBytesRead);
    if (*lpdwNumberOfBytesRead != 0) {
        Logger::append("[RECEIVED] %u saved to: %s", *lpdwNumberOfBytesRead, out_filename);
    }
    return res;
}
