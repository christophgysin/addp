#ifndef ADDPD_SERVER_H
#define ADDPD_SERVER_H

#include <stdint.h>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/system/system_error.hpp>

class server
{
public:
    server(boost::asio::io_service& io_service, uint16_t port);
    void handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd);
    void handle_send_to(const boost::system::error_code& /*error*/, size_t /*bytes_sent*/);

private:
    boost::asio::io_service& _io_service;
    boost::asio::ip::udp::endpoint _endpoint;
    boost::asio::ip::udp::socket _socket;
    boost::asio::ip::udp::endpoint _sender;
    enum { max_length = 4096 };
    char _data[max_length];
};

#endif // ADDPD_SERVER_H
