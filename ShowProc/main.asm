; CC-BY: hasherezade
; Sample library for IAT Patcher
; http://hasherezade.net/IAT_patcher/

.386
.model flat,stdcall
option casemap:none

include windows.inc

include kernel32.inc
include msvcrt.inc

IncludeLib kernel32.lib
includelib msvcrt.lib

.data
szFileFmt db 'w',0
szFileName db 'ProcList.txt',0

szFmtS db '%x; loaded: %s', 0dh,0ah,0
szFmtOrd db '%x; loaded: <ord: %ld>', 0dh,0ah,0

.data?
hFile  HANDLE ?
dwAddr HANDLE ?

ASSUME FS:NOTHING

.code
DllEntry proc hInstance:HINSTANCE, reason:DWORD, reserved1:DWORD
	.if reason==DLL_PROCESS_ATTACH
		
		;create the file
		invoke  crt_fopen,offset szFileName, offset szFileFmt
		mov     hFile,eax
		
	.elseif reason==DLL_PROCESS_DETACH
		invoke  crt_fclose,hFile
		mov hFile, 0
	.endif
ret
DllEntry Endp


strlen proc string:PSTR
	push edx
	xor eax,eax
	
	mov edx, dword ptr[string]
	test edx, 0FFFF0000h ; by ordinal? (or NULL)
	je _strlen_end
	
	mov edx, dword ptr[string]
	_is_null:
	
	cmp byte ptr[edx+eax],0
	je _strlen_end
	
	;printable?
	cmp byte ptr[edx+eax],20h
	jl _strlen_end
	cmp byte ptr[edx+eax],7Fh
	jg _strlen_end
	
	inc eax
	jmp _is_null
	_strlen_end:
	pop edx
ret
strlen endp


print_to_file proc lpString:LPCSTR
	mov eax, hFile
	cmp eax, 0
	je _print_end
	
	invoke strlen,lpString
	cmp eax, 0
	je _print_ord
	
	;invoke crt_printf, addr szFmtS, dwAddr, lpString
	invoke crt_fprintf, hFile, addr szFmtS,dwAddr, lpString
	jmp _flush_file
	
_print_ord:
	;invoke crt_printf, addr szFmtOrd,dwAddr, lpString
	invoke crt_fprintf, hFile, addr szFmtOrd,dwAddr, lpString
	
_flush_file:
	invoke crt_fflush, hFile
	
_print_end:
	Ret
print_to_file EndP

va_to_rva proc dwVA:HANDLE
	push edx
	mov eax, dwVA

	mov edx, dword ptr fs:[30h]
	mov edx, [edx+8]
	sub eax, edx
	
	pop edx
	Ret
va_to_rva EndP 

PrintProcName proc hModule:HMODULE, lpName:LPCSTR

	; save return RVA:
	mov eax, dword ptr [ebp+4]
	invoke va_to_rva, eax
	mov dwAddr, eax
	
	invoke print_to_file,lpName
	
invoke_origina1:
	invoke GetProcAddress,hModule,lpName
	Ret
PrintProcName EndP

PrintLibNameA proc lpLibName:LPCSTR

	; save return RVA:
	mov eax, dword ptr [ebp+4]
	invoke va_to_rva, eax
	mov dwAddr, eax
	
	invoke print_to_file,lpLibName
	
invoke_original2:
	invoke LoadLibrary,lpLibName
	Ret
PrintLibNameA EndP

End DllEntry
