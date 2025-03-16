#include "hnc_rpc_server.h"
#include "hnc_rpc_d.h"
#include "hnc_rpc_header.pb.h"

#include <functional>

// 用于发布rpc服务的框架类

namespace hnc::rpc::details {

/**
 * @brief 将本地 实现了 Service 接口的 方法类 添加服务中， 后续便可以根据这个服务的方法来反序列化客户端发送的请求
 * @param service 重写了 Service 类的本地服务描述类指针
 */
void HncRpcServer::add_rpc_service(::google::protobuf::Service *service) noexcept {
    //
    HncRpcServiceInfo service_info;
    const google::protobuf::ServiceDescriptor* sd_ptr = service->GetDescriptor();

    // 存储该服务信息
    service_info.m_service_ = service;
    // 存储该服务下所有的 rpc 方法描述信息
    for (int i = 0; i < sd_ptr->method_count(); ++i) {
        // 获取第 i 个方法的描述
        const google::protobuf::MethodDescriptor* md_ptr = sd_ptr->method(i);
        // 将 该方法 名 与 方法描述指针 存入当前服务中
        service_info.m_method_list_.emplace(md_ptr->name(), md_ptr);
        std::cout << "rpc_server add [" << sd_ptr->name() << "]->[" << md_ptr->name() << "] successful!\n";
    }
    // 将该服务存入 当前服务器 所有发布的服务列表 中, 以便后续收到服务请求时 可以 找到对应的服务方法来反序列化
    m_service_list_.emplace(sd_ptr->name(), service_info); // 服务名  ->  服务信息
}


/**
 * @brief 启动 rpc 服务， 实际上 就是一个tcp服务器, 开启监听 listen， 并触发回调 解析数据即可
 * 开始监听新的客户端 发送来的事件
 * @param threads 服务器 开启 的 后台线程数量
 */
void HncRpcServer::run(const uint8_t threads) {
    // 获取配置信息中的 服务器 监听的 ip 地址 和 端口号
    const muduo::net::InetAddress address(HncRpc::Load("rpc_server_ip").c_str(), atoi(HncRpc::Load("rpc_server_port").c_str()));

    std::cout << "HncRpcServer init...\n";
    // 创建 TCP 服务器
    muduo::net::TcpServer rpc_server(&m_loop_, address, "HncRpcServer");

    // 设置 当前 TCP 服务器的 执行回调
    rpc_server.setConnectionCallback(std::bind(&HncRpcServer::OnConnection, this, std::placeholders::_1));
    rpc_server.setMessageCallback(std::bind(&HncRpcServer::OnMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    // 设置 tcp 服务器 的后台线程数 reactor 模型，多reactor， 默认开启四个
    rpc_server.setThreadNum(threads);

    std::cout << "HncRpcServer start service at " << address.toIpPort().c_str() << ", start listening...\n";

    // 启动服务器所有线程
    rpc_server.start();
    // 开启服务器事件循环, 此时服务器会阻塞在 epoll_wait 上， 等待新的客户端连接到来
    m_loop_.loop();
}

/**
 * @brief 在新连接到来时和连接关闭时 都会触发此函数
 */
void HncRpcServer::OnConnection(const muduo::net::TcpConnectionPtr &conn) const noexcept {
    // 若是连接关闭的事件， 则 主动关闭 服务器 -> 客户端 的 传输 , shutdown 并不是 四次挥手！！！
    if (conn->disconnected()) {
        conn->shutdown();
    }
}

/**
 * @brief 客户端发送数据时执行的回调
 * 解析 约定好的 rpc 头部字段数据，  根据 解析出的数据 -> 服务名, 方法名, 参数
 * 调用服务器 服务列表 中对应服务的对应方法 反序列化参数， 并执行对应 方法， 然后将 结果返回给客户端
 */
void HncRpcServer::OnMessage(const muduo::net::TcpConnectionPtr &conn,
    muduo::net::Buffer *buffer, muduo::Timestamp time) noexcept{

    // 先将所有数据 从 服务器缓冲区中拿出来存放到 栈上空间    ->   这里并没有反序列化任何数据！！
    const std::string receive_buffer = buffer->retrieveAllAsString();


    // 数据头部四个字节为 协议规定好的 rpc_header 的数据头长度
    uint32_t header_size = 0;
    receive_buffer.copy(reinterpret_cast<char*>(&header_size), 4, 0);

    // 开始反序列化 自定义 rpc_header 的数据   server_name, method_name, args_size
    hnc_rpc::HncRpcHeader rpc_header;
    if (!rpc_header.ParseFromString(std::string_view(receive_buffer.data() + 4, header_size))) {
        std::cout << "rpc_server parse rpc_header failed!\n";
        return;
    }

    // 此时客户端想要调用的 服务和方法名已经解析完成
    const std::string& service_name = rpc_header.server_name();
    const std::string& method_name = rpc_header.method_name();
    // 检查 服务 是否存在当前 rpc 服务器上
    const auto service_it = m_service_list_.find(service_name);
    if (service_it == m_service_list_.end()) {
        std::cout << "rpc_server -> service:" << service_name << " is not exist!" << std::endl;
        return;
    }
    // 检查 方法 是否存在对应的 服务 中
    const auto method_it = service_it->second.m_method_list_.find(rpc_header.method_name());
    if (method_it == service_it->second.m_method_list_.end()) {
        std::cout << "rpc_server -> method: " << service_name << "-" << method_name <<" is not exist!" << std::endl;
        return;
    }

    // 获取具体的服务对象描述和方法描述
    google::protobuf::Service *service = service_it->second.m_service_;
    const google::protobuf::MethodDescriptor *method = method_it->second;

    // 创建对应服务的对应方法的request, 将缓冲区中的剩余数据(对应的方法参数) 反序列化到 request中，
    google::protobuf::Message *request = service->GetRequestPrototype(method).New();
    if (!request->ParseFromString(std::string_view(receive_buffer.data() + 4 + header_size, rpc_header.args_size()))) {
        std::cout << "args parse failed!" << std::endl;
        return;
    }
    // 创建response， response 由 对应业务逻辑去填充
    google::protobuf::Message *response = service->GetResponsePrototype(method).New();

    // 测试输出
    std::cout << " header_size = " << header_size
                << "\n service_name = " << service_name
                << "\n method_name = " << method_name
                << "\n args_size = " << rpc_header.args_size()
                << "\n args_str = " << std::string_view(receive_buffer.data() + 4 + header_size, rpc_header.args_size()) << '\n';


    // 框架根据method描述调用对应service的虚函数， 即调用了service派生类
    // 然后在 protobuf 生成的 service_rpc 类内的虚函数里根据方法描述调用对应的方法
    // 此时，服务器需要一个 继承 protobuf 生成的service_rpc 类的 派生类， 并且重写 对应的方法，
    // 根据多态， 便可以在运行时 执行对应服务的对应方法
    service->CallMethod(method, nullptr, request, response,
        google::protobuf::NewCallback<HncRpcServer, const muduo::net::TcpConnectionPtr&, google::protobuf::Message*>(this, &HncRpcServer::SendRpcResponse, conn, response));

    // 由对应业务逻辑调用 回调 ， 该回调就是将 response 序列化后 再发送给对应的客户端， 一个rpc调用流程结束
}

// 业务逻辑处理完毕后调用的 done->run() 就是调用了这里的这个方法，去执行序列化rpc的响应和网络发送
/**
 * @brief 对应业务 执行完 request 后，调用 done->run(), 就是执行了这个回调
 * 该函数负责将业务逻辑封装好的 response 中的数据 序列化， 并通过 TCP 将数据返回给客户端，
 */
void HncRpcServer::SendRpcResponse(const muduo::net::TcpConnectionPtr &conn,
    google::protobuf::Message *response) {

    std::string response_str;
    // 将response的响应序列化成二进制数据存入string中
    if (response->SerializeToString(&response_str)) {
        // 将响应数据发回客户端， 客户端收到数据后 会向服务器发送 close(), 即由客户端主动发起第一次挥手
        conn->send(response_str);
    } else {
        std::cerr << "serial response_str error!" << std::endl;
    }
    // 服务器后续不再向客户端发送数据， 可以调用 shutdown
    conn->shutdown();
}
}
