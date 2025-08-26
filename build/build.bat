@echo off

:: 确保从项目根目录执行
cd /d %~dp0..
if not exist "APP" (
    echo Error: Please run from algorithm_packet root directory
    exit /b 1
)

set PROJECTS=binary_indexed_tree graph_dijkstra_floyd hash_table union_find_sets

for %%p in (%PROJECTS%) do (
    echo ====================================
    echo Building %%p...
    echo ====================================
    
    if not exist "APP\%%p\build\build.bat" (
        echo Error: Missing build.bat in APP\%%p\build
        exit /b 1
    )
    
    cd APP\%%p\build
    if %ERRORLEVEL% neq 0 (
        echo Error: Failed to enter %%p build directory
        exit /b 1
    )
    
    call build.bat --no-remote
    if %ERRORLEVEL% neq 0 (
        echo Error: %%p build failed
        exit /b 1
    )
    
    cd ..\..\..
    echo %%p build completed
    echo.
)

echo All projects built successfully
