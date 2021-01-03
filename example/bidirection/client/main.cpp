//thrift支持的是open->client--rpc-->server->close的短连接模式。在实际应用中，却经常会有客户端建立连接后，等待服务端数据的长连接模式，也可以称为双向连接。

/*thrift双向链接的实现方法：
 *1.双向连接的service必须为oneway，否则会因为recv函数抛出remote close异常。
 *2.客户端重用建立client的protocol，开线程使用processor.Process(protocol,protocol)监听服务端callback的消息。
 *3.服务端使用ProcessorFactory，使用TConnectionInfo中的transport作为向客户端发送消息的client的transport
 */

#include "HelloBidiService.h"
#include <iostream>
#include <thread>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

using namespace std;
using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;

class HelloBidiServiceImpl : virtual public HelloBidiServiceIf {       //HelloBidiServiceImpl是客户端的handle类，等同于服务器端的HelloBidiServiceHandler类。
public:                                                                //只是服务器与客户端中调用sayHello方法需要做的事情不相同，所以需要实现两个不同的类。
    HelloBidiServiceImpl() {
        // Your initialization goes here
    }

    void sayHello(const std::string& msg) {
        printf("recv server-client: %s\n",msg.c_str());
    }
};

static void disposeReceiveMsg(shared_ptr<TTransport> transport)
{
    shared_ptr<HelloBidiServiceImpl> handler(new HelloBidiServiceImpl);
    shared_ptr<TProcessor> processor(new HelloBidiServiceProcessor(handler));

    try {
        shared_ptr<TProtocol> inProtocol(new TBinaryProtocol(transport));
        shared_ptr<TProtocol> outProtocol(new TBinaryProtocol(transport));
        while(processor->process(inProtocol, outProtocol,nullptr))           //客户端等待处理服务器回显的消息，如果获取到服务器的发送回来的消息，就交给HelloBidiServiceImpl类去处理
        {
            printf("wait next message\n");
        }
    } catch (TException& e) {
        printf("connect close\n");
        printf("error: %s\n",e.what());
    }
}

int main(int argc, char **argv) {
    printf("---client start---\n");

    int port = 9090;
    shared_ptr<TSocket> socket(new TSocket("localhost", port));
    shared_ptr<TBufferedTransport> transport(new TBufferedTransport(socket));
    shared_ptr<TBinaryProtocol> protocol(new TBinaryProtocol(transport));

    HelloBidiServiceClient client(protocol);      //创建客户端
    try {
        transport->open();

        thread receiveThread(disposeReceiveMsg,socket);    //将客户端监听服务器消息的任务，交给一个独立的线程去做

        cout<<"input message: ";
        string str;
        while (cin >> str)
        {
            getchar();
            if(str.compare("exit") == 0)
            {
                cout<<"exit client"<<endl;
                receiveThread.detach();
                break;
            }
            client.sayHello(str);                   //客户端向服务器发送消息
            Sleep(200);                             //延时500毫秒，等待接收服务器返回的消息，以避免打印顺序变乱
            cout<<"to be continue(exit stop)?: ";
        }

        transport->close();
    }
    catch (TException& tx) {
        printf("ERROR:%s\n", tx.what());
    }

    return 0;
}

