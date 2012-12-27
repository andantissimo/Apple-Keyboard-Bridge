@echo off

set OUTPUT=bin\Release
set TARGET=bin\akb
if exist %OUTPUT%\akb.exe (
	if not exist %TARGET% mkdir %TARGET%
	copy /y doc\akb.txt %TARGET%\ > nul
	copy /y %OUTPUT%\akb.exe %TARGET%\ > nul
	copy /y %OUTPUT%\akbcf.exe %TARGET%\ > nul
)
