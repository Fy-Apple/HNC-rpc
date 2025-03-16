# 设置头文件搜索路径
include_directories(include)


# 设置源文件
set(SOURCES
        src/hnc_rpc_d.cpp
        src/hnc_rpc_channel.cpp
        src/hnc_rpc_header.pb.cc
        src/hnc_rpc_server.cpp
)


# 生成静态库
add_library(hnc_rpc STATIC ${SOURCES})

target_link_libraries(hnc_rpc muduo_net muduo_base pthread)


## 如果有外部依赖库的话（比如pthread）
#target_link_libraries(hnc_rpc PUBLIC pthread)

# test
add_subdirectory(test)
