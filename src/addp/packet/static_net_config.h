#ifndef ADDP_PACKETS_H
#define ADDP_PACKETS_H

#include <addp/types.h>
#include <addp/packet/packet.h>

namespace addp {

class static_net_config_request : public packet
{
public:
    static_net_config_request(
        const ip_address& ip,
        const ip_address& subnet,
        const ip_address& gateway,
        const mac_address& mac = MAC_ADDR_BROADCAST,
        const std::string& auth = DEFAULT_PASSWORD
        );
};

class static_net_config_response : public packet
{
public:
    static_net_config_response();
};

} // namespace addp

#endif // ADDP_PACKETS_H
