#include "crypt.h"
#include <stdio.h>
#include <time.h>

#include "logger.h"

using namespace std;

BOOL
_stdcall
_cryptImportKey(
    _In_                    HCRYPTPROV  hProv,
    _In_reads_bytes_(dwDataLen)  CONST BYTE  *pbData,
    _In_                    DWORD       dwDataLen,
    _In_                    HCRYPTKEY   hPubKey,
    _In_                    DWORD       dwFlags,
    _Out_                   HCRYPTKEY   *phKey
)
{
    if (pbData != NULL) {
        Logger::logged_binary_dump(DIRNAME, "crypt_key", "[CRYPT]", (LPVOID)pbData, dwDataLen);
    }
    return CryptImportKey(hProv, pbData, dwDataLen, hPubKey, dwFlags, phKey);
}

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
    if (res == FALSE) {
        Logger::append("[DECRYPT] Failed");
        return res;
    }
    if (pdwDataLen != NULL) {
        Logger::logged_binary_dump(DIRNAME, "decrypted", "[DECRYPT]", pbData, *pdwDataLen);
    }
    if (search_pe_hdr((BYTE*)pbData, *pdwDataLen)) {
        Logger::append("[DECRYPT] PE HEADER detected!");
    }
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
    if (pdwDataLen != NULL) {
        Logger::logged_binary_dump(DIRNAME, "before_encryption", "[ENCRYPT]", pbData, *pdwDataLen);
    }
    BOOL res = CryptEncrypt(hKey, hHash, Final, dwFlags, pbData, pdwDataLen, dwBufLen);
    if (res == FALSE) {
        Logger::append("[ENCRYPT] Failed");
    }
    return res; 
}
