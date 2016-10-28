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

BOOL Logger::append_raw(LPVOID lpOptional, const DWORD dwOptionalLength)
{
    if (lpOptional == NULL) return FALSE;

    char *line = new char [dwOptionalLength];
    char *line_ptr = line;

    char *in_ptr = (char*) lpOptional;
    for (DWORD i = 0; i < dwOptionalLength; i++) {
        char c = in_ptr[i];
        if (!isprint(c)) {
            line_ptr[i] = '.';
        } else {
            line_ptr[i] = ((char*)lpOptional)[i];
        }
    }
    OutputDebugStringA(line);
    return TRUE;
}