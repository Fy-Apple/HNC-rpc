#include "hnc_rpc_channel.h"
#include "hnc_rpc_header.pb.h"
#include "hnc_rpc_d.h"

#include <google/protobuf/descriptor.h>
#include <string>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>



namespace hnc::rpc::details {
/**
 * @brief 通过stub代理对象调用方法，， 根据自定义格式序列化request ，
 *          根据描述的方法， 序列化后网络套接字发送给远程服务器
 * @param method 方法描述
 * @param controller
 * @param request rpc方法调用 请求， 序列化 header_size + service_name + method_name + args_size + args
 * @param response rpc 方法调用 的响应， 未序列化
 * @param done 最后的执行回调，可以不写
 */
void HncRpcChannel::CallMethod(
    const google::protobuf::MethodDescriptor *method,
    google::protobuf::RpcController *controller,
    const google::protobuf::Message *request,
    google::protobuf::Message *response,
    google::protobuf::Closure *done) {

    // 序列化需要发送的参数 至 request
    std::string args_str;
    if (!request->SerializeToString(&args_str)) {
        std::cout << "hnc_rpc serialize request error!";
        return;
    }


    // 序列化服务名+方法名+参数长度
    hnc_rpc::HncRpcHeader rpc_header;
    rpc_header.set_server_name(method->service()->name());
    rpc_header.set_method_name(method->name());
    rpc_header.set_args_size(args_str.size());
    std::string rpc_header_str;
    // service_name + method_name + args_size
    if (!rpc_header.SerializeToString(&rpc_header_str)) {
        std::cout << "hnc_rpc serialize rpc_header error!";
        return;
    }

    // 发送数据的头部 四字节 为 hnc_rpc_header 的长度 自定义帧边界
    uint32_t rpc_header_size = rpc_header_str.size();
    std::string send_str(reinterpret_cast<char*>(&rpc_header_size), sizeof(rpc_header_size));

    // 合并所有发送数据  头部长度 + 头部(服务名+方法名+参数长度) + 方法参数
    send_str.append(std::move(rpc_header_str));
    send_str.append(std::move(args_str));

    std::cout << "hnc_rpc send_str=" << send_str << std::endl;

    // 创建tcp套接字将该序列化后的数据发送出去
    // TODO : 添加 rpc 的 TCP 连接池， 目前使用 短链接
    const int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    // 使用RAII 自定义在 函数离开时的 close 连接 逻辑
    using SocketPtr = std::unique_ptr<int, decltype([](const int* const fd) {
        if (*fd != -1) {
            close(*fd);
        }
        delete fd;
    })>;
    SocketPtr clientPtr(new int(client_fd));

    // 获取rpc服务器的 ip 和 端口
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    // 转化为网络字节序
    inet_pton(AF_INET, HncRpc::Load("rpc_server_ip").c_str(), &server_addr.sin_addr);
    server_addr.sin_port = htons(stoi(HncRpc::Load("rpc_server_port")));

    // tcp 连接到 rpc 服务器
    if (-1 == connect(client_fd, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr))) {
        std::cout << "rpc_client connect to rpc_server error! errno = " << errno << std::endl;
        exit(EXIT_FAILURE);
        // 这里会 RAII 自定关闭 client_fd
    }

    // 将数据发送到rpc服务器
    size_t total_sent = 0;
    while (total_sent < send_str.size()) {
        // 确保将所有数据都发送到服务器
        const int sent_size = send(client_fd, send_str.c_str() + total_sent, send_str.size() - total_sent, 0);
        if (sent_size <= 0) {
            std::cerr << "rpc_client send request to rpc_server error! errno = " << errno << std::endl;
            return;
            // 这里会 RAII 自定关闭 client_fd
        }
        total_sent += sent_size;
    }

    // 同步 接收 rpc 服务器返回的 response 响应数据  (阻塞等待)
    char buffer[1024]{};
    uint32_t receive_size{};
    if (-1 == (receive_size = recv(client_fd, buffer, 1024, 0))) {
        std::cerr << "rpc_client receive error! errno = " << errno << std::endl;
        return;
    }

    // 此处已经接收到 rpc 服务器返回的序列化数据了

    // 反序列化响应数据到 response 中
    // const std::string response_str(buffer, 0, receive_size); string  \0 时直接结束了构造，因此不适用 string 反序列化
    if (!response->ParseFromArray(buffer, receive_size)) {
        std::cerr << "rpc_client parse error! response_str = " << buffer << std::endl;
    }

    // 自动关闭客户端套接字
}
}

