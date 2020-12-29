#include <iostream>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include "HelloService.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

int main(int argc, char** argv)
{
    std::cout << "---client start---" << std::endl;

	int port = 9090;
    ::std::shared_ptr<TSocket> socket(new TSocket("127.0.0.1", port));
	::std::shared_ptr<TBufferedTransport> transport(new TBufferedTransport(socket));
	::std::shared_ptr<TBinaryProtocol> protocol(new TBinaryProtocol(transport));

	HelloServiceClient client(protocol);
	try {
		transport->open();

        std::cout<<"client call sayHello interface"<<std::endl;
		client.sayHello();
		transport->close();
	}
	catch (TException& tx) {
		printf("ERROR:%s\n", tx.what());
	}

	getchar();
	return 0;
}
