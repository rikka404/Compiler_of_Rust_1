@echo off
setlocal enabledelayedexpansion

set args=

:loop
if "%~1"=="" goto afterloop

set param=%~1

REM 判断是不是选项（以 - 开头）
set firstChar=!param:~0,1!
if "!firstChar!"=="-" (
    REM 是选项参数，不转换
    set args=!args! "%param%"
) else (
    REM 路径参数，统一转换成 Linux 绝对路径
    for /f "usebackq delims=" %%i in (`C:\msys64\usr\bin\bash.exe -c "cygpath -a '%param%'"`) do (
        set converted=%%i
    )
    set args=!args! "!converted!"
)

shift
goto loop

:afterloop

REM 显示转换后的命令
echo Running: gcc !args!

REM 执行编译
C:\msys64\usr\bin\env MSYSTEM=MINGW32 C:\msys64\usr\bin\bash.exe -lc "gcc !args!"

REM endlocal
