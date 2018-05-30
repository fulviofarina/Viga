@echo off

cd "src"
REM call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64  
set compilerflags=/Od /Zi /EHsc
set linkerflags=/OUT:makegnu.exe
cl.exe %compilerflags% gnu.c gnuProg.c file.c /link %linkerflags%

REM d
makegnu.exe 50 "files/viga" "1:2:7" "1:8:2:7" "1" "1" 0

gnuplot gnuPlot.gnu
gnuplot gnuSurface.gnu

cd ".."

