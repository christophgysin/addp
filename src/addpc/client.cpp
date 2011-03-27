#include "client.h"

#include <iostream>
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
        std::cout << ADDP_VERSION << std::endl;
        return true;
    }

    if(_options.action() == "discover")
        return discover();
    if(_options.action() == "static")
        return static_net_config();
    if(_options.action() == "reboot")
        return reboot();
    if(_options.action() == "dhcp")
        return dhcp_net_config();

    std::cerr << "Unknown action: " << _options.action() << std::endl;
    std::cout << std::endl << _options.usage();
    return false;
}

bool client::run_action(addp::action& action)
{
    action.set_verbose(_options.verbose() > 0);
    action.set_dest_address(_options.multicast(), _options.port());
    action.set_timeout(_options.timeout());
    action.set_max_count(_options.max_count());

    return action.run();
}

bool client::discover()
{
    addp::discover action;
    action.set_mac_address(_options.mac());

    return run_action(action);
}

bool client::static_net_config()
{
    return false;
}

bool client::reboot()
{
    addp::reboot action;
    action.set_mac_address(_options.mac());
    action.set_password(_options.password());

    return run_action(action);
}

bool client::dhcp_net_config()
{
    return false;
}

} // namespace addpc
