@echo off

call "del.bat"

cd "src"
 REM call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64  
set compilerflags=/Od /Zi /EHsc
set linkerflags=/OUT:viga.exe
cl.exe %compilerflags% file.c gnu.c vigaLib.c vigaForzado.c vigaEDO.c viga.c /link %linkerflags%

REM         FILE        E   L   W   H   x0 dx masaExtremo freqNat freqForz density masaDistrib forcedFunction
REM viga.exe "files/viga" 69e+9 1 1e-3 1e-4 0 1e-3 0.001 2 1 2.7e+3 0 1
viga.exe "files/viga" 69e+9 1 1e-1 1e-4 0 1e-2 5 1 0 2.7e+3 n 1
REM gnuplot gnu.b
REM gnuplot gnu2.b

gnuplot gnuPlot.gnu
gnuplot gnuSurface.gnu

cd ".."
REM call "del.bat"
