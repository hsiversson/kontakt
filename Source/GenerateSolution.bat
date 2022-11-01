cd /d %~dp0%

:: Get arguments
for /f "tokens=1,* delims= " %%a in ("%*") do set ALL_BUT_FIRST=%%b

:: Launch Sharpmake
.\Shift\External\Sharpmake\Sharpmake.Application.exe /sources('Kontakt.Main.sharpmake.cs') /projectBaseDirectory(@'.\Source') /useOverrides(false) %ALL_BUT_FIRST%

:: Something went wrong
if %ERRORLEVEL% neq 0 goto ERROR

:: One should not run this script directly, but rather one of the corresponding util scripts.
if [%1]==[] goto ERROR_USAGE

:: Success
goto END

:ERROR
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!
echo Failed to generate projects.
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!

pause
goto END

:ERROR_USAGE
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!
echo Please call one of the platform specific generator scripts.
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!
pause

END:
popd