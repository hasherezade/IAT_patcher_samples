ChangeColors - sample library for [IAT Patcher](http://hasherezade.github.io/IAT_patcher/) (C/C++)
---

Purpose:<br/>
-
Changes default color set of the hooked application.

Usage:<br/>
--
Use IAT Patcher to hook your program.<br/>

**Replace**:

`GDI32.dll.SetTextColor` -> `MyLib.dll.MyTextColor` (changes text color to a random color)<br/>
`USER32.dll.GetSysColor` -> `MyLib.dll.MySysColor` (applies color set defined in file: `colors.cfg`)<br/>
