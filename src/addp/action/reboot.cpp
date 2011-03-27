#include "reboot.h"

#include <boost/lexical_cast.hpp>

#include <addp/packet/reboot.h>
#include <addp/packet/packet_io.h>
#include <addp/types_io.h>

namespace addp {

reboot::reboot(const mac_address& mac_address, const std::string& password) :
    action(reboot_request(mac_address, password)),
    _mac_address(mac_address),
    _password(password)
{
    if(mac_address != MAC_ADDR_BROADCAST)
        set_max_count(1);
}

void reboot::set_mac_address(const std::string& mac)
{
    mac_address _mac_address = boost::lexical_cast<mac_address>(mac);
    set_request(reboot_request(_mac_address, _password));

    if(_mac_address != MAC_ADDR_BROADCAST)
        set_max_count(1);
}

void reboot::set_password(const std::string& password)
{
    _password = password;
    set_request(reboot_request(_mac_address, _password));
}

} // namespace addp
