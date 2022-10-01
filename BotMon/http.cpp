#include "http.h"
#include <iostream>
#include <sstream>

#include "logger.h"
#include "util.h"

#define RESPONSE_FILE "response"
#define RESPONSE_EXT ".bin"

size_t g_CurrResp = 0;

std::string make_filename(const std::string &base_name, size_t id, const std::string &ext)
{
    std::stringstream ss;
    ss << base_name;
    ss << "_";
    ss << id;
    ss << ext;
    return ss.str();
}

//-----

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
    return TRUE; // always true
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

BOOL BOTMON_API __stdcall _winHttpReceiveResponseFromFile(
    IN HINTERNET hRequest,
    IN LPVOID    lpReserved
)
{
    std::string resp_file = make_filename(RESPONSE_FILE, g_CurrResp, RESPONSE_EXT);
    if (get_file_size(resp_file.c_str()) != 0) {
        return TRUE;
    }
    return FALSE;
}


BOOL BOTMON_API __stdcall _winHttpQueryDataAvailableFromFile(
    IN  HINTERNET hRequest,
    OUT LPDWORD   lpdwNumberOfBytesAvailable
)
{
    const std::string resp_file = make_filename(RESPONSE_FILE, g_CurrResp, RESPONSE_EXT);
    size_t size = get_file_size(resp_file.c_str());
    if (lpdwNumberOfBytesAvailable) {
        (*lpdwNumberOfBytesAvailable) = size;
    }
   return TRUE;
}


BOOL BOTMON_API __stdcall _winHttpReadDataFromFile(
    IN  HINTERNET hRequest,
    OUT LPVOID    lpBuffer,
    IN  DWORD     dwNumberOfBytesToRead,
    OUT LPDWORD   lpdwNumberOfBytesRead
)
{
    if (!lpBuffer) return FALSE;

    const std::string resp_file = make_filename(RESPONSE_FILE, g_CurrResp, RESPONSE_EXT);
    FILE *fp = fopen(resp_file.c_str(), "rb");
    if (!fp) return FALSE;

    size_t readSize = fread(lpBuffer, 1, dwNumberOfBytesToRead, fp);
    fclose(fp);

    if (lpdwNumberOfBytesRead) {
        (*lpdwNumberOfBytesRead) = readSize;
    }
    g_CurrResp++;
    return TRUE;
}
