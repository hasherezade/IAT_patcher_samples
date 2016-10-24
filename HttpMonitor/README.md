ChangeColors - sample library for IAT Patcher* (C/C++)
--
*http://hasherezade.net/IAT_patcher<br/>

Purpose:<br/>
-
Changes default color set of the hooked application.

Usage:<br/>
--
Use IAT Patcher to hook your program.<br/>
<b>Replace:</b><br/>
GDI32.dll.SetTextColor -> MyLib.dll.MyTextColor (changes text color to a random color)<br/>
USER32.dll.GetSysColor -> MyLib.dll.MySysColor (applies color set defined in file: colors.cfg)<br/>

Compiled:
--
+ http://hasherezade.net/IAT_patcher/sample/32b/MyLib.dll
+ http://hasherezade.net/IAT_patcher/sample/64b/MyLib.dll

Sample result of patching:
---
![](http://hasherezade.net/IAT_patcher/pics/iat_p3.png)
