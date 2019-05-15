#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

namespace boost_local = boost::asio::local;

class EchoConnectionHandler : public boost::enable_shared_from_this<EchoConnectionHandler> {

public:
    typedef boost::shared_ptr<EchoConnectionHandler> EchoConnectionHandlerPtr;
    EchoConnectionHandler(boost::asio::io_service& io_service);
    boost_local::stream_protocol::socket& socket();
    void start();
    void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
    void handle_write(const boost::system::error_code& error);

private:
    boost_local::stream_protocol::socket socket_;
    char data_[1024];
};