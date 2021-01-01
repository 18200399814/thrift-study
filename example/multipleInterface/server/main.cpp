#include "HelloService.h"
#include "ByeService.h"
#include <iostream>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/processor/TMultiplexedProcessor.h>

#pragma comment(lib, "libthrift.lib")  //链接库文件

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
		printf("hello thrift\n");
	}
};

class ByeServiceHandler : virtual public ByeServiceIf {
public:
	ByeServiceHandler() {
		// Your initialization goes here
	}

	void sayBye() {
		// Your implementation goes here
		printf("bye thrift\n");
	}
};

int main(int argc, char **argv) {
	std::cout << "---server start---" << std::endl;

	int port = 9090;
	::std::shared_ptr<HelloServiceHandler> hellohandler(new HelloServiceHandler());
	::std::shared_ptr<TProcessor> helloprocessor(new HelloServiceProcessor(hellohandler));

	::std::shared_ptr<ByeServiceHandler> byehandler(new ByeServiceHandler());
	::std::shared_ptr<TProcessor> byeprocessor(new ByeServiceProcessor(byehandler));

	//通过TMultiplexedProcessor类注册多个接口的服务
	std::shared_ptr<TMultiplexedProcessor> multiprocessor(new TMultiplexedProcessor);
	multiprocessor->registerProcessor("HelloService", helloprocessor);
	multiprocessor->registerProcessor("ByeService", byeprocessor);

	::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket("192.168.0.102", port));
	::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
	::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

	TSimpleServer server(multiprocessor, serverTransport, transportFactory, protocolFactory);
	server.serve();
	return 0;
}

