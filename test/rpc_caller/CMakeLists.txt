set(SRC_LIST test_rpc_caller.cpp ../rpc_test.pb.cc)

add_executable(rpc_caller_test ${SRC_LIST})

#find_package(protobuf REQUIRED)
#find_package(absl REQUIRED)

target_link_libraries(rpc_caller_test hnc_rpc protobuf absl::log_internal_check_op)
