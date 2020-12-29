#include "CalculatorService.h"
#include <iostream>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

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

	CalculatorServiceClient client(protocol);
	try {
		transport->open();
		std::cout << "1 + 2 =" << client.add(1, 2) << std::endl;
		std::cout << "8 - 2 =" << client.sub(8, 2) << std::endl;
		std::cout << "4 * 5 =" << client.mul(4, 5) << std::endl;
		std::cout << "18 / 3 =" << client.div(18, 3) << std::endl;
		transport->close();
	}
	catch (TException& tx) {
		printf("ERROR:%s\n", tx.what());
	}

	getchar();
	return 0;
}
