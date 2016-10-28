#include "util.h"

#include <stdio.h>
#include <time.h>

void make_out_filename(const LPWSTR dirname, const LPCSTR prefix, LPSTR out_filename)
{
    CreateDirectory(dirname, NULL);
    static time_t t1 = 0;
    if (time == 0) {
        t1 = time(NULL);
        srand(t1);
    }
    _snprintf(out_filename, MAX_PATH, "%S\\%s_%llu_%u.bin", dirname, prefix, time(NULL), (unsigned int)rand());
}

BOOL dump_binary(LPSTR out_filename, BYTE *pbData, DWORD dwDataLen)
{
    FILE *fp = fopen(out_filename, "wb");
    if (fp == NULL) return FALSE;
    if (dwDataLen != 0) {
        fwrite(pbData, 1, dwDataLen, fp);
    }
    fclose(fp);
    return TRUE;
}