#pragma once 

#include <Windows.h>

void make_out_filename(IN LPWSTR dirname, OUT LPSTR out_filename);
BOOL dump_binary(IN LPSTR out_filename, IN BYTE *pbData, IN DWORD dwDataLen);