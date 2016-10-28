#include "processmod.h"

#include "logger.h"

BOOL __declspec(dllexport) __stdcall _writeProcessMemory(
    IN HANDLE hProcess,
    IN LPVOID lpBaseAddress,
    _In_reads_bytes_(nSize) LPCVOID lpBuffer,
    IN SIZE_T nSize,
    _Out_opt_ SIZE_T * lpNumberOfBytesWritten
)
{
    char out_filename[MAX_PATH];
    make_out_filename(L"write_mem", out_filename);
    dump_binary(out_filename, (BYTE*)lpBuffer, nSize);
    Logger::append("[PROCESSWRITE] %u saved to: %s\n", nSize, out_filename);

    BOOL res = WriteProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesWritten);
    if (res == FALSE) Logger::append("[PROCESSWRITE] Failed");
    return res;
}