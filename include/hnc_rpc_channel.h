#pragma once
#include "google/protobuf/service.h"

namespace hnc::rpc::details {

/**
 * @brief 继承至 protobuf 为我们生成的 channel 类， 用于根据方法描述 调用对应的rpc服务方法
 */
class HncRpcChannel final : public google::protobuf::RpcChannel { // 必须继承自protobuf生成的channel类
public:
    /**
     * @brief 通过stub代理对象调用方法，， 根据自定义格式序列化request ，
     *          根据描述的方法， 序列化后网络套接字发送给远程服务器
     * @param method 方法描述
     * @param controller
     * @param request rpc方法调用 请求， 序列化
     * @param response rpc 方法调用 的响应， 未序列化
     * @param done 最后的执行回调，可以不写
     */
    void CallMethod(const google::protobuf::MethodDescriptor* method,
                    google::protobuf::RpcController* controller, const google::protobuf::Message* request,
                    google::protobuf::Message* response, google::protobuf::Closure* done) override;
private:

};
}