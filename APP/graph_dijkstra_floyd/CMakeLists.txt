cmake_minimum_required(VERSION 3.10)
project(graph_dijkstra_floyd)


set(CMAKE_C_STANDARD 11)

# Installation Path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

add_executable(graph_dijkstra_floyd
    ${CMAKE_SOURCE_DIR}/src/graph_dijkstra_floyd.c
    ${CMAKE_SOURCE_DIR}/src/main.c
)

target_include_directories(graph_dijkstra_floyd PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
)
