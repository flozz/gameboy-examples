echo off

set PROG=graphics3

set GBDK_N=..\gbdk-n
set CC=%GBDK_N%\bin\gbdk-n-compile.bat
set LD=%GBDK_N%\bin\gbdk-n-link.bat
set MR=%GBDK_N%\bin\gbdk-n-make-rom.bat
set IMG2GB=img2gb.exe

:: Clean
if "%1" == "clean" (
    del src\*.rel
    del src\*.lst
    del src\*.sym
    del src\*.asm
    del %PROG%.gb
    del %PROG%.ihx
    del %PROG%.map
    del %PROG%.sym
    del %PROG%.noi
    del %PROG%.lk
    goto end
)

:: assets
if "%1" == "assets" (
    echo "Building assets"
    call %IMG2GB% tileset --output-c-file=src/tileset.c --output-header-file=src/tileset.h --output-image=src/tileset.png --deduplicate tilemap.png
    call %IMG2GB% tilemap --output-c-file=src/tilemap.c --output-header-file=src/tilemap.h src/tileset.png tilemap.png
    goto end
)

:: Check that gbdk-n is available
if not exist %GBDK_N% (
    echo "gbdk-n folder not found at '%GBDK_N%'."
    pause
    goto end
)

:: Check that gbdk-n is compiled
if not exist %GBDK_N%\lib\gb.lib (
    echo "gbdk-n library is not yet compiled. Please go to the '%GBDK_N%' directory and run 'Make.bat' to build it."
    pause
    goto end
)

:: Compile (*.c -> *.res)
for %%A in (src\*.c) do (
    if exist %%~nA.rel del %%~nA.rel
    echo Compiling: %%~nxA
    call %CC% -c src\%%~nA.c -o src\%%~nA.rel
    if not exist src\%%~nA.rel echo. && echo "Build failed!" && echo. && pause && goto end
)

:: Link  (*.rel -> prog.ihx)
setlocal enabledelayedexpansion
set REL_LIST=
for %%A in (src\*.rel) do set REL_LIST=!REL_LiST! %%A

if exist %PROG%.ihx del %PROG%.ihx
echo Linking: %PROG%.ihx
call %LD% -o %PROG%.ihx %REL_LIST%
if not exist %PROG%.ihx echo. && echo "Build failed!" && echo. && pause && goto end

:: Build the ROM (prog.ihx -> prog.gb)
if exist %PROG%.gb del %PROG%.gb
echo Building ROM: %PROG%.gb
call %MR% %PROG%.ihx %PROG%.gb
if not exist %PROG%.gb echo. && echo "Build failed!" && echo. && pause && goto end

echo "Build succeded!"

:end
