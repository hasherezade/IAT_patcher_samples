#pragma once 
#include <Windows.h>
#include <stdio.h>
#include "util.h"

#define DIRNAME L"BotMon"

#define MAX_LINE 1024

namespace Logger
{
    BOOL append(const char* format, ...);
    BOOL append_raw(LPVOID lpOptional, const DWORD dwOptionalLength);
};

