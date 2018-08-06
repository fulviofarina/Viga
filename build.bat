@echo off

call "del.bat"

cd "src"
REM call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64 
set compilerflags=/Od /Zi /EHsc
set linkerflags=/OUT:makegnu.exe
cl.exe %compilerflags% gnu.c gnuProg.c file.c /link %linkerflags% 
set compilerflags=/Od /Zi /EHsc
set linkerflags=/OUT:viga.exe
cl.exe %compilerflags% file.c gnu.c mathLib.c vigaLib.c vigaForzado.c vigaEDO.c vigaEngine.c viga.c /link %linkerflags%

REM         FILE        E   L   W   H   x0 dx masaExt tf freqForz density masaDistrib forcedFunction
REM viga.exe "files/vigaAlu" 69e+9 1 1e-3 1e-4 0 1000 0.01 5 200 2.7e+3 n 4
REM makegnu.exe 999 "files/vigaAlu" "1:2:7" "1:5:2:7" "5" "0.3" 0 "pics/vigAlu"

REM viga.exe "files/vigaAce" 180e+9 1 1e-3 1e-4 0 1000 0.5 5 200 8.05e+3 n 4
REM makegnu.exe 999 "files/vigaAce" "1:2:7" "1:5:2:7" "5" "0.3" 0 "pics/vigAcero"
REM         FILE        t L  W     H x0 xCel masaExt freqForz masaDistrib indice E G density
REM viga.exe "files/vigaSi" 1 1 1e-3 1e-4 0 1000 1e-3 100 n 4 130e+9 25.56e+9 2.328e+3
viga.exe "files/vigaAce.1e-2" 1 1 1e-3 1e-4 0 50 1e-2 2 n 4 180e+9 79.56e+9 8.05e+3
makegnu.exe 999 "files/vigaAce.1e-2" "1:2:4" "1:5:2:4" "5" "0.3" 0 "pics/vigaAce.1e-2"
gnuplot gnuPlot.gnu
gnuplot gnuSurface.gnu

cd ".."
REM call "del.bat"
