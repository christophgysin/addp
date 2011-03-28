#ifndef ADDP_ACTION_STATIC_NET_CONFIG_H
#define ADDP_ACTION_STATIC_NET_CONFIG_H

#include <addp/constants.h>
#include <addp/types.h>
#include <addp/action/action.h>

namespace addp {

class static_net_config : public action
{
public:
    static_net_config(const mac_address& mac_address,
        const ip_address& ip, const ip_address& subnet,
        const ip_address& gateway, const std::string& auth = DEFAULT_PASSWORD);

    void set_mac_address(const std::string& mac);
    void set_ip(const std::string& ip);
    void set_subnet(const std::string& subnet);
    void set_gateway(const std::string& gateway);
    void set_password(const std::string& password);

private:
    mac_address _mac_address;
    ip_address _ip;
    ip_address _subnet;
    ip_address _gateway;
    std::string _password;
};

} // namespace addp

#endif // ADDP_ACTION_STATIC_NET_CONFIG_H
