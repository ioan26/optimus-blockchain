cmake_minimum_required(VERSION 3.10)

# set project name
project(OptimusChain VERSION 0.1)

# creates the variable EXEC and sets it to hello
set(EXEC Blockchain)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_PREFIX_PATH "/opt/grpc" "/opt/protobuf")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(OpenSSL REQUIRED)
find_package(Protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)

# I../includes
include_directories(includes)

# puts all .cpp files inside src to the SOURCES variable
file(GLOB SOURCES src/*)

# compiles the files defined by SOURCES to generante the executable defined by EXEC
add_executable(${EXEC} ${SOURCES})

target_link_libraries(${EXEC} 
    OpenSSL::SSL
    protobuf::libprotobuf
    gRPC::grpc++)
