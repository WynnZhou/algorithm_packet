cmake_minimum_required(VERSION 3.10)
project(binary_indexed_tree)

set(CMAKE_C_STANDARD 11)

# Installation Path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

add_executable(binary_indexed_tree
    ${CMAKE_SOURCE_DIR}/src/binary_indexed_tree.c
    ${CMAKE_SOURCE_DIR}/src/main.c
)

target_include_directories(binary_indexed_tree PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
)