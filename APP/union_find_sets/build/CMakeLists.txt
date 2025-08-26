cmake_minimum_required(VERSION 3.10)
project(union_find_sets)

# Include Conan-generated files
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(CMAKE_C_STANDARD 11)

add_executable(union_find_sets
    ../src/union_find_sets.c
    ../src/main.c
)

target_include_directories(union_find_sets PRIVATE 
    ${CMAKE_SOURCE_DIR}/../src
)

# Installation
install(TARGETS union_find_sets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY ../src/ DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
