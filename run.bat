@echo off
pushd %~dp0
echo Y | rmdir .\bin /s /q
call .\premake5.exe vs2022
call MSBuild.exe GLBox.sln -m
call .\bin\Debug\Sandbox.exe
popd