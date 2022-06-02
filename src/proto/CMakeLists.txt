cmake_minimum_required(VERSION 3.16)
project(proto)

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)
set(_PROTOBUF_PROTOC protoc)
set(_GRPC_CPP_PLUGIN_EXECUTABLE `which grpc_cpp_plugin`)

# Proto file
get_filename_component(jitaas_proto "${SOURCE_DIR}/proto/jitaas.proto" ABSOLUTE)
get_filename_component(jitaas_proto_path "${jitaas_proto}" PATH)

# Generated sources
set(jitaas_proto_srcs "${INCLUDE_DIR}/proto/jitaas.pb.cc")
set(jitaas_proto_hdrs "${INCLUDE_DIR}/proto/jitaas.pb.h")
set(jitaas_grpc_srcs "${INCLUDE_DIR}/proto/jitaas.grpc.pb.cc")
set(jitaas_grpc_hdrs "${INCLUDE_DIR}/proto/jitaas.grpc.pb.h")
add_custom_command(
        OUTPUT "${jitaas_proto_srcs}" "${jitaas_proto_hdrs}" "${jitaas_grpc_srcs}" "${jitaas_grpc_hdrs}"
        COMMAND ${_PROTOBUF_PROTOC}
        ARGS --grpc_out "${INCLUDE_DIR}/proto"
        --cpp_out "${INCLUDE_DIR}/proto"
        -I "${jitaas_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${jitaas_proto}"
        DEPENDS "${jitaas_proto}")

# Include generated *.pb.h files
include_directories("${SOURCE_DIR}" PUBLIC)

add_library(jitaas_grpc_proto
        ${jitaas_grpc_srcs}
        ${jitaas_grpc_hdrs}
        ${jitaas_proto_srcs}
        ${jitaas_proto_hdrs})
target_link_libraries(jitaas_grpc_proto
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF})