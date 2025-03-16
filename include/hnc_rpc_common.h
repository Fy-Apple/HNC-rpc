#pragma once

#include <string>

namespace hnc::rpc::details::constant {
// 设置 rpc 服务器监听的 ip和端口
// TODO : 后续将所有参数 通过配置文件去读取
constexpr std::string RPC_SEVER_IP = "127.0.0.1";
constexpr std::string RPC_SEVER_PORT = "9096";

}