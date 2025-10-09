cmake_minimum_required(VERSION 3.28)
project(Hands-On_Network_Programming_with_C)

add_compile_options(-Wall)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

option(ALL_ON "Build all" OFF)
option(C_TOBITS "Build 'C. ToBits'-exp" ON)
add_subdirectory("3rdparty/C-CPP-Experiments")

add_subdirectory("1. list_network_nodes")
