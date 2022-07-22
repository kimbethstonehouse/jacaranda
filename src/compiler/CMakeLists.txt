cmake_minimum_required(VERSION 3.16)

project(compiler)

enable_language(ASM)

set(SOURCES
        ${COMPILER_DIR}/main.cpp
        ${COMPILER_DIR}/compiler-envoy-client.cpp
        ${COMPILER_DIR}/compiler.cpp
        ${COMPILER_DIR}/decoder.cpp
        ${COMPILER_DIR}/stubs.S
        ${SHARED_DIR}/section.cpp)
add_executable(compiler ${SOURCES})

target_include_directories(compiler PRIVATE
        ${INCLUDE_DIR}/compiler
        ${INCLUDE_DIR}/proto
        ${INCLUDE_DIR}/shared)

target_link_libraries(compiler jacaranda_grpc_proto ${llvm_libs})