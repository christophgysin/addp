#ifndef ADDPC_CLIENT_H
#define ADDPC_CLIENT_H

#include <boost/asio/io_service.hpp>

#include <addp.h>
#include <udp_socket.h>

#include "options.h"

namespace addpc {

class client
{
public:
    client(const options& options);

    bool run();

    // actions
    bool discover();
    bool static_net_config();
    bool reboot();
    bool dhcp_net_config();

private:
    void handle_send_to(const boost::system::error_code& error, size_t bytes_sent);
    void handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd);

    const options& _options;
    boost::asio::io_service _io_service;
    boost::asio::ip::address _address;
    boost::asio::ip::udp::endpoint _endpoint;
    boost::asio::ip::udp::endpoint _sender;
    boost::asio::ip::udp::socket _socket;
    enum { max_length = 4096 };
    boost::array<uint8_t, max_length> _data;
};

} // namespace addpc

#endif // ADDPC_CLIENT_H
