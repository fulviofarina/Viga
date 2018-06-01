@echo off

call "del.bat"

cd "src"
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64  
set compilerflags=/Od /Zi /EHsc
set linkerflags=/OUT:viga.exe
cl.exe %compilerflags% file.c gnu.c vigaLib.c vigaForzado.c vigaEDO.c viga.c /link %linkerflags%

REM FILE E L W H w0 z0 dx x0 ForN freq forcedFunction
viga.exe "files/viga" 210e+9 1 1e-3 1e-4 0 0 0 1e-3 5 0 2.7e+3 1

REM gnuplot gnu.b
REM gnuplot gnu2.b

gnuplot gnuPlot.gnu
gnuplot gnuSurface.gnu

cd ".."
REM call "del.bat"
