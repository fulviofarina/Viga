@echo off
del *.gif
call "del.bat"
REM call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64  

set compilerflags=/Od /Zi /EHsc
set linkerflags=/OUT:viga.exe
cl.exe %compilerflags% file.c gnu.c vigaLib.c vigaForzado.c vigaEDO.c viga.c /link %linkerflags%
REM FILE E L W H w0 z0 dx x0 ForN freq forcedFunction
viga.exe "viga" 210e+9 1 0.02 0.02 0 0 0 0.001 n 6.2832 1

REM gnuplot gnu.b
REM gnuplot gnu2.b

gnuplot gnuFinal.gnu

REM call "del.bat"