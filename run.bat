IF EXIST bin  (
ECHO.
) ELSE (
mkdir bin
ECHO created bin directory!
)
cd bin && cmake .. && cmake --build . && cd src/Debug && ECHO. && ECHO. && hello.exe