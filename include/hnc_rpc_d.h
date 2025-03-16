#pragma once

#include <string>
#include <unordered_map>


namespace hnc::rpc::details {
/**
 * @brief 提供rpc框架的基本初始化
 */
class HncRpc {
public:
    /**
     * @brief rpc框架初始化
     */
    static void init() noexcept;
    // 获取全局唯一单例
    static HncRpc& GetInstance() noexcept{
        return app;
    }
    /**
     * @brief 获取对应参数值
     * @param key 参数对应的键， 例如 server_ip
     */
    static std::string Load(const std::string &key) noexcept{
        if (!m_config_info_.contains(key)) {
            return {};
        }
        return m_config_info_[key];
    }

private:
    // 删除拷贝和赋值
    HncRpc(){}
    HncRpc(const HncRpc&) = delete;
    HncRpc(HncRpc&&) = delete;
    HncRpc& operator=(const HncRpc&) = delete;
    HncRpc& operator=(HncRpc&&) = delete;

private:
    static HncRpc app;;
    // 存储框架的基本参数 ip，端口，服务名等
    static std::unordered_map<std::string, std::string> m_config_info_;
};
}