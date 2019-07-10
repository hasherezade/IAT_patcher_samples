#include "logger.h"

#include <stdarg.h>
#include <ctype.h>
#include <wtypes.h>
#include <time.h>

void make_out_filename(const LPWSTR dirname, const LPCSTR prefix, LPSTR out_filename)
{
    wchar_t current_dir[MAX_PATH];
    GetCurrentDirectoryW(MAX_PATH, current_dir);

    CreateDirectoryW(dirname, NULL);

    static time_t t1 = 0;
    if (time == 0) {
        t1 = time(NULL);
        srand(t1);
    }
    _snprintf(out_filename, MAX_PATH,
        "%S\\%S\\%s_%llu_%u.bin",
        current_dir,
        dirname,
        prefix,
        static_cast<unsigned long long>(time(NULL)),
        static_cast<unsigned int>(rand())
    );
}

BOOL dump_binary(LPSTR out_filename, BYTE *pbData, DWORD dwDataLen)
{
    FILE *fp = fopen(out_filename, "wb");
    if (fp == NULL) return FALSE;
    if (dwDataLen != 0) {
        fwrite(pbData, 1, dwDataLen, fp);
    }
    fclose(fp);
    return TRUE;
}

//----

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

BOOL Logger::appendW(const wchar_t* format, ...)
{
    if (format == NULL) {
        return FALSE;
    }
    va_list argptr;
    // Initializing arguments to store all values after format
    va_start(argptr, format);
    _locale_t locale = { 0 };
    wchar_t line[MAX_LINE];
    int printed = _vsnwprintf_s(line, MAX_LINE, format, argptr);

    //cleaning up the list:
    va_end(argptr);
    if (printed <= 0) return FALSE;

    OutputDebugStringW(line);
    return TRUE;
}

DWORD Logger::append_raw(LPVOID lpOptional, const DWORD dwOptionalLength, BOOL stopOnNonPrintable)
{
    if (lpOptional == NULL) return 0;

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
    return i;
}

BOOL Logger::logged_binary_dump(LPWSTR dir_name, LPCSTR file_prefix, LPCSTR log_line_prefix, LPVOID buffer, DWORD bufferSize)
{
    if (buffer == NULL || bufferSize == 0) {
        return FALSE;
    }
    char out_filename[MAX_PATH];
    make_out_filename(dir_name, file_prefix, out_filename);
    if (dump_binary(out_filename, (BYTE*) buffer, bufferSize)) {
        Logger::append("%s %u saved to: %s", log_line_prefix, bufferSize, out_filename);
        return TRUE;
    }
    return FALSE;
}