#pragma once 

#include <windows.h>
#include <winhttp.h>

#pragma comment(lib, "WinHttp.lib")

extern "C" {

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

};
