#pragma once 

#include <windows.h>
#include <winhttp.h>
#include <wincrypt.h>

#pragma comment(lib, "crypt32.lib")

extern "C" {

	BOOL __declspec(dllexport) __stdcall _cryptDecrypt(
		IN HCRYPTKEY   hKey,
		IN HCRYPTHASH  hHash,
		IN BOOL        Final,
		IN DWORD       dwFlags,
		_Inout_updates_bytes_to_(*pdwDataLen, *pdwDataLen) BYTE *pbData,
		_Inout_ DWORD *pdwDataLen
    );

BOOL __declspec (dllexport) __stdcall _cryptEncrypt(
    IN HCRYPTKEY   hKey,
    IN HCRYPTHASH  hHash,
    IN BOOL    Final,
    IN DWORD   dwFlags,
    _Inout_updates_bytes_to_opt_(dwBufLen, *pdwDataLen) BYTE *pbData,
    _Inout_ DWORD   *pdwDataLen,
    IN DWORD   dwBufLen
    );
};
