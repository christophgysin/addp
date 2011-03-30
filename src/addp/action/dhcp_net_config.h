#ifndef ADDP_ACTION_DHCP_NET_CONFIG_H
#define ADDP_ACTION_DHCP_NET_CONFIG_H

#include <addp/constants.h>
#include <addp/types.h>
#include <addp/action/action.h>

namespace addp {

class dhcp_net_config : public action
{
public:
    dhcp_net_config(const mac_address& mac_address, bool enable,
            const std::string& password = DEFAULT_PASSWORD);

    void set_mac_address(const std::string& mac);
    void set_enable(bool enable);
    void set_password(const std::string& password);

protected:
    void print_brief(const boost::asio::ip::udp::endpoint& sender, const packet& response) const;

private:
    mac_address _mac_address;
    bool _enable;
    std::string _password;
};

} // namespace addp

#endif // ADDP_ACTION_DHCP_NET_CONFIG_H
