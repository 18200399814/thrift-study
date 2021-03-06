/**
 * Autogenerated by Thrift Compiler (0.13.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef ClientHelloService_H
#define ClientHelloService_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include <memory>
#include "communication_types.h"



#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class ClientHelloServiceIf {
 public:
  virtual ~ClientHelloServiceIf() {}
  virtual void sayHello(const std::string& msg) = 0;
};

class ClientHelloServiceIfFactory {
 public:
  typedef ClientHelloServiceIf Handler;

  virtual ~ClientHelloServiceIfFactory() {}

  virtual ClientHelloServiceIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(ClientHelloServiceIf* /* handler */) = 0;
};

class ClientHelloServiceIfSingletonFactory : virtual public ClientHelloServiceIfFactory {
 public:
  ClientHelloServiceIfSingletonFactory(const ::std::shared_ptr<ClientHelloServiceIf>& iface) : iface_(iface) {}
  virtual ~ClientHelloServiceIfSingletonFactory() {}

  virtual ClientHelloServiceIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(ClientHelloServiceIf* /* handler */) {}

 protected:
  ::std::shared_ptr<ClientHelloServiceIf> iface_;
};

class ClientHelloServiceNull : virtual public ClientHelloServiceIf {
 public:
  virtual ~ClientHelloServiceNull() {}
  void sayHello(const std::string& /* msg */) {
    return;
  }
};

typedef struct _ClientHelloService_sayHello_args__isset {
  _ClientHelloService_sayHello_args__isset() : msg(false) {}
  bool msg :1;
} _ClientHelloService_sayHello_args__isset;

class ClientHelloService_sayHello_args {
 public:

  ClientHelloService_sayHello_args(const ClientHelloService_sayHello_args&);
  ClientHelloService_sayHello_args& operator=(const ClientHelloService_sayHello_args&);
  ClientHelloService_sayHello_args() : msg() {
  }

  virtual ~ClientHelloService_sayHello_args() noexcept;
  std::string msg;

  _ClientHelloService_sayHello_args__isset __isset;

  void __set_msg(const std::string& val);

  bool operator == (const ClientHelloService_sayHello_args & rhs) const
  {
    if (!(msg == rhs.msg))
      return false;
    return true;
  }
  bool operator != (const ClientHelloService_sayHello_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ClientHelloService_sayHello_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class ClientHelloService_sayHello_pargs {
 public:


  virtual ~ClientHelloService_sayHello_pargs() noexcept;
  const std::string* msg;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

class ClientHelloServiceClient : virtual public ClientHelloServiceIf {
 public:
  ClientHelloServiceClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  ClientHelloServiceClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void sayHello(const std::string& msg);
  void send_sayHello(const std::string& msg);
 protected:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class ClientHelloServiceProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  ::std::shared_ptr<ClientHelloServiceIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (ClientHelloServiceProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_sayHello(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  ClientHelloServiceProcessor(::std::shared_ptr<ClientHelloServiceIf> iface) :
    iface_(iface) {
    processMap_["sayHello"] = &ClientHelloServiceProcessor::process_sayHello;
  }

  virtual ~ClientHelloServiceProcessor() {}
};

class ClientHelloServiceProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  ClientHelloServiceProcessorFactory(const ::std::shared_ptr< ClientHelloServiceIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::std::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::std::shared_ptr< ClientHelloServiceIfFactory > handlerFactory_;
};

class ClientHelloServiceMultiface : virtual public ClientHelloServiceIf {
 public:
  ClientHelloServiceMultiface(std::vector<std::shared_ptr<ClientHelloServiceIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~ClientHelloServiceMultiface() {}
 protected:
  std::vector<std::shared_ptr<ClientHelloServiceIf> > ifaces_;
  ClientHelloServiceMultiface() {}
  void add(::std::shared_ptr<ClientHelloServiceIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void sayHello(const std::string& msg) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->sayHello(msg);
    }
    ifaces_[i]->sayHello(msg);
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class ClientHelloServiceConcurrentClient : virtual public ClientHelloServiceIf {
 public:
  ClientHelloServiceConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot, std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync) : sync_(sync)
{
    setProtocol(prot);
  }
  ClientHelloServiceConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot, std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync) : sync_(sync)
{
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void sayHello(const std::string& msg);
  void send_sayHello(const std::string& msg);
 protected:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync_;
};

#ifdef _MSC_VER
  #pragma warning( pop )
#endif



#endif
