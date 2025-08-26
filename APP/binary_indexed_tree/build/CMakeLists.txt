cmake_minimum_required(VERSION 3.10)
project(binary_indexed_tree)

# Include Conan-generated files
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(CMAKE_C_STANDARD 11)

add_executable(binary_indexed_tree
    ../src/binary_indexed_tree.c
    ../src/main.c
)

target_include_directories(binary_indexed_tree PRIVATE 
    ${CMAKE_SOURCE_DIR}/../src
)

# Installation
install(TARGETS binary_indexed_tree
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY ../src/ DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
