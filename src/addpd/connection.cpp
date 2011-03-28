#include "connection.h"

#include <iostream>
#include <boost/bind.hpp>
#include <boost/format.hpp>
#include <boost/asio/placeholders.hpp>

connection::connection(boost::asio::ip::udp::socket& socket,
        const boost::asio::ip::udp::endpoint& endpoint,
        const addp::packet& request) :
    _socket(socket),
    _endpoint(endpoint),
    _data_bytes(0)
{
    handle_request(request);
}

bool connection::create_response(const addp::packet& request)
{
    switch(request.type())
    {
        default:
            std::cerr << "got unknown request (" << int(request.type()) << ")" <<
                ", ignoring" << std::endl;
            return false;
    }
}

void connection::handle_request(const addp::packet& request)
{
    if(!create_response(request))
        return;

    _socket.async_send_to(
        boost::asio::buffer(_data, _data_bytes), _endpoint,
        boost::bind(&connection::handle_send_to, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void connection::handle_send_to(const boost::system::error_code& error, size_t bytes_sent)
{
    if(error || bytes_sent != _data_bytes)
        std::cerr << str(
                boost::format("error while sending response: %s (%d) sent %d of %d bytes")
                    % error.message()
                    % error.value()
                    % bytes_sent
                    % _data_bytes
                ) << std::endl;

    delete this;
}
