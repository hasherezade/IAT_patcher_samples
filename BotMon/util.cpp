#include "util.h"

#include <stdio.h>
#include <time.h>

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

BOOL has_printable_line(LPVOID buffer, DWORD bufferSize)
{
    if (bufferSize == 0) return FALSE;

    DWORD i = 0;
    for (; i < bufferSize; i++) {
        char c = ((char*)buffer)[i];
        if (!isprint(c)) {
            if (i > 0 && (c == '\0' || c == '\n')) {
                return TRUE;
            }
            return FALSE;
        }
    }
    return TRUE;
}