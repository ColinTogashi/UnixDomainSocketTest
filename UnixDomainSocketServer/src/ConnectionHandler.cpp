#include "ConnectionHandler.hpp"
#include <iostream>

ConnectionHandler::ConnectionHandler(boost::asio::io_service& io_service, std::shared_ptr<std::map<std::string, ConnectionHandler::FunctionPtr>> available_functions) : 
        socket_(io_service),
        available_functions_(available_functions) {
}

boost_local::stream_protocol::socket& ConnectionHandler::socket() {
    return socket_;
}

void ConnectionHandler::start() {
    socket_.async_read_some(boost::asio::buffer(data_),
            boost::bind(&ConnectionHandler::handle_read,
                    shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

void ConnectionHandler::handle_read(const boost::system::error_code& error, size_t bytes_transferred) {
    int ret = 0;
    if (!error) {
        std::map<std::string, ConnectionHandler::FunctionPtr>::iterator it = (*available_functions_).find(data_);
        if(it != (*available_functions_).end()) {
            // element found
            ret = (*available_functions_)[data_]();
        } else {
            std::cout << "Function \"" << data_ << "\" not registered!\n";
        }

        memset(&data_[0], 0, sizeof(data_));
        data_[0] = ret;

        boost::asio::write(socket_, boost::asio::buffer(data_, sizeof(data_)));
        socket_.async_read_some(boost::asio::buffer(data_),
                boost::bind(&ConnectionHandler::handle_read,
                        shared_from_this(),
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
    }
}

// void ConnectionHandler::handle_write(const boost::system::error_code& error) {
//     if (!error) {
//         boost::asio::async_write(socket_,
//                 boost::asio::buffer(data_, bytes_transferred),
//                 boost::bind(&ConnectionHandler::handle_write,
//                         shared_from_this(),
//                         boost::asio::placeholders::error));
//     }
// }