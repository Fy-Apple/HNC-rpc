#pragma once
#include "google/protobuf/service.h"
#include "google/protobuf/descriptor.h"

#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/InetAddress.h>
#include <string>
#include <unordered_map>


namespace hnc::rpc::details {
/**
 * @brief rpc 模块 提供的 发布 本地rpc 方法的接口类
 */
class HncRpcServer {
public:
    /**
     * @brief 将本地 实现了 Service 接口的 方法类 添加服务中， 后续便可以根据这个服务的方法来反序列化客户端发送的请求
     * @param service 重写了 Service 类的本地服务描述类指针
     */
    void add_rpc_service(::google::protobuf::Service *service) noexcept;

    /**
     * @brief 启动 rpc 服务， 实际上 就是一个tcp服务器, 开启监听 listen， 并触发回调 解析数据即可
     * 开始监听新的客户端 发送来的事件
     * @param threads 服务器 开启 的 后台线程数量
     */
    void run(uint8_t threads);

private:
    /**
     * @brief 新连接到来时执行的回调
     */
    void OnConnection(const muduo::net::TcpConnectionPtr &conn) const noexcept;

    /**
     * @brief 服务器接收到数据时执行的回调 ( 反序列化客户端发来的rpc数据， 调用本地服务方法后 在序列化返回给客户端执行结果)
     */
    void OnMessage(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer *buffer, muduo::Timestamp time) noexcept;

    /**
     * @brief 将执行结果发送回客户端后 执行的 callback
     */
    void SendRpcResponse(const muduo::net::TcpConnectionPtr&, google::protobuf::Message*);
private:
    // 网络库的 事件循环
    muduo::net::EventLoop m_loop_;

    // 服务信息
    struct HncRpcServiceInfo {
        // 指向具体服务的指针， 方便调用对应服务
        google::protobuf::Service *m_service_;
        // 根据方法名 找到 对应的方法描述， 提供给 protobuf 生成的 rpc 服务类调用
        std::unordered_map<std::string, const google::protobuf::MethodDescriptor*> m_method_list_;
    };
    // 存储所有服务对象和其所有发布的的方法
    std::unordered_map<std::string, HncRpcServiceInfo> m_service_list_;
};
}