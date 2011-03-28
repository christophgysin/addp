#include "server.h"

#include <iostream>
#include <boost/asio/buffer.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/bind.hpp>

#include "connection.h"

server::server(boost::asio::io_service& io_service, uint16_t port) :
    _io_service(io_service),
    _endpoint(boost::asio::ip::udp::v4(), port),
    _socket(io_service, _endpoint)
{
    _socket.async_receive_from(
        boost::asio::buffer(_data), _sender,
        boost::bind(&server::handle_receive_from, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void server::handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd)
{
    if (!error && bytes_recvd > 0)
        new connection(_socket, _sender, addp::packet(_data.data(), bytes_recvd));

    _socket.async_receive_from(
        boost::asio::buffer(_data), _sender,
        boost::bind(&server::handle_receive_from, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

