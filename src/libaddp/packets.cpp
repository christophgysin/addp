#include "packets.h"

namespace addp {

discovery_request::discovery_request(const mac_address mac_addr) :
    packet(addp::packet::PT_DISCOVERY_REQUEST)
{
    add_raw(reinterpret_cast<const uint8_t*>(&mac_addr), 6);
}

discovery_response::discovery_response() :
    packet(addp::packet::PT_DISCOVERY_RESPONSE)
{
}

static_net_config_request::static_net_config_request() :
    packet(addp::packet::PT_STATIC_NET_CONFIG_REQUEST)
{
}

static_net_config_response::static_net_config_response() :
    packet(addp::packet::PT_STATIC_NET_CONFIG_RESPONSE)
{
}

reboot_request::reboot_request() :
    packet(addp::packet::PT_REBOOT_REQUEST)
{
}

reboot_response::reboot_response() :
    packet(addp::packet::PT_REBOOT_RESPONSE)
{
}

dhcp_net_config_request::dhcp_net_config_request() :
    packet(addp::packet::PT_DHCP_NET_CONFIG_REQUEST)
{
}

dhcp_net_config_response::dhcp_net_config_response() :
    packet(addp::packet::PT_DHCP_NET_CONFIG_RESPONSE)
{
}

} // namespace addp
