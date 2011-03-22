#ifndef ADDPC_CLIENT_H
#define ADDPC_CLIENT_H

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
    const options& _options;
    udp_socket _socket;
};

} // namespace addpc

#endif // ADDPC_CLIENT_H
