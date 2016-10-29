#pragma once 
#include <Windows.h>
#include <stdio.h>
#include "util.h"

#define DIRNAME L"BotMon"

#define MAX_LINE 1024

namespace Logger
{
    BOOL append(const char* format, ...);

    //returns: size of the appended content:
    DWORD append_raw(LPVOID lpOptional, const DWORD dwOptionalLength, BOOL stopOnNonPrintable);

    //dump content into a binary file, log the event:
    BOOL logged_binary_dump(LPWSTR dir_name, LPCSTR file_prefix, LPCSTR log_line_prefix, LPVOID buffer, DWORD bufferSize);
};

