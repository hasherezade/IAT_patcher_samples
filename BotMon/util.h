#pragma once 

#include <Windows.h>

LPVOID search_pe_hdr(BYTE *buf, DWORD buf_size);
BOOL starts_with(LPVOID buffer, DWORD bufferSize, LPCSTR keyword);

//counts printable characters, starting form the beginning till the first non-printable
BOOL has_printable_line(LPVOID buffer, DWORD bufferSize);

size_t get_file_size(const char *filename);
