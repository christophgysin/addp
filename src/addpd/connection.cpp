#include "connection.h"

#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>

connection::connection(boost::asio::ip::udp::socket& socket,
        const boost::asio::ip::udp::endpoint& endpoint,
        const addp::packet& request) :
    _socket(socket),
    _endpoint(endpoint)
{
    handle_request(request);
}

void connection::handle_request(const addp::packet& /*request*/)
{
    // TODO: create response

    _socket.async_send_to(
        boost::asio::buffer(_data), _endpoint,
        boost::bind(&connection::handle_send_to, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void connection::handle_send_to(const boost::system::error_code& error, size_t /*bytes_sent*/)
{
    if(error)
        std::cerr << "error while sending response: " <<
            error.message() << "(" << error.value() << ")" << std::endl;

    delete this;
}
