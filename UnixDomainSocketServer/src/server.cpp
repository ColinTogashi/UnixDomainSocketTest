#include <boost/asio.hpp>
#include <thread>
#include <iostream>

// #include "ConnectionHandler.hpp"
#include "UnixDomainSocketServer.hpp"

int hello_world() {
    std::cout << "Hello World!\n";
    return 1;
}

int main(int argc, char* argv[])
{
  uint counter=0;;
  try
  {
    ::unlink("/tmp/test"); // Remove previous binding.
    boost::asio::io_service io_service;
    std::unique_ptr<UnixDomainSocketServer> server;
    server.reset(new UnixDomainSocketServer(io_service, "/tmp/test"));
    server->AddFunction("hello_world", &hello_world);
    
    io_service.run();
    
    std::cout << "Crackalackin\n";
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }


  return 0;
}