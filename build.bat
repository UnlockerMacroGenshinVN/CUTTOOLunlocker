@echo off
setlocal

set MSBUILD="C:\Program Files\Microsoft Visual Studio\18\Enterprise\MSBuild\Current\Bin\amd64\MSBuild.exe"
set SLN=%~dp0Genshin.Fps.UnlockerIsland.sln
set VCTargetsPath=C:\Program Files\Microsoft Visual Studio\18\Enterprise\MSBuild\Microsoft\VC\v170\

echo ============================================
echo   CUTTOOL - Build Tool
echo ============================================
echo.

if not exist %MSBUILD% (
    echo [ERROR] MSBuild not found at:
    echo         %MSBUILD%
    echo.
    echo Please install Visual Studio 2022 with C++ Desktop workload.
    pause
    exit /b 1
)

echo [*] Building Release x64...
echo.

%MSBUILD% "%SLN%" /t:Build /p:Configuration=Release /p:Platform=x64 /p:PlatformToolset=v143 /p:BuildInParallel=true /m /nologo /verbosity:minimal

if %ERRORLEVEL% == 0 (
    echo.
    echo ============================================
    echo   BUILD SUCCEEDED!
    echo ============================================
    echo.
    echo Output files:
    echo   %~dp0x64\Release\CUTTOOL.UnlockerIsland.dll
    echo   %~dp0x64\Release\Launcher.dll
    echo   %~dp0x64\Release\Launcher_2.exe
    echo.
    echo [*] Generating config.ini...
    (
    echo File=CUTTOOL.UnlockerIsland.dll
    echo.
    echo [DebugConsole]
    echo Value=0
    echo.
    echo [ShowFps]
    echo Value=1
    echo.
    echo [FpsUnlock]
    echo Value=1
    echo.
    echo [TargetFps]
    echo Value=120
    echo.
    echo [VSync]
    echo Value=0
    echo.
    echo [FovUnlock]
    echo Value=1
    echo.
    echo [FovValue]
    echo Value=55.0
    echo.
    echo [DisableCameraMove]
    echo Value=1
    echo.
    echo [RemoveTeamAnim]
    echo Value=1
    echo.
    echo [DisableFog]
    echo Value=1
    echo.
    echo [HideUID]
    echo Value=1
    echo.
    echo [BlockNetwork]
    echo Value=0
    echo.
    echo [EnableNetworkToggle]
    echo Value=1
    echo.
    echo [NetworkToggleKey]
    echo Value=122
    echo.
    echo [ToggleKey]
    echo Value=36
    echo.
    echo [DumpOffsets]
    echo Value=0
    ) > "%~dp0x64\Release\config.ini"
    echo   %~dp0x64\Release\config.ini
    echo.
    echo [*] Deploying files to root and Plugins...
    copy /Y "%~dp0x64\Release\Launcher_2.exe" "%~dp0Launcher_2.exe" >nul
    copy /Y "%~dp0x64\Release\Launcher.dll" "%~dp0Launcher.dll" >nul
    copy /Y "%~dp0x64\Release\CUTTOOL.UnlockerIsland.dll" "%~dp0CUTTOOL.UnlockerIsland.dll" >nul
    if not exist "%~dp0Plugins\UnlockerIsland" mkdir "%~dp0Plugins\UnlockerIsland"
    copy /Y "%~dp0x64\Release\CUTTOOL.UnlockerIsland.dll" "%~dp0Plugins\UnlockerIsland\CUTTOOL.UnlockerIsland.dll" >nul
    copy /Y "%~dp0x64\Release\config.ini" "%~dp0Plugins\UnlockerIsland\config.ini" >nul
    echo   -> Updated root Launcher_2.exe and CUTTOOL.UnlockerIsland.dll
    echo   -> Updated Plugins\UnlockerIsland\CUTTOOL.UnlockerIsland.dll
    echo   -> Updated Plugins\UnlockerIsland\config.ini

    if exist "D:\GSVNUNLOCKER\Skirk-macro\build\app\CUTTOOL\resources\unlocker" (
        echo.
        echo [*] Auto-syncing to Skirk-macro build app...
        copy /Y "%~dp0x64\Release\Launcher_2.exe" "D:\GSVNUNLOCKER\Skirk-macro\build\app\CUTTOOL\resources\unlocker\Launcher_2.exe" >nul
        copy /Y "%~dp0x64\Release\Launcher.dll" "D:\GSVNUNLOCKER\Skirk-macro\build\app\CUTTOOL\resources\unlocker\Launcher.dll" >nul
        copy /Y "%~dp0x64\Release\CUTTOOL.UnlockerIsland.dll" "D:\GSVNUNLOCKER\Skirk-macro\build\app\CUTTOOL\resources\unlocker\CUTTOOL.UnlockerIsland.dll" >nul
        if not exist "D:\GSVNUNLOCKER\Skirk-macro\build\app\CUTTOOL\resources\unlocker\Plugins\UnlockerIsland" mkdir "D:\GSVNUNLOCKER\Skirk-macro\build\app\CUTTOOL\resources\unlocker\Plugins\UnlockerIsland"
        del /F /Q "D:\GSVNUNLOCKER\Skirk-macro\build\app\CUTTOOL\resources\unlocker\Plugins\UnlockerIsland\CUTTOOL.UnlockerIsland.dll.old" >nul 2>&1
        move /Y "D:\GSVNUNLOCKER\Skirk-macro\build\app\CUTTOOL\resources\unlocker\Plugins\UnlockerIsland\CUTTOOL.UnlockerIsland.dll" "D:\GSVNUNLOCKER\Skirk-macro\build\app\CUTTOOL\resources\unlocker\Plugins\UnlockerIsland\CUTTOOL.UnlockerIsland.dll.old" >nul 2>&1
        copy /Y "%~dp0x64\Release\CUTTOOL.UnlockerIsland.dll" "D:\GSVNUNLOCKER\Skirk-macro\build\app\CUTTOOL\resources\unlocker\Plugins\UnlockerIsland\CUTTOOL.UnlockerIsland.dll" >nul
        echo   -> Updated Skirk-macro build app CUTTOOL.UnlockerIsland.dll
        echo   -> Updated Skirk-macro build app Plugins\UnlockerIsland\CUTTOOL.UnlockerIsland.dll
    )

    if exist "D:\GSVNUNLOCKER\Skirk-macro\src\unlocker" (
        echo [*] Auto-syncing to Skirk-macro src...
        copy /Y "%~dp0x64\Release\Launcher_2.exe" "D:\GSVNUNLOCKER\Skirk-macro\src\unlocker\Launcher_2.exe" >nul
        copy /Y "%~dp0x64\Release\Launcher.dll" "D:\GSVNUNLOCKER\Skirk-macro\src\unlocker\Launcher.dll" >nul
        copy /Y "%~dp0x64\Release\CUTTOOL.UnlockerIsland.dll" "D:\GSVNUNLOCKER\Skirk-macro\src\unlocker\CUTTOOL.UnlockerIsland.dll" >nul
        if not exist "D:\GSVNUNLOCKER\Skirk-macro\src\unlocker\Plugins\UnlockerIsland" mkdir "D:\GSVNUNLOCKER\Skirk-macro\src\unlocker\Plugins\UnlockerIsland"
        copy /Y "%~dp0x64\Release\CUTTOOL.UnlockerIsland.dll" "D:\GSVNUNLOCKER\Skirk-macro\src\unlocker\Plugins\UnlockerIsland\CUTTOOL.UnlockerIsland.dll" >nul
        echo   -> Updated Skirk-macro src Plugins\UnlockerIsland\CUTTOOL.UnlockerIsland.dll
    )
    echo.
) else (
    echo.
    echo ============================================
    echo   BUILD FAILED! Check errors above.
    echo ============================================
    echo.
)

if not "%1" == "/nopause" pause
endlocal
