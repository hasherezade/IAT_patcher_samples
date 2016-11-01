#pragma once 

#include <windows.h>
#include <winhttp.h>

#pragma comment(lib, "WinHttp.lib")

extern "C" {

    HINTERNET __declspec(dllexport) __stdcall _winHttpConnect(
        IN HINTERNET hSession,
        IN LPCWSTR pswzServerName,
        IN INTERNET_PORT nServerPort,
        _Reserved_ DWORD dwReserved
    );

	HINTERNET __declspec(dllexport) __stdcall _winHttpOpenRequest(IN HINTERNET hConnect,
		IN LPCWSTR pwszVerb,
		IN LPCWSTR pwszObjectName,
		IN LPCWSTR pwszVersion,
		IN LPCWSTR pwszReferrer OPTIONAL,
		IN LPCWSTR FAR * ppwszAcceptTypes OPTIONAL,
		IN DWORD dwFlags
	);

	BOOL __declspec(dllexport) __stdcall _winHttpSendRequest(
		IN HINTERNET hRequest,
		_In_reads_opt_(dwHeadersLength) LPCWSTR lpszHeaders,
		IN DWORD dwHeadersLength,
		_In_reads_bytes_opt_(dwOptionalLength) LPVOID lpOptional,
		IN DWORD dwOptionalLength,
		IN DWORD dwTotalLength,
		IN DWORD_PTR dwContext
	);

    BOOL  __declspec(dllexport) __stdcall _winHttpReadData(
        IN HINTERNET hRequest,
        OUT LPVOID lpBuffer,
        IN DWORD dwNumberOfBytesToRead,
        OUT LPDWORD lpdwNumberOfBytesRead
    );

};
