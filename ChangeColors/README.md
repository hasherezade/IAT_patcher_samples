ChangeColors - sample library for IAT Patcher* (C/C++)
--
*http://hasherezade.net/IAT_patcher<br/>

Purpose:<br/>
-
Changes default color set of the hooked application.

Usage:<br/>
--
Use IAT Patcher to hook your program.<br/>

**Replace**:

`GDI32.dll.SetTextColor` -> `MyLib.dll.MyTextColor` (changes text color to a random color)<br/>
`USER32.dll.GetSysColor` -> `MyLib.dll.MySysColor` (applies color set defined in file: `colors.cfg`)<br/>
