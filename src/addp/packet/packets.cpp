#include "packets.h"

namespace addp {

discovery_request::discovery_request(
        const mac_address mac
        ) :
    packet(packet::PT_DISCOVERY_REQUEST)
{
    add(mac);
}

discovery_response::discovery_response() :
    packet(packet::PT_DISCOVERY_RESPONSE)
{
}

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

reboot_request::reboot_request(
        const mac_address& mac,
        const std::string& auth
        ) :
    packet(packet::PT_REBOOT_REQUEST)
{
    add(mac);
    add(auth);
}

reboot_response::reboot_response() :
    packet(packet::PT_REBOOT_RESPONSE)
{
}

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
