cmake_minimum_required(VERSION 3.10)
project(hash_table)

set(CMAKE_C_STANDARD 11)

# Installation Path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

add_executable(hash_table
    ${CMAKE_SOURCE_DIR}/src/prime.c
    ${CMAKE_SOURCE_DIR}/src/hash_table.c
    ${CMAKE_SOURCE_DIR}/src/main.c
)

target_include_directories(hash_table PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
)