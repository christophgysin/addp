#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H

#include <stdint.h>

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/system/system_error.hpp>

class udp_socket
{
public:
    udp_socket(const std::string& ip, uint16_t port);

    size_t send(const std::vector<uint8_t>& packet);
    size_t receive(boost::asio::ip::udp::endpoint& sender, boost::asio::mutable_buffer buffer);

private:
    boost::asio::io_service io_service;
    boost::asio::ip::address address;
    boost::asio::ip::udp::socket socket;
    boost::asio::ip::udp::endpoint endpoint;
};

#endif // UDP_SOCKET_H
