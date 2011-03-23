#include "discover.h"

#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>

#include <packets.h>
#include <packet_io.h>

namespace addpc {

discover::discover(boost::asio::ip::udp::socket& socket, const addp::mac_address& mac_address) :
    _socket(socket),
    _mcast_address(
            boost::asio::ip::address::from_string(addp::MCAST_IP_ADDRESS),
            addp::UDP_PORT),
    _mac_address(mac_address),
    _timeout_ms(0),
    _max_count(0),
    _count(0),
    _verbose(false)
{
}

void discover::set_mac_address(const addp::mac_address& mac_address)
{
    _mac_address = mac_address;
}

void discover::set_mcast_address(const std::string& mcast_address, uint16_t port)
{
    _mcast_address = boost::asio::ip::udp::endpoint(
            boost::asio::ip::address::from_string(mcast_address),
            port);
}

void discover::set_timeout(ssize_t timeout_ms)
{
    _timeout_ms = timeout_ms;
}

void discover::set_max_count(ssize_t max_count)
{
    _max_count = max_count;
}

void discover::set_verbose(bool verbose)
{
    _verbose = verbose;
}

bool discover::run()
{
    addp::discovery_request request;

    boost::asio::ip::udp::endpoint endpoint(
        boost::asio::ip::address::from_string(addp::MCAST_IP_ADDRESS),
        addp::UDP_PORT);

    if(_verbose)
        std::cout << "sending to: " << _mcast_address << " packet: " << request
            << std::endl << std::endl;

    _socket.async_send_to(
        boost::asio::buffer(request.raw()),
        _mcast_address,
        boost::bind(&discover::handle_send_to, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));

    return true;
}

const std::list<addp::packet>& discover::packets() const
{
    return _packets;
}

void discover::handle_send_to(const boost::system::error_code& /*error*/, size_t /*bytes_sent*/)
{
    _socket.async_receive_from(
        boost::asio::buffer(_data, max_length), _sender_address,
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

        std::cout << _sender_address << " " << response << std::endl;

        _packets.push_back(response);

        if(++_count == _max_count)
            return;
    }
    else
        std::cerr << "error: " <<  error.value() << "(" << error.message() << ")"
            << " received: " << bytes_recvd << std::endl;

    _socket.async_receive_from(
        boost::asio::buffer(_data, max_length), _sender_address,
        boost::bind(&discover::handle_receive_from, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

} // namespace addpc
