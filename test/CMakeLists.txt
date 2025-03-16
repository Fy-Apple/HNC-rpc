
include_directories(include)


find_package(protobuf REQUIRED)
find_package(absl REQUIRED)

# 服务调用方
add_subdirectory(rpc_caller)

# 服务提供方
add_subdirectory(rpc_server)
