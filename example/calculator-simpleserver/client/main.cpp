/*
Thrift������ܹ�
+-------------------------------------------+
| Server                                    |
|(single-threaded,event-driven etc)         |
+-------------------------------------------+
| Processor                                 |
|(compiler generated)                       |
+-------------------------------------------+
| Protocol                                  |
|(JSON, compact etc)                        |
+-------------------------------------------+
| Transport                                 |
|(raw TCP, HTTP etc)                        |
+-------------------------------------------+

1.Transport���ṩ�˼򵥶������������ݶ�д�ĳ���㣬��ʹ��transport����ϵͳ�������֣��磺���л�/�����л����н��

2.Protocol����㶨����һ�ֽ��ڴ������ݽṹӳ��ɿɽ������紫�����ݸ�ʽ�Ļ��ơ���Protocol�㶨����datatype����ʹ�õײ��Transport�����ͽ��б���롣
  ���Protocol��ʵ��Ҫ����������Ʋ���������ݽ������л���Э��ı����ʽ��JSON��XML�����ı���ѹ���Ķ����Ƶȡ�

3.Processor��װ�˴������������ж����ݺ����������д���ݵĲ�������д��������������Protocol�����ʾ�������(service)��ص�processorʵ����thrift������������
  Processor�����Ͼ��Ǵ������ж�ȡ����(ʹ������protocaol)��������ί�и�handler(���û�ʵ��)�������Ӧ���д��������(ʹ�����protocol)��

4.Server�������������Լ�����һ��
(1)����һ��transport����
(2)Ϊtransport���󴴽��������protocol��
(3)�����������protocol����processor��
(4)�ȴ��������󲢽�֮����processor����
*/

/*
 *1.thrift֧�ֵĴ����ʽ:
 *(1)TBinaryProtocol �C �����Ƹ�ʽ.
 *(2)TCompactProtocol �C ѹ����ʽ
 *(3)TJSONProtocol �C JSON��ʽ
 *(4)TSimpleJSONProtocol �C�ṩJSONֻдЭ�飬 ���ɵ��ļ�������ͨ���ű����Խ�����
 *(5)TDebugProtocol �C ʹ���׶��Ŀɶ����ı���ʽ���Ա���debug
*/

/*
 *2.֧�ֵ����ݴ��䷽ʽ:
 *(1)TSocket - ����ʽsocker
 *(3)TFramedTransport �C ��frameΪ��λ���д��䣬������ʽ������ʹ�á�
 *(4)TFileTransport �C ���ļ���ʽ���д��䡣
 *(5)TMemoryTransport �C ���ڴ�����I / O.javaʵ��ʱ�ڲ�ʵ��ʹ���˼򵥵�ByteArrayOutput - Stream��
 *(6)TZlibTransport �C ʹ��zlib����ѹ���� ���������䷽ʽ����ʹ�á���ǰ��javaʵ�֡�
 */

 /*
  *1.֧�ֵķ���ģ��
  *(1)TSimpleServer �C �򵥵ĵ��̷߳���ģ�ͣ������ڲ���
  *(2)TThreadPoolServer �C ���̷߳���ģ�ͣ�ʹ�ñ�׼������ʽIO��
  *(3)TNonblockingServer �C ���̷߳���ģ�ͣ�ʹ�÷�����ʽIO����ʹ��TFramedTransport���ݴ��䷽ʽ��
  */

#include "CalculatorService.h"
#include <stdio.h>
#include <iostream>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>

#pragma comment(lib, "libthrift.lib")  //���ӿ��ļ�

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;

int main(int argc, char** argv)
{
	std::cout << "---simple client start---" << std::endl;

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
			std::cout << "������������������";
			std::cin >> num1 >> num2;
			getchar();                      //����cin�������ʱ�����õ�Enter��

			std::cout << "�������������";
			while (std::cin >> opt)
			{
				getchar();
				if (opt != '+' && opt != '-' && opt != '*' && opt != '/')
				{
					std::cout << "��������Ĳ��������Ϸ������������룺";
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
				std::cout << "��������Ĳ��������Ϸ�" << std::endl;
			}

			std::cout << "���������������q�˳����򣩣�";
			if (getchar() == 'q')
			{
				break;
			}
			getchar();
		}

		transport->close();
	}
	catch (TException& tx) {
		printf("ERROR:%s\n", tx.what());
	}

	getchar();
	return 0;
}