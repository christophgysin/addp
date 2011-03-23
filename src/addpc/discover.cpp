#include "discover.h"

#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>

namespace addpc {

discover::discover(boost::asio::ip::udp::socket& socket, const addp::mac_address& mac_address) :
    _socket(socket),
    _mac_address(mac_address),
    _mcast_address(addp::MCAST_IP_ADDRESS),
    _timeout_ms(0),
    _max_count(0)
{
}

void discover::set_mac_address(const addp::mac_address& mac_address)
{
    _mac_address = mac_address;
}

void discover::set_mcast_address(const std::string& mcast_address)
{
    _mcast_address = mcast_address;
}

void discover::set_timeout(ssize_t timeout_ms)
{
    _timeout_ms = timeout_ms;
}

void discover::set_max_count(ssize_t max_count)
{
    _max_count = max_count;
}

bool discover::run()
{
    addp::discovery_request request;

    /*
    if(_options.verbose())
        std::cout << "sending to: " << _endpoint << " packet: " << request
            << std::endl << std::endl;
    */

    _socket.async_send_to(
        boost::asio::buffer(request.raw()),
        boost::asio::ip::udp::endpoint(
            boost::asio::ip::address::from_string(addp::MCAST_IP_ADDRESS),
            addp::UDP_PORT),
        boost::bind(&discover::handle_send_to, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));

    /*
    _socket.async_send(
        boost::asio::buffer(request.raw()),
        boost::bind(&discover::handle_send_to, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    */

    //_io_service.run();

    return true;
}



void discover::handle_send_to(const boost::system::error_code& /*error*/, size_t /*bytes_sent*/)
{
    _socket.async_receive_from(
        boost::asio::buffer(_data, max_length), _sender,
        boost::bind(&discover::handle_receive_from, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void discover::handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd)
{
    if(!error && bytes_recvd > 0)
    {
        addp::packet response(_data.data(), bytes_recvd);

        if(!response.parse_fields())
            std::cerr << "failed to parse fields!" << std::endl;

        std::cout << _sender << " " << response << std::endl;

        _packets.push_back(response);
    }
    else
        std::cerr << "error: " <<  error.value() << "(" << error.message() << ")"
            << " received: " << bytes_recvd << std::endl;

    _socket.async_receive_from(
        boost::asio::buffer(_data, max_length), _sender,
        boost::bind(&discover::handle_receive_from, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

} // namespace addpc
