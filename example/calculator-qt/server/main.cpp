/*
Thrift的网络架构
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

1.Transport层提供了简单对网络层进行数据读写的抽象层，这使得transport层与系统其它部分（如：序列化/反序列化）中解耦。

2.Protocol抽象层定义了一种将内存中数据结构映射成可进行网络传输数据格式的机制。即Protocol层定义了datatype怎样使用底层的Transport对类型进行编解码。
  因此Protocol的实现要给出编码机制并负责对数据进行序列化。协议的编码格式有JSON、XML、纯文本、压缩的二进制等。

3.Processor封装了从输入数据流中读数据和向输出流中写数据的操作。读写数据流都可以用Protocol对象表示。与服务(service)相关的processor实现由thrift编译器产生。
  Processor本质上就是从网络中读取数据(使用输入protocaol)，将处理委托给handler(由用户实现)，最后将响应结果写到网络上(使用输出protocol)。

4.Server将以上所有特性集成在一起：
(1)创建一个transport对象。
(2)为transport对象创建输入输出protocol。
(3)基于输入输出protocol创建processor。
(4)等待连接请求并将之交给processor处理。
*/

/*
 *1.thrift支持的传输格式:
 *(1)TBinaryProtocol – 二进制格式.
 *(2)TCompactProtocol – 压缩格式
 *(3)TJSONProtocol – JSON格式
 *(4)TSimpleJSONProtocol –提供JSON只写协议， 生成的文件很容易通过脚本语言解析。
 *(5)TDebugProtocol – 使用易懂的可读的文本格式，以便于debug
*/

/*
 *2.支持的数据传输方式:
 *(1)TSocket - 阻塞式socker
 *(3)TFramedTransport – 以frame为单位进行传输，非阻塞式服务中使用。
 *(4)TFileTransport – 以文件形式进行传输。
 *(5)TMemoryTransport – 将内存用于I / O.java实现时内部实际使用了简单的ByteArrayOutput - Stream。
 *(6)TZlibTransport – 使用zlib进行压缩， 与其他传输方式联合使用。当前无java实现。
 */

/*
 *1.支持的服务模型
 *(1)TSimpleServer – 简单的单线程服务模型，常用于测试
 *(2)TThreadPoolServer – 多线程服务模型，使用标准的阻塞式IO。
 *(3)TNonblockingServer – 多线程服务模型，使用非阻塞式IO（需使用TFramedTransport数据传输方式）
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

