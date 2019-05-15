#include <boost/asio.hpp>
#include <thread>
#include <iostream>

// #include "ConnectionHandler.hpp"
#include "UnixDomainSocketServer.hpp"

void hello_world() {
    std::cout << "Hello World!\n";
}

int main(int argc, char* argv[])
{
  uint counter=0;;
  try
  {
    ::unlink("/tmp/test"); // Remove previous binding.
    boost::asio::io_service io_service;
    UnixDomainSocketServer server = UnixDomainSocketServer(io_service, "/tmp/test");
    server.AddFunction("hello_world", &hello_world);
    
    std::thread run_thread([&]{ io_service.run(); });
    
    std::cout << "Crackalackin\n";
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }


  return 0;
}