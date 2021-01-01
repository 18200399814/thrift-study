#include "CalculatorService.h"
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
	::std::shared_ptr<TSocket> socket(new TSocket("192.168.136.1", 9090));
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