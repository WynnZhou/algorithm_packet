cmake_minimum_required(VERSION 3.10)
project(hash_table)

# Include Conan-generated files
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(CMAKE_C_STANDARD 11)

add_executable(hash_table
    ../src/hash_table.c
    ../src/main.c
    ../src/prime.c
)

target_include_directories(hash_table PRIVATE 
    ${CMAKE_SOURCE_DIR}/../src
)

# Installation
install(TARGETS hash_table
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY ../src/ DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
