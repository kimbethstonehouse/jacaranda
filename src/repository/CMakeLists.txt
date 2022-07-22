cmake_minimum_required(VERSION 3.16)

project(repository)

set(SOURCES
        ${REPOSITORY_DIR}/repository.cpp
        ${REPOSITORY_DIR}/main.cpp
        ${SHARED_DIR}/section.cpp
        ${SHARED_DIR}/wasm-module.cpp)
add_executable(repository ${SOURCES})

target_include_directories(repository PRIVATE
        ${INCLUDE_DIR}/repository
        ${INCLUDE_DIR}/proto
        ${INCLUDE_DIR}/shared)

target_link_libraries(repository jacaranda_grpc_proto ${llvm_libs})