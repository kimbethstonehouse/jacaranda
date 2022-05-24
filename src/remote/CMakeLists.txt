cmake_minimum_required(VERSION 3.16)

project(remote)

enable_language(ASM)

set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/compiler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/stubs.S)
add_executable(remote ${SOURCES})
set_property(TARGET remote PROPERTY LINK_OPTIONS "-pthread")
target_link_libraries(remote PRIVATE rpclib)
target_include_directories(remote PRIVATE
        ${INCLUDE_DIR}/remote
        ${INCLUDE_DIR}/shared)
