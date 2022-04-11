cmake_minimum_required(VERSION 3.16)

project(local)

set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/runtime.cpp
        ${SOURCE_DIR}/wasm/section.cpp
        ${SOURCE_DIR}/wasm/static-module.cpp
        ${SOURCE_DIR}/wasm/runtime-module.cpp)
add_executable(local ${SOURCES})
target_include_directories(local PRIVATE
        ${INCLUDE_DIR}/local
        ${INCLUDE_DIR}/wasm
        ${INCLUDE_DIR}/shared)