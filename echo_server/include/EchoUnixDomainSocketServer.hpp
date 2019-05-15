#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "EchoConnectionHandler.hpp"

namespace boost_local = boost::asio::local;

class EchoUnixDomainSocketServer {

public:
    EchoUnixDomainSocketServer(boost::asio::io_service& io_service, const std::string& file);
    void handle_accept(EchoConnectionHandler::EchoConnectionHandlerPtr ptr, const boost::system::error_code& error);

private:
    boost::asio::io_service& io_service_;
    boost_local::stream_protocol::acceptor acceptor_;
};