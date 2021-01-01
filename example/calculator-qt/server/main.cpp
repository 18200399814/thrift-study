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
#include <cstdlib>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

class CalculatorServiceHandler : virtual public CalculatorServiceIf {
 public:
  CalculatorServiceHandler() {
    // Your initialization goes here
  }

  int32_t add(const int32_t num1, const int32_t num2) {
    printf("server add: %d + %d = %d\n",num1,num2,num1 + num2);
	return num1 + num2;
  }

  int32_t sub(const int32_t num1, const int32_t num2) {
    printf("server sub: %d - %d =%d\n",num1,num2,num1 - num2);
	return num1 - num2;
  }

  int32_t mul(const int32_t num1, const int32_t num2) {
    printf("server mul: %d * %d =%d\n",num1,num2,num1 * num2);
	return num1 * num2;
  }

  int32_t div(const int32_t num1, const int32_t num2) {
	if (num2 == 0)
	{
		printf("server div error: divisor can't be zero");
		exit(-1);
	}
	
	printf("server div: %d / %d = %d\n",num1,num2,num1 / num2);
	return num1 / num2;
  }
};

int main(int argc, char **argv)
{
	printf("---server start---\n");

	int port = 9090;
	::std::shared_ptr<CalculatorServiceHandler> handler(new CalculatorServiceHandler());
	::std::shared_ptr<TProcessor> processor(new CalculatorServiceProcessor(handler));
	::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
	::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
	::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
	
	TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
	server.serve();
	return 0;
}

