cmake_minimum_required(VERSION 3.16)
project(jitaas)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build")

file(COPY file.wasm DESTINATION ${CMAKE_BINARY_DIR})
file(COPY a.out DESTINATION ${CMAKE_BINARY_DIR})

include_directories(include)

add_subdirectory(src/remote)
add_subdirectory(src/local)