cmake_minimum_required(VERSION 3.16)

project(runtime)

enable_language(ASM)

set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/runtime.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/runtime-envoy.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/trampoline.S)
add_executable(runtime ${SOURCES})

target_include_directories(runtime PRIVATE
        ${INCLUDE_DIR}/runtime
        ${INCLUDE_DIR}/proto
        ${INCLUDE_DIR}/shared)

target_link_libraries(runtime jacaranda_grpc_proto ${llvm_libs})