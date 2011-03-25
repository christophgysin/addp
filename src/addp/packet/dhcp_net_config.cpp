#include "dhcp_net_config.h"

namespace addp {

dhcp_net_config_request::dhcp_net_config_request(
        bool enable,
        const mac_address& mac,
        const std::string& auth
        ) :
    packet(packet::PT_DHCP_NET_CONFIG_REQUEST)
{
    add(enable ? field::BF_TRUE : field::BF_FALSE);
    add(mac);
    add(auth);
}

dhcp_net_config_response::dhcp_net_config_response() :
    packet(packet::PT_DHCP_NET_CONFIG_RESPONSE)
{
}

} // namespace addp
