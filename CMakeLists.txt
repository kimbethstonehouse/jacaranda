cmake_minimum_required(VERSION 3.16)

project(jacaranda)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_GENERATOR "Unix Makefiles")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
#set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/exe")

set(REPOSITORY_DIR "${SOURCE_DIR}/repository")
set(COMPILER_DIR "${SOURCE_DIR}/compiler")
set(RUNTIME_DIR "${SOURCE_DIR}/runtime")
set(SHARED_DIR "${SOURCE_DIR}/shared")
set(PROTO_DIR "${SOURCE_DIR}/proto")
set(ASMJIT_H "${CMAKE_CURRENT_SOURCE_DIR}/asmjit/src/asmjit")

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(LLVM REQUIRED CONFIG)

if(LLVM_VERSION_MAJOR LESS 6)
    message(FATAL_ERROR "At least version 6.0 of LLVM required")
endif()

include_directories(${LLVM_INCLUDE_DIRS} ${ASMJIT_H})
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

set(ASMJIT_BUILD_STATIC)

add_subdirectory(src)
add_subdirectory(asmjit)