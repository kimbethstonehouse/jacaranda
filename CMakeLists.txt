cmake_minimum_required(VERSION 3.16)
project(jitaas)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_GENERATOR "Unix Makefiles")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/exe")

#list(APPEND CMAKE_PREFIX_PATH "/home/kim/.local/bin")
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

add_subdirectory(src)
