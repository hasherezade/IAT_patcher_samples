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

IMAGE_NT_HEADERS* get_nt_hrds(BYTE *pe_buffer)
{
    if (pe_buffer == NULL) return NULL;

    IMAGE_DOS_HEADER *idh = (IMAGE_DOS_HEADER*)pe_buffer;
    if (idh->e_magic != IMAGE_DOS_SIGNATURE) {
        return NULL;
    }
    const LONG kMaxOffset = 1024;
    LONG pe_offset = idh->e_lfanew;
    if (pe_offset > kMaxOffset) return NULL;

    IMAGE_NT_HEADERS *inh = (IMAGE_NT_HEADERS *)((BYTE*)pe_buffer + pe_offset);
    return inh;
}

LPVOID search_pe_hdr(BYTE *buf, DWORD buf_size)
{
    for (DWORD i = 0; i < buf_size; i++) {
        IMAGE_DOS_HEADER *idh = (IMAGE_DOS_HEADER*) buf;
        if (get_nt_hrds((BYTE*)idh) != NULL) return idh;
        buf++;
    }
    return NULL;
}

BOOL starts_with(LPVOID buffer, DWORD bufferSize, LPCSTR keyword)
{
    const DWORD check_size = static_cast<DWORD>(strlen(keyword));
    if (bufferSize < check_size) return FALSE;

    if (memcmp(buffer, keyword, check_size) == 0) {
        return TRUE;
    }
    return FALSE;
}