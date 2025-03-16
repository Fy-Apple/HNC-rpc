#include <iostream>
#include <rpc_test.pb.h>

#include "hnc_rpc.h"

using namespace hnc::rpc;


int main(int argc, char **argv) {
    hnc::core::logger::change_log_file_name("rpc/caller_log");
    rpc_init();


    // 客户端调用服务器的 rpc 方法需要创建 代理对象， stub, 并将 框架重写的 rpc_channel类传递给 自定义服务器
    rpc_test::UserServiceRpc_Stub stub(get_rpc_channel());

    // 创建一个新的请求
    rpc_test::LoginRequest request;
    // 封装请求参数
    request.set_name("apple");
    request.set_pwd("201209");

    // 创建空的response， 后续服务器会将结果返回， 反序列化后 到该response里
    rpc_test::LoginResponse response;

    // 同步 远程过程调用 服务器的 rpc 方法， 阻塞等待对方发回响应
    stub.Login(nullptr, &request, &response, nullptr);

    /**
     * 事实上代理对象 调用的 Login 就是调用了 protobuf 生成的 channel 类的 callmethod 方法
     * 而该方法是一个虚函数， 它会调用 刚刚创建代理对象时 传递进去的 rpc_channel 这个类重写的 callmethod方法
     * 这个类由 自己写生成， 通过hcn_rpc 获取该对象指针即可，
     * 而这个虚函数就是 本 hnc_rpc 框架的重点 ，  负责将数据序列化， 再将数据 发送给服务器
     */



    // 处理响应数据
    if (0 == response.result().errcode()) {
        std:: cout << "rpc_client login response successful :" << response.success() << std::endl;
    } else {
        std::cout << "rpc_client login response error : " << response.result().errmsg() << std::endl;
    }

    return 0;
}
