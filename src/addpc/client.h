#ifndef ADDPC_CLIENT_H
#define ADDPC_CLIENT_H

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>

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
};

} // namespace addpc

#endif // ADDPC_CLIENT_H
