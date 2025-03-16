#include "hnc_rpc_d.h"
#include "hnc_rpc_common.h"


#include <iostream>




namespace hnc::rpc::details {
// 静态变量全局初始化
HncRpc HncRpc::app;
std::unordered_map<std::string, std::string> HncRpc::m_config_info_{};

/**
     * @brief rpc框架初始化, 获取配置参数
     */
void HncRpc::init() noexcept {

    // TODO : 从配置文件中读取所以配置参数

    m_config_info_["rpc_server_ip"] = constant::RPC_SEVER_IP;
    m_config_info_["rpc_server_port"] = constant::RPC_SEVER_PORT;

    // ......


}
}
