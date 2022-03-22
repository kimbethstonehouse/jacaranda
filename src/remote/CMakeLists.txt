cmake_minimum_required(VERSION 3.16)

project(remote)

set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/compiler.cpp)
add_executable(remote ${SOURCES})
target_include_directories(remote PRIVATE
        ${INCLUDE_DIR}/remote
        ${INCLUDE_DIR}/shared)
