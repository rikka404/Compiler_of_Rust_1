@echo off
call make run
call gcc32 obj\main.s obj\io.c -o obj\out.exe
echo ================= START out.exe =================
obj\out.exe
echo ================== END out.exe ==================