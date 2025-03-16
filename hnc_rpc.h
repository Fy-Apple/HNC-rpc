#pragma once

#include "hnc_rpc_server.h"
#include "hnc_rpc_d.h"
#include "hnc_rpc_channel.h"
#include "hnc_log.h"

namespace hnc::rpc{

// TODO : 添加全局配置文件读取, 并初始化 rpc 框架

/**
 * @brief 负责初始化rpc框架的一些参数， 后续添加 全局配置读取器
 */
inline void rpc_init() {
    core::logger::log_debug("rpc init!");
    details::HncRpc::init();
}

inline details::HncRpcChannel* get_rpc_channel() {
    core::logger::log_debug("create hnc_rpc_channel");
    return new details::HncRpcChannel;
}

/**
 * @brief 全局提供 rpc 服务器 接口， 返回 一个shared_ptr 服务器的智能指针
 */
inline std::shared_ptr<details::HncRpcServer> get_rpc_server() {
    core::logger::log_debug("get rpc_server");
    return std::make_shared<details::HncRpcServer>();
}




}
