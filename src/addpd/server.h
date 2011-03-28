#ifndef ADDPD_SERVER_H
#define ADDPD_SERVER_H

#include <stdint.h>
#include <string>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/system/system_error.hpp>

class server
{
public:
    server(const std::string& listen_ip, uint16_t port);

    void run();
    void stop();

private:
    void handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd);

    boost::asio::io_service _io_service;
    boost::asio::ip::udp::endpoint _listen_address;
    boost::asio::ip::udp::socket _socket;
    size_t _thread_count;
    boost::asio::ip::udp::endpoint _sender_address;
    boost::array<uint8_t, 4096> _data;
};

#endif // ADDPD_SERVER_H
