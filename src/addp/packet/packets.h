#ifndef ADDP_PACKETS_H
#define ADDP_PACKETS_H

#include "types.h"
#include "packet.h"

namespace addp {

class discovery_request : public packet
{
public:
    discovery_request(const mac_address mac = MAC_ADDR_BROADCAST);
};

class discovery_response : public packet
{
public:
    discovery_response();
};

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

class reboot_request : public packet
{
public:
    reboot_request(
        const mac_address& mac = MAC_ADDR_BROADCAST,
        const std::string& auth = DEFAULT_PASSWORD
        );
};

class reboot_response : public packet
{
public:
    reboot_response();
};

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
