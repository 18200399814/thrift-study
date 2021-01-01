#include "HelloService.h"
#include "ByeService.h"
#include <iostream>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TMultiplexedProtocol.h>

#pragma comment(lib,"libthrift.lib")       //�ν�libthrift.lib���ļ�

using std::cout;
using std::endl;

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;

int main(int argc, char **argv) {
	cout << "---client start---" << endl;

	int port = 9090;
	::std::shared_ptr<TSocket> socket(new TSocket("192.168.0.102", port));
	::std::shared_ptr<TBufferedTransport> transport(new TBufferedTransport(socket));
	::std::shared_ptr<TBinaryProtocol> protocol(new TBinaryProtocol(transport));

	//ʹ��TMultiplexedProtocol���������ͻ�����������ĸ�����ӿ�
	std::shared_ptr<TMultiplexedProtocol> helloprotocol(new TMultiplexedProtocol(protocol, "HelloService"));   //����ķ������������̨TMultiplexedProcessorע�����ʱ�ķ�����������ͬ
	HelloServiceClient helloclient(helloprotocol);

	std::shared_ptr<TMultiplexedProtocol> byeprotocol(new TMultiplexedProtocol(protocol, "ByeService"));
	ByeServiceClient byeclient(byeprotocol);

	try{
		transport->open();

		cout << "helloclient call sayHello" << endl;
		helloclient.sayHello();                       //����HelloService����ӿ�

		cout << "byeclient call sayBye" << endl;      //����ByeService����ӿ�
		byeclient.sayBye();

		transport->close();
	}catch (TException& tx) {
		printf("ERROR:%s\n", tx.what());
	}

	return 0;
}

