#!/bin/bash

# Check if Conan is installed
if command -v conan &> /dev/null; then
    echo "Using Conan for build..."
    conan install . --output-folder=build --build=missing
    cd build
    cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
    cmake --build .
else
    echo "Conan not found, using plain CMake..."
    mkdir -p build
    cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release
    cmake --build .
fi
