@echo off
setlocal enabledelayexpansion

set "buildtype=Debug"
set "generator=Visual Studio 17 2022"
set "cmakecmdline="

:parse_args
if "%~1"=="" goto end_parse
if "%~1"=="-r" (
    set "buildtype=Release"
) else (
    set "cmakecmdline=%cmakecmdline% %1"
)
shift
goto parse_args
:end_parse

msbuild -version >nul 2>&1
if %errorlevel% neq 0 (
    echo MSBuild not found. Please run from
    echo "Developer Command Prompt for VS 2022".
    exit /b 1
)

md build
cmake -G "%generator" -T ClangCL -B build %cmakecmdline
if %errorlevel% neq 0 exit /b %errorlevel%

echo Building %buildtype%...
cmake --build build --config %buildtype%

echo.
echo Done.