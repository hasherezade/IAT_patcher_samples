#include "logger.h"
#include <stdarg.h>
#include <ctype.h>

BOOL Logger::append(const char* format, ...)
{
    if (format == NULL) {
        return FALSE;
    }
    va_list argptr;                     
    // Initializing arguments to store all values after format
    va_start(argptr, format);

    char line[MAX_LINE];
    int printed = vsnprintf(line, MAX_LINE, format, argptr);

    //cleaning up the list:
    va_end(argptr);
    if (printed <= 0) return FALSE;

    OutputDebugStringA(line);
    return TRUE;
}

BOOL Logger::append_raw(LPVOID lpOptional, const DWORD dwOptionalLength, BOOL stopOnNonPrintable)
{
    if (lpOptional == NULL) return FALSE;

    char *line = new char [dwOptionalLength + 1];
    char *line_ptr = line;

    char *in_ptr = (char*) lpOptional;
    DWORD i = 0;
    for (; i < dwOptionalLength; i++) {
        char c = in_ptr[i];
        if (!isprint(c)) {
            if (stopOnNonPrintable) break;
            line_ptr[i] = '.';
        } else {
            line_ptr[i] = ((char*)lpOptional)[i];
        }
    }
    line[i] = '\0';
    OutputDebugStringA(line);
    return TRUE;
}