#include "packets.h"

namespace addp {

discovery_request::discovery_request(
        const mac_address mac
        ) :
    packet(packet::PT_DISCOVERY_REQUEST)
{
    add_raw(mac.data, mac.len);
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
    add_raw(ip.data, ip.len);
    add_raw(subnet.data, subnet.len);
    add_raw(gateway.data, gateway.len);
    add_raw(mac.data, mac.len);
    add_raw(reinterpret_cast<const uint8_t*>(auth.data()), auth.size());
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
    add_raw(mac.data, mac.len);
    add_raw(reinterpret_cast<const uint8_t*>(auth.data()), auth.size());
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
    uint8_t value = field::bool_flag(enable ? field::BF_TRUE : field::BF_FALSE);
    add_raw(&value, sizeof(value));
    add_raw(mac.data, mac.len);
    add_raw(reinterpret_cast<const uint8_t*>(auth.data()), auth.size());
}

dhcp_net_config_response::dhcp_net_config_response() :
    packet(packet::PT_DHCP_NET_CONFIG_RESPONSE)
{
}

} // namespace addp
