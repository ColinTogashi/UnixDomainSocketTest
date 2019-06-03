#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

namespace boost_local = boost::asio::local;

class ConnectionHandler : public boost::enable_shared_from_this<ConnectionHandler> {

public:
    typedef boost::shared_ptr<ConnectionHandler> ConnectionHandlerPtr;
    typedef boost::function<int (void)> FunctionPtr;

    ConnectionHandler(boost::asio::io_service& io_service, std::shared_ptr<std::map<std::string, ConnectionHandler::FunctionPtr>> available_functions);
    boost_local::stream_protocol::socket& socket();
    void start();
    void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
    void handle_write(const boost::system::error_code& error);

private:
    boost_local::stream_protocol::socket socket_;
    char data_[1024];
    std::shared_ptr<std::map<std::string, ConnectionHandler::FunctionPtr>> available_functions_;
};