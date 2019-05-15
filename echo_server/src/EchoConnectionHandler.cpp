#include "EchoConnectionHandler.hpp"
#include <iostream>

EchoConnectionHandler::EchoConnectionHandler(boost::asio::io_service& io_service) : 
        socket_(io_service) {
}

boost_local::stream_protocol::socket& EchoConnectionHandler::socket() {
    return socket_;
}

void EchoConnectionHandler::start() {
    socket_.async_read_some(boost::asio::buffer(data_),
            boost::bind(&EchoConnectionHandler::handle_read,
                    shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

void EchoConnectionHandler::handle_read(const boost::system::error_code& error, size_t bytes_transferred) {
    if (!error) {
        std::cout << "Received : " << data_ << "\n";
        boost::asio::async_write(socket_,
                boost::asio::buffer(data_, bytes_transferred),
                boost::bind(&EchoConnectionHandler::handle_write,
                        shared_from_this(),
                        boost::asio::placeholders::error));
    }
}

void EchoConnectionHandler::handle_write(const boost::system::error_code& error) {
    if (!error) {
        socket_.async_read_some(boost::asio::buffer(data_),
                boost::bind(&EchoConnectionHandler::handle_read,
                        shared_from_this(),
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
    }
}