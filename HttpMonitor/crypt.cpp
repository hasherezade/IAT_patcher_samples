#include "crypt.h"
#include <stdio.h>
#include <time.h>
#include "util.h"

using namespace std;

BOOL __stdcall _cryptDecrypt(
    IN HCRYPTKEY   hKey,
    IN HCRYPTHASH  hHash,
    IN BOOL        Final,
    IN DWORD       dwFlags,
    _Inout_updates_bytes_to_(*pdwDataLen, *pdwDataLen) BYTE *pbData,
    _Inout_ DWORD *pdwDataLen
    )
{
    BOOL res = CryptDecrypt(hKey, hHash, Final, dwFlags, pbData, pdwDataLen);
    if (res == FALSE) return res;

    char out_filename[MAX_PATH];
    make_out_filename(L"decrypted", out_filename);
    dump_binary(out_filename, pbData, *pdwDataLen);
    return res;
}

BOOL __declspec (dllexport) __stdcall _cryptEncrypt(
    IN HCRYPTKEY   hKey,
    IN HCRYPTHASH  hHash,
    IN BOOL    Final,
    IN DWORD   dwFlags,
    _Inout_updates_bytes_to_opt_(dwBufLen, *pdwDataLen) BYTE *pbData,
    _Inout_ DWORD   *pdwDataLen,
    IN DWORD   dwBufLen
    )
{
    char out_filename[MAX_PATH];
    make_out_filename(L"before_encryption", out_filename);
    dump_binary(out_filename, pbData, *pdwDataLen);

    BOOL res = CryptEncrypt(hKey, hHash, Final, dwFlags, pbData, pdwDataLen, dwBufLen);
    return res; 
}