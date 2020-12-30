#include "CalculatorService.h"
#include <stdio.h>
#include <iostream>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#pragma comment(lib, "libthrift.lib")  //链接库文件

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

int main(int argc, char** argv)
{
	std::cout << "---threadpool client start---" << std::endl;

	int port = 9090;
	::std::shared_ptr<TSocket> socket(new TSocket("127.0.0.1", 9090));
	::std::shared_ptr<TBufferedTransport> transport(new TBufferedTransport(socket));
	::std::shared_ptr<TBinaryProtocol> protocol(new TBinaryProtocol(transport));

	CalculatorServiceClient client(protocol);
	try {
		transport->open();

		char opt = '+';
		int num1 = 0, num2 = 0;
		for (;;)
		{
			std::cout << "请输入两个操作数：";
			std::cin >> num1 >> num2;
			fflush(stdin);                      //吸收cin输入结束时，所敲的Enter键

			std::cout << "请输入运算符：";
			while (std::cin >> opt)
			{
				getchar();
				if (opt != '+' && opt != '-' && opt != '*' && opt != '/')
				{
					std::cout << "错误：输入的操作符不合法，请重新输入：";
					continue;
				}
				break;
			}

			if (opt == '+')
			{
				std::cout << num1 << " + " << num2 << " =" << client.add(num1, num2) << std::endl;
			}
			else if (opt == '-')
			{
				std::cout << num1 << " - " << num2 << " =" << client.sub(num1, num2) << std::endl;
			}
			else if (opt == '*')
			{
				std::cout << num1 << " * " << num2 << " =" << client.mul(num1, num2) << std::endl;
			}
			else if (opt == '/')
			{
				std::cout << num1 << " / " << num2 << " =" << client.div(num1, num2) << std::endl;
			}
			else
			{
				std::cout << "错误：输入的操作符户合法" << std::endl;
			}

			std::cout << "按任意键继续？（q退出程序）：";
			if (getchar() == 'q')
			{
				break;
			}
			fflush(stdin);      //清空输入缓存区
		}

		transport->close();
	}
	catch (TException& tx) {
		printf("ERROR:%s\n", tx.what());
	}

	getchar();
	return 0;
}