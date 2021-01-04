/*实现Thrift双向链接的两种方法：
 *1.双连接（服务端与客户端都开ThriftServer）：
 *  让服务端与客户端互相访问时，可以给服务端与客户端，两者都开一个ThriftServer，也就是两者互为服务端与客户端。
 *      客户端：   <------------>     服务端：
 *  ThriftClient  <------------->  ThriftService
 *  ThriftService <------------->  ThriftClient
 *
 *2.单连接（利用ProcessorFactory中TConnectionInfo的transport定时向客户端发送消息，让thrift保持长连接不立即关闭）：
 *  thrift是rpc结构的通信框架，rpc结构默认是【客户端请求 -> 服务端回应 -> 连接断开】的这种短连接形式，因此rpc默认是没有服务端回调功能，自然也没有长连接。
 *  如果要保持连接不关闭且被动接收到对方的数据，需要指定双方连接的service必须为oneway，且服务端需要利用客户端发送数据到服务端时，连接成功产生的transport，
 *  定时向客户端发送信息。同时客户端需也创建Processor处理服务端发送过来的消息，并实时检测transport的状态，以便出现与服务端连接断开的情况出现。
 *
 *3.利用单连接实现thrift双向通信的具体步骤：
 *（1）双向连接的service必须为oneway，否则会因为recv函数抛出remote close异常。
 *（2）客户端重用建立client的protocol，开线程使用TProcessor::rocess(protocol,protocol)监听服务端回调发送过来的消息。
 *（3）服务端使用ProcessorFactory创建Processor，通过getProcessor函数中transport作为向客户端发送消息的client的transport而创建一个Processor。
 */

#include "HelloBidiService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#define WORKER_COUNT 3

using namespace std;
using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

static shared_ptr<TTransport> g_currentTransport = nullptr;       //保存客户端发送数据到服务端时，连接成功产生的transport

class HelloBidiServiceHandler : virtual public HelloBidiServiceIf {
public:
    HelloBidiServiceHandler() {

    }

    void sayHello(const std::string& msg) {
        printf("recv client->server: %s\n",msg.c_str());

        sayToClient(msg);
    }

    void sayToClient(const std::string& msg)
    {
        printf("send server-client: %s\n",msg.c_str());

        shared_ptr<TBinaryProtocol> protocol(new TBinaryProtocol(g_currentTransport));
        HelloBidiServiceClient client(protocol);              //服务器中创建RPC客户端，已实现服务器向客户端发送消息
        client.sayHello(msg);
    }
};

//thrift自动生成的代码已经实现了HelloBidiServiceProcessorFactory类，所以为了避免重名使用UserHelloBidiServiceProcessorFactory
class UserHelloBidiServiceProcessorFactory : public TProcessorFactory
{
public:
    shared_ptr<TProcessor> getProcessor(const TConnectionInfo& connInfo) override
    {
        printf("receive connecting signal\n");
        g_currentTransport = connInfo.transport;

        shared_ptr<HelloBidiServiceHandler> handler(new HelloBidiServiceHandler());
        shared_ptr<TProcessor> processor(new HelloBidiServiceProcessor(handler));
        return processor;
    }
};

int main(int argc, char **argv) {
    printf("---server start---\n");

    int port = 9090;
    shared_ptr<TProcessorFactory> processorFactory(new UserHelloBidiServiceProcessorFactory);
    shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    TSimpleServer server(processorFactory, serverTransport, transportFactory, protocolFactory);
    server.serve();
    return 0;
}

