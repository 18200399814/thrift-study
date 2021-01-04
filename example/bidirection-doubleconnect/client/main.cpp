// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "ServerByeService.h"
#include "ClientHelloService.h"
#include <thread>
#include <iostream>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace std;
using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

class ServerByeServiceHandler : virtual public ServerByeServiceIf {
public:
    ServerByeServiceHandler() {
        // Your initialization goes here
    }

    void sayBye(const std::string& msg) {
        printf("\nclient implement sayBye: %s\n",msg.c_str());
    }

};

static void sendToServer()
{
    int port = 9090;
    ::std::shared_ptr<TSocket> socket(new TSocket("localhost", port));
    ::std::shared_ptr<TBufferedTransport> transport(new TBufferedTransport(socket));
    ::std::shared_ptr<TBinaryProtocol> protocol(new TBinaryProtocol(transport));

    ClientHelloServiceClient client(protocol);
    try {
        transport->open();

        string msg;
        cout<<"Please input message to send to server: ";
        while(cin>>msg)
        {
            getchar();
            if(msg == "exit")
            {
                return ;
            }
            client.sayHello(msg);
            cout<<"to be continue?(input exit to stop): ";
        }

        transport->close();
    }
    catch (TException& tx) {
        printf("ERROR:%s\n", tx.what());
    }
}

static void handleRecvMsg()
{
    int port = 8080;
    ::std::shared_ptr<ServerByeServiceHandler> handler(new ServerByeServiceHandler());
    ::std::shared_ptr<TProcessor> processor(new ServerByeServiceProcessor(handler));
    ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
    server.serve();
}

int main(int argc, char **argv) {
    printf("---client start---\n");

    thread recvMsgThread(handleRecvMsg);

    sendToServer();
	recvMsgThread.join();

    return 0;
}

