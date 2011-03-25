#include "static_net_config.h"

namespace addp {

static_net_config_request::static_net_config_request(
        const ip_address& ip,
        const ip_address& subnet,
        const ip_address& gateway,
        const mac_address& mac,
        const std::string& auth
        ) :
    packet(packet::PT_STATIC_NET_CONFIG_REQUEST)
{
    add(ip);
    add(subnet);
    add(gateway);
    add(mac);
    add(auth);
}

static_net_config_response::static_net_config_response() :
    packet(packet::PT_STATIC_NET_CONFIG_RESPONSE)
{
}

} // namespace addp
