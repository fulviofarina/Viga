@echo off

call "del.bat"

cd "src"
REM call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64 
set compilerflags=/Od /Zi /EHsc
set linkerflags=/OUT:makegnu.exe
cl.exe %compilerflags% gnu.c gnuProg.c file.c /link %linkerflags% 
set compilerflags=/Od /Zi /EHsc
set linkerflags=/OUT:viga.exe
cl.exe %compilerflags% file.c gnu.c mathLib.c vigaLib.c vigaForzado.c vigaEDO.c viga.c /link %linkerflags%

REM         FILE        E   L   W   H   x0 dx masaExt tf freqForz density masaDistrib forcedFunction
REM viga.exe "files/vigaAlu" 69e+9 1 1e-3 1e-4 0 1e-3 0.01 5 200 2.7e+3 n 4
REM makegnu.exe 999 "files/vigaAlu" "1:2:7" "1:5:2:7" "5" "0.3" 0 "pics/vigAlu"

REM viga.exe "files/vigaAce" 180e+9 1 1e-3 1e-4 0 1e-3 0.5 5 200 8.05e+3 n 4
REM makegnu.exe 999 "files/vigaAce" "1:2:7" "1:5:2:7" "5" "0.3" 0 "pics/vigAcero"

viga.exe "files/vigaSi" 130e+9 1e-4 1e-8 1e-9 0 1e-7 0.01e-5 1 200 2.328e+3 n 4
makegnu.exe 999 "files/vigaSi" "1:2:7" "1:5:2:7" "5" "0.3" 0 "pics/vigSi"

gnuplot gnuPlot.gnu
gnuplot gnuSurface.gnu



cd ".."
REM call "del.bat"
