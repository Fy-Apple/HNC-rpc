#include <iostream>
#include <string>
#include "rpc_test.pb.h"
#include "hnc_rpc.h"

using namespace hnc::rpc;

/**
 * @brief 服务器要发布一个 rpc 服务， 需要继承 protobuf 生成 的rpc 服务类
 */
class MyTestService final : public rpc_test::UserServiceRpc{
public:
    /**
     * @brief 实际上真正的 业务逻辑
     */
    bool Login(const std::string &name, const std::string &pwd) {
        std::cout << "doing local service : Login!" << std::endl;
        std::cout << "name: " << name.c_str() << ", pwd: " << pwd.c_str() << std::endl;

        std::srand(std::time(nullptr));  // 设置随机种子
        const int random_bit = std::rand() % 2;  // 生成 0 或 1
        return random_bit;
    }

    /**
     * @brief 重写基类的 rpc 服务方法， 该方法去调用 具体的业务逻辑即可
     */
    void Login(::google::protobuf::RpcController* controller,
                        const ::rpc_test::LoginRequest* request,
                        ::rpc_test::LoginResponse* response,
                        ::google::protobuf::Closure* done) override {
        // 框架会收到服务请求，并将请求parse成参数放入request中，
        const std::string name = request->name();
        const std::string pwd = request->pwd();

        // 调用本地函数 执行真正的业务逻辑
        const bool login_result = Login(name, pwd);

        // 将响应写入框架给的 response 中
        rpc_test::ResultCode *result = response->mutable_result();

        // 设置 用户自己的 response 响应数据
        result->set_errcode(login_result ? 0 : 1);
        result->set_errmsg("pwd is error!");
        response->set_success(login_result);

        // 执行回调操作  ->  将 response 序列化成字节 并通过网络返回给 客户端
        done->Run();
    }
};


int main(int argc, char** argv) {

    // 初始化rpc框架( 读取配置文件参数 )
    rpc_init();

    // 从rpc框架提供的全局接口中 获取 一个 rpc 服务器的智能指针
    const auto rpc_server = get_rpc_server();

    // 将本地 rpc 服务 添加到服务器中， 使得服务器 可以调用 该服务的方法进行响应
    rpc_server->add_rpc_service(new MyTestService());

    // 启动 rpc 服务器， 事实上 底层启动了 TCP 服务器开始监听客户端的到来， 需要提供 后台线程数量
    rpc_server->run(4);

    // 服务器接收到数据后也会处理并将结果反馈给客户端

    return 0;
}