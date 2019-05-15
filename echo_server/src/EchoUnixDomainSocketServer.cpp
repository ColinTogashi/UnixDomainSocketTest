#include "EchoUnixDomainSocketServer.hpp"

EchoUnixDomainSocketServer::EchoUnixDomainSocketServer(boost::asio::io_service& io_service, const std::string& file) : 
        io_service_(io_service),
        acceptor_(io_service, boost_local::stream_protocol::endpoint(file)) {
    
    EchoConnectionHandler::EchoConnectionHandlerPtr ptr(new EchoConnectionHandler(io_service_));
    acceptor_.async_accept(ptr->socket(),
            boost::bind(&EchoUnixDomainSocketServer::handle_accept, this, ptr,
                    boost::asio::placeholders::error));
}

void EchoUnixDomainSocketServer::handle_accept(EchoConnectionHandler::EchoConnectionHandlerPtr ptr, const boost::system::error_code& error) {
    if (!error) {
        ptr->start();
    }

    ptr.reset(new EchoConnectionHandler(io_service_));
    acceptor_.async_accept(ptr->socket(),
            boost::bind(&EchoUnixDomainSocketServer::handle_accept, this, ptr,
                    boost::asio::placeholders::error));
}