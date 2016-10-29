#pragma once 

#include <Windows.h>

void make_out_filename(IN const LPWSTR dirname, IN const LPCSTR prefix, OUT LPSTR out_filename);
BOOL dump_binary(IN LPSTR out_filename, IN BYTE *pbData, IN DWORD dwDataLen);

LPVOID search_pe_hdr(BYTE *buf, DWORD buf_size);
BOOL starts_with(LPVOID buffer, DWORD bufferSize, LPCSTR keyword);
