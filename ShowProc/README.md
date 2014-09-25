ShowProc - sample library for IAT Patcher
--
http://hasherezade.net/IAT_patcher<br/>
compile using WinAsm (masm32)<br/>

Purpose:<br/>
-
Prints list of dynamically loaded modules and functions. <br/>

Output is saved in file: "ProcList.txt"<br/>
Format:<br/>
<pre>
[return_address]; loaded [Name]<br/>
</pre>
Example:<br/>
--
<pre>
19aa50; loaded: KERNEL32.DLL
19aa6e; loaded: SystemTimeToFileTime
19aa6e; loaded: SetEvent
</pre>
Usage:<br/>
--
Use IAT Patcher to hook your program.<br/>
<b>Replace:</b><br/>
Kernel32.dll.GetModuleHandleA -> ShowProc.dll.PrintLibNameA<br/>
Kernel32.dll.GetProcAddress -> ShowProc.dll.PrintProcName</br>
