#include "server.h"

#include <boost/asio/buffer.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/bind.hpp>

server::server(boost::asio::io_service& io_service, uint16_t port) :
    _io_service(io_service),
    _endpoint(boost::asio::ip::udp::v4(), port),
    _socket(io_service, _endpoint)
{
    _socket.async_receive_from(
        boost::asio::buffer(_data, max_length), _sender,
        boost::bind(&server::handle_receive_from, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void server::handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd)
{
    if (!error && bytes_recvd > 0)
    {
        _socket.async_send_to(
            boost::asio::buffer(_data, bytes_recvd), _sender,
            boost::bind(&server::handle_send_to, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }
    else
    {
        _socket.async_receive_from(
            boost::asio::buffer(_data, max_length), _sender,
            boost::bind(&server::handle_receive_from, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }
}

void server::handle_send_to(const boost::system::error_code& /*error*/, size_t /*bytes_sent*/)
{
    _socket.async_receive_from(
        boost::asio::buffer(_data, max_length), _sender,
        boost::bind(&server::handle_receive_from, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}
