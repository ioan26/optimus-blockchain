#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include "transaction.grpc.pb.h"


using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using transaction::Message;
using transaction::ACK;
using transaction::Transaction;

class TransactionServiceImpl final : public Transaction::Service {
 public:

    Status GetFeature(ServerContext* context, const Message* message, ACK* ack) override {
      std::string sender_address("node_1");
      std::string receiver_address("node_2");

      ack->set_sender(sender_address);
      ack->set_reciever(receiver_address);
      return Status::OK;
    }
};



void RunServer(void) {
  std::string server_address("0.0.0.0:50051");
  TransactionServiceImpl service;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}