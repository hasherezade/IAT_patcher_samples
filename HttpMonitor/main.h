#pragma once 

#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <winhttp.h>
#include <wincrypt.h>

#pragma comment(lib, "WinHttp.lib")
#pragma comment(lib, "crypt32.lib")

extern "C" {

BOOL __declspec(dllexport) __stdcall _cryptDecrypt(
    IN HCRYPTKEY   hKey,
    IN HCRYPTHASH  hHash,
    IN BOOL        Final,
    IN DWORD       dwFlags,
    _Inout_updates_bytes_to_(*pdwDataLen, *pdwDataLen)   BYTE *pbData,
    _Inout_ DWORD *pdwDataLen
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

};
