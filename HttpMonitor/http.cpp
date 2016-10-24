#include "http.h"
#include <stdio.h>

using namespace std;

HINTERNET __stdcall _winHttpOpenRequest(IN HINTERNET hConnect,
    IN LPCWSTR pwszVerb,
    IN LPCWSTR pwszObjectName, //url
    IN LPCWSTR pwszVersion,
    IN LPCWSTR pwszReferrer OPTIONAL,
    IN LPCWSTR FAR * ppwszAcceptTypes OPTIONAL,
    IN DWORD dwFlags)
{
    FILE *fp = fopen("_winHttpOpenRequest.log", "a+");
    if (fp != NULL) {
		fprintf(fp, "%S\n", pwszObjectName);
		fclose(fp);
	}
	HINTERNET res = WinHttpOpenRequest(hConnect, pwszVerb, pwszObjectName, pwszVersion, pwszReferrer, ppwszAcceptTypes, dwFlags);
	return res;
}


BOOL __stdcall _winHttpSendRequest(IN HINTERNET hRequest,
    _In_reads_opt_(dwHeadersLength) LPCWSTR lpszHeaders,
    IN DWORD dwHeadersLength,
    _In_reads_bytes_opt_(dwOptionalLength) LPVOID lpOptional,
    IN DWORD dwOptionalLength,
    IN DWORD dwTotalLength,
    IN DWORD_PTR dwContext)
{
    FILE *fp = fopen("_winHttpOpenRequest.log", "a+");
    if (fp != NULL) {
		if (dwOptionalLength != 0) {
			fprintf(fp, "--------------------\n");
			fwrite(lpOptional, 1, dwOptionalLength, fp);
			fprintf(fp, "--------------------\n");
		}
		fclose(fp);
	}
	BOOL res = WinHttpSendRequest(hRequest, lpszHeaders, dwHeadersLength, lpOptional, dwOptionalLength, dwTotalLength, dwContext);
	return res;
}

