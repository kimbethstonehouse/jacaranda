cmake_minimum_required(VERSION 3.16)
project(jitaas)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BINARY_DIR build)

include_directories(include)

add_subdirectory(remote)
add_subdirectory(local)