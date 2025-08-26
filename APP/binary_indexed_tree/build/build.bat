@echo off
setlocal

:: 检查是否在正确目录
if not exist "conanfile.py" (
    echo Error: Must run from project build directory
    exit /b 1
)

:: 使用Conan构建
conan install . --build=missing --no-remote
if %ERRORLEVEL% neq 0 (
    echo Error: Conan install failed
    exit /b 1
)

:: 运行CMake构建
cmake --build . --config Release
if %ERRORLEVEL% neq 0 (
    echo Error: CMake build failed
    exit /b 1
)

endlocal
