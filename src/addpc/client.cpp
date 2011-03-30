#include "client.h"

#include <iostream>
#include <boost/lexical_cast.hpp>
#include <addp/addp.h>

#include "options.h"

namespace addpc {

client::client(const options& options) :
    _options(options)
{
}

bool client::run()
{
    if(_options.version())
    {
        std::cout << addp::VERSION << std::endl;
        return true;
    }

    if(_options.action() == "discover")
        return discover();
    if(_options.action() == "static")
        return static_net_config();
    if(_options.action() == "dhcp")
        return dhcp_net_config();
    if(_options.action() == "reboot")
        return reboot();

    // not reached
    return false;
}

bool client::run_action(addp::action& action)
{
    action.set_verbose(_options.verbose());
    action.set_dest_address(_options.multicast(), _options.port());
    action.set_timeout(_options.timeout());
    action.set_max_count(_options.max_count());

    return action.run();
}

bool client::discover()
{
    addp::discover action;
    action.set_listen_address(_options.listen(), _options.port());
    action.set_mac_address(_options.mac());

    return run_action(action);
}

bool client::static_net_config()
{
    addp::mac_address mac_address = boost::lexical_cast<addp::mac_address>(_options.mac());
    addp::ip_address ip = boost::lexical_cast<addp::ip_address>(_options.ip());
    addp::ip_address subnet = boost::lexical_cast<addp::ip_address>(_options.subnet());
    addp::ip_address gateway = boost::lexical_cast<addp::ip_address>(_options.gateway());
    addp::static_net_config action(mac_address, ip, subnet, gateway);
    action.set_password(_options.password());

    return run_action(action);
}

bool client::dhcp_net_config()
{
    addp::mac_address mac_address = boost::lexical_cast<addp::mac_address>(_options.mac());
    addp::dhcp_net_config action(mac_address, _options.dhcp());
    action.set_password(_options.password());

    return run_action(action);
}

bool client::reboot()
{
    addp::mac_address mac_address = boost::lexical_cast<addp::mac_address>(_options.mac());
    addp::reboot action(mac_address);
    action.set_password(_options.password());

    return run_action(action);
}

} // namespace addpc
