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
    );

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
    );

};
