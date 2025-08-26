cmake_minimum_required(VERSION 3.10)
project(graph_dijkstra_floyd)

# Include Conan-generated files
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(CMAKE_C_STANDARD 11)

add_executable(graph_dijkstra_floyd
    ../src/graph_dijkstra_floyd.c
    ../src/main.c
)

target_include_directories(graph_dijkstra_floyd PRIVATE 
    ${CMAKE_SOURCE_DIR}/../src
)

# Installation
install(TARGETS graph_dijkstra_floyd
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY ../src/ DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
