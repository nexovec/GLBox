@echo off
pushd %~dp0
echo Y | rmdir .\bin /s /q
call .\premake5.exe vs2022
if not defined DevEnvDir (
    call vcvarsall.bat x64
)
@REM MSBuild.exe GLBox.sln -m -t:Clean
call MSBuild.exe GLBox.sln -m /p:Platform="Win64" /p:Configuration=Release
call .\bin\Release\Sandbox.exe
popd