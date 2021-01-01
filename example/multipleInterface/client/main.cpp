#include "HelloService.h"
#include "ByeService.h"
#include <iostream>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TMultiplexedProtocol.h>

#pragma comment(lib,"libthrift.lib")       //衔接libthrift.lib库文件

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

	//使用TMultiplexedProtocol类来帮助客户端区别调用哪个服务接口
	std::shared_ptr<TMultiplexedProtocol> helloprotocol(new TMultiplexedProtocol(protocol, "HelloService"));   //这里的服务器名称与后台TMultiplexedProcessor注册服务时的服务器名称相同
	HelloServiceClient helloclient(helloprotocol);

	std::shared_ptr<TMultiplexedProtocol> byeprotocol(new TMultiplexedProtocol(protocol, "ByeService"));
	ByeServiceClient byeclient(byeprotocol);

	try{
		transport->open();

		cout << "helloclient call sayHello" << endl;
		helloclient.sayHello();                       //调用HelloService服务接口

		cout << "byeclient call sayBye" << endl;      //调用ByeService服务接口
		byeclient.sayBye();

		transport->close();
	}catch (TException& tx) {
		printf("ERROR:%s\n", tx.what());
	}

	return 0;
}

