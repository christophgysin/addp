#include "client.h"

#include <iostream>

#include <packet.h>
#include <packets.h>

#include "options.h"
#include "discover.h"

namespace addpc {

client::client(const options& options) :
    _options(options)
{
}

bool client::run()
{
    if(_options.action() == "discover")
        return discover();
    if(_options.action() == "static")
        return static_net_config();
    if(_options.action() == "reboot")
        return reboot();
    if(_options.action() == "dhcp")
        return dhcp_net_config();

    std::cerr << "Unknown option! (" << _options.action() << ")" << std::endl;
    return false;
}


bool client::discover()
{
    addpc::discover d(_options.listen(), _options.port());
    //d.set_mac_address(...);
    d.set_mcast_address(_options.multicast(), _options.port());
    if(_options.max_count())
        d.set_max_count(_options.max_count());
    if(_options.timeout())
        d.set_timeout(_options.timeout());
    d.set_verbose(_options.verbose() > 0);
    d.run();
    return true;
}

bool client::static_net_config()
{
    return false;
}

bool client::reboot()
{
    return false;
}

bool client::dhcp_net_config()
{
    return false;
}

} // namespace addpc
