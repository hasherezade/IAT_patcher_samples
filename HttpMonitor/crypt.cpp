#include "crypt.h"
#include <stdio.h>

using namespace std;

BOOL __stdcall _cryptDecrypt(
    IN HCRYPTKEY   hKey,
    IN HCRYPTHASH  hHash,
    IN BOOL        Final,
    IN DWORD       dwFlags,
    _Inout_updates_bytes_to_(*pdwDataLen, *pdwDataLen)   BYTE *pbData,
    _Inout_ DWORD *pdwDataLen
    )
{
	BOOL res = CryptDecrypt(hKey, hHash, Final, dwFlags, pbData, pdwDataLen);
	if (res == FALSE) return res;

	FILE *fp = fopen("_decrypted_data.log", "a+");
    if (fp != NULL) {
		if (*pdwDataLen != 0) {
			fprintf(fp, "\n--------------------\n");
			fwrite(pbData, 1, *pdwDataLen, fp);
			fprintf(fp, "\n--------------------\n");
		}
		fclose(fp);
	}
	return res;
}
