@echo off
call make run
call gcc32 obj\src\main.s obj\src\io.s -o obj\out.exe
echo ================= START out.exe =================
obj\out.exe
set EXITCODE=%ERRORLEVEL%
echo ================== END out.exe ==================
if %EXITCODE% NEQ 0 (
    echo [ERROR] out.exe exited with code %EXITCODE%.
    exit /b %EXITCODE%
) else (
    echo [OK] out.exe exited normally.
)
