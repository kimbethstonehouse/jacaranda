cmake_minimum_required(VERSION 3.16)

project(proto)

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)
set(_PROTOBUF_PROTOC protoc)
set(_GRPC_CPP_PLUGIN_EXECUTABLE `which grpc_cpp_plugin`)

# Proto file
get_filename_component(jacaranda_proto "${SOURCE_DIR}/proto/jacaranda.proto" ABSOLUTE)
get_filename_component(jacaranda_proto_path "${jacaranda_proto}" PATH)

# Generated sources
set(jacaranda_proto_srcs "${INCLUDE_DIR}/proto/jacaranda.pb.cc")
set(jacaranda_proto_hdrs "${INCLUDE_DIR}/proto/jacaranda.pb.h")
set(jacaranda_grpc_srcs "${INCLUDE_DIR}/proto/jacaranda.grpc.pb.cc")
set(jacaranda_grpc_hdrs "${INCLUDE_DIR}/proto/jacaranda.grpc.pb.h")
add_custom_command(
        OUTPUT "${jacaranda_proto_srcs}" "${jacaranda_proto_hdrs}" "${jacaranda_grpc_srcs}" "${jacaranda_grpc_hdrs}"
        COMMAND ${_PROTOBUF_PROTOC}
        ARGS --grpc_out "${INCLUDE_DIR}/proto"
        --cpp_out "${INCLUDE_DIR}/proto"
        -I "${jacaranda_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${jacaranda_proto}"
        DEPENDS "${jacaranda_proto}")

# Include generated *.pb.h files
include_directories("${SOURCE_DIR}" PUBLIC)

add_library(jacaranda_grpc_proto
        ${jacaranda_grpc_srcs}
        ${jacaranda_grpc_hdrs}
        ${jacaranda_proto_srcs}
        ${jacaranda_proto_hdrs})

target_link_libraries(jacaranda_grpc_proto
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF})