@echo off
setlocal enabledelayedexpansion

:: 确保从项目根目录执行
cd /d %~dp0..
if not exist "APP" (
    echo Error: Please run from algorithm_packet root directory
    exit /b 1
)

:: 自动检测APP目录下的模块
set module_count=0
set module_list=
for /d %%i in (APP\*) do (
    set /a module_count+=1
    set "module_!module_count!=%%~nxi"
    set "module_list=!module_list! %%~nxi"
)
set module_list=!module_list:~1!

:menu
cls
echo ====================================
echo    Algorithm Packet Build System
echo ====================================
echo.
echo Available modules in APP directory:
set i=0
for %%m in (%module_list%) do (
    set /a i+=1
    echo [!i!] %%m
)
set /a all_option=i+1
set /a clear_option=i+2
set /a exit_option=i+3

echo [!all_option!] ALL - Build all modules
echo [!clear_option!] CLEAR - Clean build directories
echo [!exit_option!] Exit
echo.
set /p choice="Please select an option (1-!exit_option!): "

:: 验证输入
set valid_choice=0
for /l %%j in (1,1,!i!) do (
    if "!choice!"=="%%j" set valid_choice=1
)
if "!choice!"=="!all_option!" set valid_choice=1
if "!choice!"=="!clear_option!" set valid_choice=1
if "!choice!"=="!exit_option!" set valid_choice=1

if !valid_choice! equ 0 (
    echo Invalid choice! Please try again.
    pause
    goto menu
)

:: 处理选择
if "!choice!"=="!all_option!" goto build_all
if "!choice!"=="!clear_option!" goto clean_all
if "!choice!"=="!exit_option!" goto exit_program

:: 构建单个模块
set j=0
for %%m in (%module_list%) do (
    set /a j+=1
    if "!choice!"=="!j!" (
        call :build_module %%m
        goto menu
    )
)

:build_all
for %%m in (%module_list%) do (
    call :build_module %%m
)
goto menu

:clean_all
for %%m in (%module_list%) do (
    call :clean_module %%m
)
goto menu

:build_module
set module=%~1
echo.
echo ====================================
echo Building !module!...
echo ====================================

if not exist "APP\!module!" (
    echo Error: Project directory APP\!module! does not exist
    pause
    exit /b 1
)

:: 检查是否是有效的算法模块（包含CMakeLists.txt）
if not exist "APP\!module!\CMakeLists.txt" (
    echo Warning: APP\!module! does not contain CMakeLists.txt, skipping...
    pause
    exit /b 0
)

:: 进入项目目录
cd APP\!module!
if !ERRORLEVEL! neq 0 (
    echo Error: Failed to enter !module! directory
    pause
    exit /b 1
)

:: 创建build目录（如果不存在）
if not exist "build" (
    mkdir build
    if !ERRORLEVEL! neq 0 (
        echo Error: Failed to create build directory for !module!
        pause
        exit /b 1
    )
)

:: 进入build目录
cd build
if !ERRORLEVEL! neq 0 (
    echo Error: Failed to enter build directory for !module!
    pause
    exit /b 1
)

:: 使用Conan构建
echo Running Conan install...
conan install .. --build=missing --no-remote
if !ERRORLEVEL! neq 0 (
    echo Error: Conan install failed for !module!
    pause
    exit /b 1
)

:: 运行CMake配置
echo Running CMake configure...
cmake .. -DCMAKE_BUILD_TYPE=Release
if !ERRORLEVEL! neq 0 (
    echo Error: CMake configure failed for !module!
    pause
    exit /b 1
)

:: 运行CMake构建
echo Running CMake build...
cmake --build . --config Release
if !ERRORLEVEL! neq 0 (
    echo Error: CMake build failed for !module!
    pause
    exit /b 1
)

:: 返回项目根目录
cd ..\..\..
if !ERRORLEVEL! neq 0 (
    echo Error: Failed to return to project root directory
    pause
    exit /b 1
)

echo !module! build completed successfully!
echo Output files are in APP\!module!\bin\ directory
echo.
pause
exit /b 0

:clean_module
set module=%~1
echo.
echo ====================================
echo Cleaning !module!...
echo ====================================

:: 清理构建目录（包含CMake缓存和临时文件）
if exist "APP\!module!\build" (
    echo Removing build directory for !module!...
    rmdir /s /q "APP\!module!\build"
    echo Build directory removed.
) else (
    echo No build directory found for !module!.
)

:: 清理可执行文件目录
if exist "APP\!module!\bin" (
    echo Removing bin directory for !module!...
    rmdir /s /q "APP\!module!\bin"
    echo Bin directory removed.
) else (
    echo No bin directory found for !module!.
)

:: 清理库文件目录
if exist "APP\!module!\lib" (
    echo Removing lib directory for !module!...
    rmdir /s /q "APP\!module!\lib"
    echo Lib directory removed.
) else (
    echo No lib directory found for !module!.
)

echo !module! cleanup completed!
echo.
exit /b 0

:exit_program
echo.
echo Thank you for using Algorithm Packet Build System!
echo.
pause
exit /b 0
