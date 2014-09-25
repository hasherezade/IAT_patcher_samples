Sample library for IAT Patcher
http://hasherezade.net/IAT_patcher
compile using WinAsm (masm32) : http://www.winasm.net
---
Purpose:
Prints list of dynamically loaded modules and functions. 

Format:
[return_address]; loaded [Name]

Example:
19aa50; loaded: KERNEL32.DLL
19aa6e; loaded: SystemTimeToFileTime
19aa6e; loaded: SetEvent

Usage:
Use IAT Patcher to hook your program.