set(SRC_LIST test_rpc_server.cpp ../rpc_test.pb.cc)

add_executable(test_rpc_server ${SRC_LIST})

#find_package(protobuf REQUIRED)
#find_package(absl REQUIRED)

target_link_libraries(test_rpc_server hnc_rpc protobuf absl::log_internal_check_op)
