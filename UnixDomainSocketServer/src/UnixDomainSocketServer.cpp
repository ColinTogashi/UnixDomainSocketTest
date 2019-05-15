#include "UnixDomainSocketServer.hpp"
#include <iostream>

UnixDomainSocketServer::UnixDomainSocketServer(boost::asio::io_service& io_service, const std::string& file) : 
        io_service_(io_service),
        acceptor_(io_service, boost_local::stream_protocol::endpoint(file)),
        filename_(file) {
    
    available_functions_.reset(new std::map<std::string, ConnectionHandler::FunctionPtr>);

    ConnectionHandler::ConnectionHandlerPtr ptr(new ConnectionHandler(io_service_, available_functions_));
    acceptor_.async_accept(ptr->socket(),
            boost::bind(&UnixDomainSocketServer::HandleAccept, this, ptr,
                    boost::asio::placeholders::error));
}

UnixDomainSocketServer::~UnixDomainSocketServer() {
    ::unlink(filename_.c_str());
}

void UnixDomainSocketServer::HandleAccept(ConnectionHandler::ConnectionHandlerPtr ptr, const boost::system::error_code& error) {
    if (!error) {
        ptr->start();
    }

    ptr.reset(new ConnectionHandler(io_service_, available_functions_));
    acceptor_.async_accept(ptr->socket(),
            boost::bind(&UnixDomainSocketServer::HandleAccept, this, ptr,
                    boost::asio::placeholders::error));
}

void UnixDomainSocketServer::AddFunction(std::string function_name, ConnectionHandler::FunctionPtr ptr) {
    (*available_functions_)[function_name] = ptr;
    std::cout << "Added Function: " << function_name << "\n";
}