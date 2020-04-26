#include "processmod.h"

#include "logger.h"

BOOL __declspec(dllexport) WINAPI _createProcessW(
    _In_opt_ LPCWSTR lpApplicationName,
    _Inout_opt_ LPWSTR lpCommandLine,
    _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
    _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
    _In_ BOOL bInheritHandles,
    _In_ DWORD dwCreationFlags,
    _In_opt_ LPVOID lpEnvironment,
    _In_opt_ LPCWSTR lpCurrentDirectory,
    _In_ LPSTARTUPINFOW lpStartupInfo,
    _Out_ LPPROCESS_INFORMATION lpProcessInformation
)
{
    BOOL res = CreateProcessW(
        lpApplicationName,
        lpCommandLine,
        lpProcessAttributes,
        lpThreadAttributes,
        bInheritHandles,
        dwCreationFlags,
        lpEnvironment,
        lpCurrentDirectory,
        lpStartupInfo,
        lpProcessInformation
    );
    if (res == FALSE) {
        Logger::append("[PROCESS][CREATE_W] %S : %S, flags: %x -> failed", lpApplicationName, lpCommandLine, dwCreationFlags);
    }
    else {
        Logger::append("[PROCESS][CREATE_W]  %S : %S, flags: %x -> PID: %d", lpApplicationName, lpCommandLine, dwCreationFlags, lpProcessInformation->dwProcessId);
    }
    return res;
}

BOOL __declspec(dllexport) WINAPI _createProcessA(
    _In_opt_ LPCSTR lpApplicationName,
    _Inout_opt_ LPSTR lpCommandLine,
    _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
    _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
    _In_ BOOL bInheritHandles,
    _In_ DWORD dwCreationFlags,
    _In_opt_ LPVOID lpEnvironment,
    _In_opt_ LPCSTR lpCurrentDirectory,
    _In_ LPSTARTUPINFOA lpStartupInfo,
    _Out_ LPPROCESS_INFORMATION lpProcessInformation
)
{
    BOOL res = CreateProcessA(lpApplicationName, lpCommandLine,
        lpProcessAttributes,
        lpThreadAttributes,
        bInheritHandles,
        dwCreationFlags,
        lpEnvironment,
        lpCurrentDirectory,
        lpStartupInfo,
        lpProcessInformation
    );
    if (res == FALSE) {
        Logger::append("[PROCESS][CREATE_A] %s : %s, flags: %x -> failed", lpApplicationName, lpCommandLine, dwCreationFlags);
    }
    else {
        Logger::append("[PROCESS][CREATE_A]  %s : %s, flags: %x -> PID: %d", lpApplicationName, lpCommandLine, dwCreationFlags, lpProcessInformation->dwProcessId);
    }
    return res;
}

BOOL __declspec(dllexport) __stdcall _writeProcessMemory(
    IN HANDLE hProcess,
    IN LPVOID lpBaseAddress,
    _In_reads_bytes_(nSize) LPCVOID lpBuffer,
    IN SIZE_T nSize,
    _Out_opt_ SIZE_T * lpNumberOfBytesWritten
)
{
    DWORD pid = GetProcessId(hProcess);

    Logger::append("[PROCESS][WRITE] PID: %d", pid);
    Logger::logged_binary_dump(DIRNAME, "write_mem", "[PROCESS][WRITE]", (BYTE*)lpBuffer, nSize);

    if (search_pe_hdr((BYTE*)lpBuffer, nSize)) {
        Logger::append("[PROCESS][WRITE] PE HEADER detected!");
    }

    BOOL res = WriteProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesWritten);
    if (res == FALSE) Logger::append("[PROCESS][WRITE] Failed");
    return res;
}
