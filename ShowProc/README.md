Sample library for IAT Patcher<br/>
http://hasherezade.net/IAT_patcher<br/>
compile using WinAsm (masm32)<br/>

Purpose:<br/>
Prints list of dynamically loaded modules and functions. <br/>

Output is saved in file: "ProcList.txt"<br/>
Format:<br/>
[return_address]; loaded [Name]<br/>

Example:<br/>
19aa50; loaded: KERNEL32.DLL<br/>
19aa6e; loaded: SystemTimeToFileTime<br/>
19aa6e; loaded: SetEvent<br/>

Usage:<br/>
Use IAT Patcher to hook your program.
