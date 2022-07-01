cmake_minimum_required(VERSION 3.16)
project(remote)

enable_language(ASM)

set(SOURCES
        ${REMOTE_DIR}/main.cpp
        ${REMOTE_DIR}/server.cpp
        ${REMOTE_DIR}/compiler.cpp
        ${REMOTE_DIR}/decoder.cpp
        ${REMOTE_DIR}/stubs.S
        ${SHARED_DIR}/section.cpp)
add_executable(remote ${SOURCES})

target_include_directories(remote PRIVATE
        ${INCLUDE_DIR}/remote
        ${INCLUDE_DIR}/proto
        ${INCLUDE_DIR}/shared)

target_link_libraries(remote jitaas_grpc_proto ${llvm_libs})