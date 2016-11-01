#include "http.h"
#include <stdio.h>

#include "logger.h"

HINTERNET __stdcall _winHttpConnect(
    IN HINTERNET hSession,
    IN LPCWSTR pswzServerName,
    IN INTERNET_PORT nServerPort,
    _Reserved_ DWORD dwReserved)
{

    Logger::append("[HTTP][conn] %S:%u", pswzServerName, static_cast<unsigned int>(nServerPort));
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
    if (pwszVerb) Logger::append("[HTTP][verb] %S", pwszVerb);
    if (pwszVersion) Logger::append("[HTTP][vers] %S", pwszVersion);
    if (pwszObjectName) Logger::append("[HTTP][obj ] %S", pwszObjectName);

    HINTERNET res = WinHttpOpenRequest(hConnect, pwszVerb, pwszObjectName, pwszVersion, pwszReferrer, ppwszAcceptTypes, dwFlags);
    if (res == FALSE) {
        Logger::append("[HTTP] Failed");
    }
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
        Logger::append("[HTTP][header] %S", lpszHeaders);
    }
    if (dwOptionalLength != 0) {
        Logger::append("[HTTP][optional]");
        Logger::append_raw(lpOptional, dwOptionalLength, FALSE);
        Logger::append("[HTTP][/optional]");
        Logger::logged_binary_dump(DIRNAME, "post", "[HTTP][optional]", lpOptional, dwOptionalLength);
    }
    BOOL res = WinHttpSendRequest(hRequest, lpszHeaders, dwHeadersLength, lpOptional, dwOptionalLength, dwTotalLength, dwContext);
    if (res == FALSE) {
        Logger::append("[HTTP] Failed");
    }
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

    if (*lpdwNumberOfBytesRead == 0) return res;
    DWORD printableSize = 0;
    if (has_printable_line(lpBuffer, *lpdwNumberOfBytesRead)) {
        Logger::append("[HTTP][response]");
        printableSize = Logger::append_raw(lpBuffer, *lpdwNumberOfBytesRead, TRUE);
        Logger::append("[HTTP][/response]");
    }
    //dump the raw content into a file:
    Logger::logged_binary_dump(DIRNAME, "responses", "[HTTP][rcvd]", lpBuffer, *lpdwNumberOfBytesRead);

    //check for a PE file:
    if (search_pe_hdr((BYTE*)lpBuffer, *lpdwNumberOfBytesRead)) {
        Logger::append("[HTTP] PE HEADER detected!");
    }
    /*
    const char blacklisted[] ="/25/";
    if (starts_with(lpBuffer, *lpdwNumberOfBytesRead, blacklisted)) {
        // this is the blacklisted command!
        return FALSE;
    }*/
    return res;
}
