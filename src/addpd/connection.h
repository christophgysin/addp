#ifndef ADDPD_CONNECTION_H
#define ADDPD_CONNECTION_H

#include <boost/asio/ip/udp.hpp>
#include <boost/system/system_error.hpp>
#include <addp/addp.h>

class connection
{
public:
    connection(boost::asio::ip::udp::socket& socket,
            const boost::asio::ip::udp::endpoint& endpoint,
            const addp::packet& request);

private:
    bool create_response(const addp::packet& request);
    void handle_request(const addp::packet& request);
    void handle_send_to(const boost::system::error_code& error, size_t bytes_sent);

    boost::asio::ip::udp::socket& _socket;
    const boost::asio::ip::udp::endpoint& _endpoint;
    boost::array<uint8_t, addp::MAX_UDP_MESSAGE_LEN> _data;
    size_t _data_bytes;
};

#endif // ADDPD_CONNECTION_H
