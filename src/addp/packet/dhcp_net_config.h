#ifndef ADDP_PACKETS_H
#define ADDP_PACKETS_H

#include <addp/types.h>
#include <addp/packet/packet.h>

namespace addp {

class dhcp_net_config_request : public packet
{
public:
    dhcp_net_config_request(
        bool enable,
        const mac_address& mac = MAC_ADDR_BROADCAST,
        const std::string& auth = DEFAULT_PASSWORD
        );
};

class dhcp_net_config_response : public packet
{
public:
    dhcp_net_config_response();
};

} // namespace addp

#endif // ADDP_PACKETS_H