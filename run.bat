@echo off
pushd %~dp0
echo Y | rmdir .\bin /s /q
call MSBuild.exe GLBox.sln -m
call .\bin\Debug\Sandbox.exe
popd