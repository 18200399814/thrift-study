#include "Hello.h"
#include <iostream>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>

#pragma comment(lib, "libthrift.lib")  //Á´½Ó¿âÎÄ¼þ

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;

int main(int argc, char** argv)
{
	std::cout << "---client start---" << std::endl;

	int port = 9090;
	::std::shared_ptr<TSocket> socket(new TSocket("192.168.0.102", 9090));
	::std::shared_ptr<TBufferedTransport> transport(new TBufferedTransport(socket));
	::std::shared_ptr<TBinaryProtocol> protocol(new TBinaryProtocol(transport));

	HelloClient client(protocol);
	try {
		transport->open();

		std::cout << "client call sayHello" << std::endl;
		client.sayHello();

		transport->close();
	}
	catch (TException& tx) {
		printf("ERROR:%s\n", tx.what());
	}

	getchar();
	return 0;
}