cmake_minimum_required(VERSION 3.16)
project(jitaas)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build")

add_subdirectory(src)
