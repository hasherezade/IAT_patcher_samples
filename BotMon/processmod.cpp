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
    Logger::logged_binary_dump(DIRNAME, "write_mem", "[PROCESSWRITE]", (BYTE*)lpBuffer, nSize);

    if (search_pe_hdr((BYTE*)lpBuffer, nSize)) {
        Logger::append("[PROCESSWRITE] PE HEADER detected!");
    }

    BOOL res = WriteProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesWritten);
    if (res == FALSE) Logger::append("[PROCESSWRITE] Failed");
    return res;
}