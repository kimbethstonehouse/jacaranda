cmake_minimum_required(VERSION 3.16)

project(jitaas)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_GENERATOR "Unix Makefiles")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/exe")

set(REMOTE_DIR "${SOURCE_DIR}/remote")
set(PROTO_DIR "${SOURCE_DIR}/proto")
set(LOCAL_DIR "${SOURCE_DIR}/local")
set(SHARED_DIR "${SOURCE_DIR}/shared")
set(WAVM_DIR "${REMOTE_DIR}/wavm")

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(LLVM REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

# Find the LLVM libraries to link with.
llvm_map_components_to_libnames(llvm_libs
        support
        core
        passes
        orcjit
        RuntimeDyld
        DebugInfoDWARF
        AllTargetsAsmParsers
        ${LLVM_TARGETS_TO_BUILD})

add_subdirectory(src)