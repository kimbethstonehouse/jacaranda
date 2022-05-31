cmake_minimum_required(VERSION 3.16)

project(local)
enable_language(ASM)

set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/runtime.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/trampoline.S
        ${SOURCE_DIR}/remote/stubs.S
        ${SOURCE_DIR}/shared/section.cpp
        ${SOURCE_DIR}/shared/static-module.cpp
        ${SOURCE_DIR}/shared/runtime-module.cpp)
add_executable(local ${SOURCES})

set_property(TARGET local PROPERTY LINK_OPTIONS "-pthread")
target_include_directories(local PRIVATE
        ${INCLUDE_DIR}/local
        ${INCLUDE_DIR}/proto
        ${INCLUDE_DIR}/shared)

find_package(Protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)
target_link_libraries(local gRPC::grpc++)