#include "discover.h"

#include <boost/lexical_cast.hpp>

#include <addp/packet/discovery.h>
#include <addp/types_io.h>

namespace addp {

discover::discover(const mac_address& mac_address) :
    action(discovery_request(mac_address))
{
    if(mac_address != MAC_ADDR_BROADCAST)
        set_max_count(1);
}

void discover::set_mac_address(const std::string& mac)
{
    mac_address mac_addr = boost::lexical_cast<mac_address>(mac);
    set_request(discovery_request(mac_addr));

    if(mac_addr != MAC_ADDR_BROADCAST)
        set_max_count(1);
}

} // namespace addp
