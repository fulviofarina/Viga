@echo off

call "del.bat"

cd "src"
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64 
set compilerflags=/Od /Zi /EHsc
set linkerflags=/OUT:makegnu.exe
cl.exe %compilerflags% gnu.c gnuProg.c file.c /link %linkerflags% 
set compilerflags=/Od /Zi /EHsc
set linkerflags=/OUT:viga.exe
cl.exe %compilerflags% file.c gnu.c mathLib.c vigaLib.c vigaForzado.c vigaEDO.c viga.c /link %linkerflags%

REM         FILE        E   L   W   H   x0 dx masaExt tf freqForz density masaDistrib forcedFunction
viga.exe "files/viga" 69e+9 1 1e-3 1e-4 0 1e-3 1 5 200 2.7e+3 n 1
makegnu.exe 999 "files/viga" "1:2:7" "1:5:2:7" "1" "1" 0 "pics/vigAluminio"
gnuplot gnuPlot.gnu
gnuplot gnuSurface.gnu



cd ".."
REM call "del.bat"
