#include "http.h"
#include <stdio.h>
#include "util.h"

#define LOG_NAME "HttpMonitor.log"

using namespace std;

HINTERNET __stdcall _winHttpConnect(
    IN HINTERNET hSession,
    IN LPCWSTR pswzServerName,
    IN INTERNET_PORT nServerPort,
    _Reserved_ DWORD dwReserved)
{
    FILE *fp = fopen(LOG_NAME, "a+");
    if (fp != NULL) {
        fprintf(fp, "[CONN]   %S:%u\n", pswzServerName, static_cast<unsigned int>(nServerPort));
        fclose(fp);
    }
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
    FILE *fp = fopen(LOG_NAME, "a+");
    if (fp != NULL) {
        fprintf(fp, "[VERB]   %S\n", pwszVerb);
        fprintf(fp, "[VERSIO] %S\n", pwszVersion);
        fprintf(fp, "[OBJECT] %S\n", pwszObjectName);
        fclose(fp);
    }
    HINTERNET res = WinHttpOpenRequest(hConnect, pwszVerb, pwszObjectName, pwszVersion, pwszReferrer, ppwszAcceptTypes, dwFlags);
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
    FILE *fp = fopen(LOG_NAME, "a+");
    if (fp != NULL) {
        if (dwHeadersLength != 0) {
            fprintf(fp, "[HEADER] %S\n", lpszHeaders);
        }
        if (dwOptionalLength != 0) {
            fprintf(fp, "[OPTIONAL]\n");
            fwrite(lpOptional, 1, dwOptionalLength, fp);
            fprintf(fp, "\n[/OPTIONAL]\n");
        }
        fclose(fp);
    }
    BOOL res = WinHttpSendRequest(hRequest, lpszHeaders, dwHeadersLength, lpOptional, dwOptionalLength, dwTotalLength, dwContext);
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

    FILE *fp = fopen(LOG_NAME, "a+");
    if (fp != NULL) {
        if (*lpdwNumberOfBytesRead != 0) {
            fprintf(fp, "[RECEIVED] %u saved to: %s\n", *lpdwNumberOfBytesRead, out_filename);
        }
        fclose(fp);
    }
    return res;
}
