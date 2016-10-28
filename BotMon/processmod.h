#pragma once 

#include <Windows.h>

extern "C" {

	BOOL __declspec(dllexport) __stdcall _writeProcessMemory(
        IN HANDLE hProcess,
        IN LPVOID lpBaseAddress,
        _In_reads_bytes_(nSize) LPCVOID lpBuffer,
        IN SIZE_T nSize,
        _Out_opt_ SIZE_T * lpNumberOfBytesWritten
    );

};
