@ECHO OFF
IF EXIST bin  (
cd .
) ELSE (
mkdir bin
ECHO created bin directory!
)
cd bin
@ECHO ON
cmake ..
cmake --build .
@ECHO OFF
cd src/Debug
ECHO. && ECHO.
App.exe