@echo off
setlocal

set "ROOT=%~dp0"
set "BUILD_DIR=%ROOT%build"
set "OUTPUT=%BUILD_DIR%\air_quality_monitor.exe"

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

gcc -std=c11 -Wall -Wextra -Werror -I"%ROOT%src" "%ROOT%src\aq_monitor.c" "%ROOT%src\main.c" -o "%OUTPUT%"
if errorlevel 1 exit /b %errorlevel%

"%OUTPUT%"
