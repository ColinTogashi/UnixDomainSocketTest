#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <map>

#include "ConnectionHandler.hpp"

namespace boost_local = boost::asio::local;

class UnixDomainSocketServer {

public:
    UnixDomainSocketServer(boost::asio::io_service& io_service, const std::string& file);
    UnixDomainSocketServer(const UnixDomainSocketServer&);
    UnixDomainSocketServer& operator=(const UnixDomainSocketServer&);
    ~UnixDomainSocketServer();
    void HandleAccept(ConnectionHandler::ConnectionHandlerPtr ptr, const boost::system::error_code& error);
    void AddFunction(std::string function_name, ConnectionHandler::FunctionPtr ptr);

private:
    boost::asio::io_service& io_service_;
    boost_local::stream_protocol::acceptor acceptor_;
    const std::string& filename_;
    std::shared_ptr<std::map<std::string, ConnectionHandler::FunctionPtr>> available_functions_;

};