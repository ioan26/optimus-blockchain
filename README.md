# optimus-blockchain

In this project I intent to create a blockchain system able to run on small systems such as uC or ARM. 
In this first approach I am building a general blockchain system. By now I want it to just work. 

Next Steps: Evaluate performance on Raspberry Pi 3 


Reference: [Blockchain for IoT Security and Privacy: The Case Study of a Smart Home](https://www.researchgate.net/publication/312218574_Blockchain_for_IoT_Security_and_Privacy_The_Case_Study_of_a_Smart_Home)


# Info on Protoc

This command can be included in the Makefile. See [gRPC Doc. C++](https://grpc.io/docs/languages/cpp/basics/#generating-client-and-server-code)

```
protoc -I . --grpc_out=<destination_path> --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` <file_name.proto>
```

```
protoc -I . --cpp_out=<destination_path> <file_name.proto>
```