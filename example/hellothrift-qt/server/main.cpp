#include <iostream>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include "HelloService.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

class HelloServiceHandler : virtual public HelloServiceIf {
 public:
  HelloServiceHandler() {
    // Your initialization goes here
  }

  void sayHello() {
    // Your implementation goes here
    printf("call sayHello implement\n");
  }

};

int main(int argc, char **argv) 
{
	std::cout << "---server start---" << std::endl;

    int port = 9090;
	::std::shared_ptr<HelloServiceHandler> handler(new HelloServiceHandler());
    ::std::shared_ptr<TProcessor> processor(new HelloServiceProcessor(handler));
	::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
	::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
	::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
	
	TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
	server.serve();
	return 0;
}

