@echo off
setlocal

set MSBUILD="C:\Program Files\Microsoft Visual Studio\18\Insiders\MSBuild\Current\Bin\amd64\MSBuild.exe"
set SLN=%~dp0Genshin.Fps.UnlockerIsland.sln

echo ============================================
echo   CUTTOOL - Build Tool
echo ============================================
echo.

if not exist %MSBUILD% (
    echo [ERROR] MSBuild not found at:
    echo         %MSBUILD%
    echo.
    echo Please install Visual Studio with C++ Desktop workload.
    pause
    exit /b 1
)

echo [*] Building Release x64...
echo.

%MSBUILD% "%SLN%" /t:Build /p:Configuration=Release /p:Platform=x64 /p:BuildInParallel=true /m /nologo /verbosity:minimal

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
    echo [DebugConsole]
    echo Value=0
    echo.
    echo [FpsUnlock]
    echo Value=0
    echo.
    echo [TargetFps]
    echo Value=60
    echo.
    echo [VSync]
    echo Value=1
    echo.
    echo [FovUnlock]
    echo Value=0
    echo.
    echo [FovValue]
    echo Value=45.0
    echo.
    echo [DisableCameraMove]
    echo Value=0
    echo.
    echo [RemoveTeamAnim]
    echo Value=0
    echo.
    echo [DisableFog]
    echo Value=0
    echo.
    echo [HideUID]
    echo Value=0
    echo.
    echo [BlockNetwork]
    echo Value=0
    echo.
    echo [EnableNetworkToggle]
    echo Value=0
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
) else (
    echo.
    echo ============================================
    echo   BUILD FAILED! Check errors above.
    echo ============================================
    echo.
)

pause
endlocal
