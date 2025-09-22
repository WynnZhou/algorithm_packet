cmake_minimum_required(VERSION 3.10)
project(union_find_sets)

set(CMAKE_C_STANDARD 11)

# Installation Path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

add_executable(union_find_sets
    ${CMAKE_SOURCE_DIR}/src/union_find_sets.c
    ${CMAKE_SOURCE_DIR}/src/main.c
)

target_include_directories(union_find_sets PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
)