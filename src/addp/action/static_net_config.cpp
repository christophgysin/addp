#include "static_net_config.h"

#include <iostream>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

#include <addp/packet/static_net_config.h>
#include <addp/packet/packet_io.h>
#include <addp/types_io.h>

namespace addp {

static_net_config::static_net_config(const mac_address& mac_address,
        const ip_address& ip, const ip_address& subnet,
        const ip_address& gateway, const std::string& password) :
    action(static_net_config_request(mac_address, ip, subnet, gateway, password)),
    _mac_address(mac_address),
    _ip(ip),
    _subnet(subnet),
    _gateway(gateway),
    _password(password)
{
    set_max_count(1);
}

void static_net_config::set_mac_address(const std::string& mac)
{
    _mac_address = boost::lexical_cast<mac_address>(mac);
    set_request(static_net_config_request(_mac_address, _ip, _subnet, _gateway, _password));
}

void static_net_config::set_ip(const std::string& ip)
{
    _ip = boost::lexical_cast<ip_address>(ip);
    set_request(static_net_config_request(_mac_address, _ip, _subnet, _gateway, _password));
}

void static_net_config::set_subnet(const std::string& subnet)
{
    _subnet = boost::lexical_cast<ip_address>(subnet);
    set_request(static_net_config_request(_mac_address, _ip, _subnet, _gateway, _password));
}

void static_net_config::set_gateway(const std::string& gateway)
{
    _gateway = boost::lexical_cast<ip_address>(gateway);
    set_request(static_net_config_request(_mac_address, _ip, _subnet, _gateway, _password));
}

void static_net_config::set_password(const std::string& password)
{
    _password = password;
    set_request(static_net_config_request(_mac_address, _ip, _subnet, _gateway, _password));
}

void static_net_config::print_brief(const boost::asio::ip::udp::endpoint& /*sender*/, const packet& response) const
{
    BOOST_FOREACH(const field& f, response.fields())
        if(f.type() == field::FT_RESULT_MSG)
        {
            std::cout << f.value<std::string>() << std::endl;
            break;
        }
}

} // namespace addp
