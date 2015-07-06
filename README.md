# preemy

Like preeny( https://github.com/zardus/preeny ), but for Microsoft Windows instead of *nix.

A series of injectable DLLs, and an interface to load them into executables via AppInit_DLL.


# What works( and what doesn't )

Currently, the magic that is Windows on Windows virtualization is making it so I can not automatically
enable AppInit_DLLs and load in the requested modules, so that must be done manually.

## To enable AppInit_DLLs
1. Open regedit.exe
2. Navigate to HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Windows
3. Modify/create the key LoadAppInit_DLLs, setting it to 1.
4. Modify/create the key RequireSignedAppInit_DLLs, setting it to 0. Both of these keys are DWORD types.

## To include a DLL
1. Using short.bat, convert the path to the desired DLL to the shortened version
2. Add this shortened path to the key AppInit_DLLs, seperating DLLs by commas.
* Example: C:\PROGR~1\file1.dll, C:\PROGR~1\file2.dll