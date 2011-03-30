#include "reboot.h"

#include <iostream>
#include <boost/foreach.hpp>
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
    set_max_count(1);
}

void reboot::set_mac_address(const std::string& mac)
{
    _mac_address = boost::lexical_cast<mac_address>(mac);
    set_request(reboot_request(_mac_address, _password));
}

void reboot::set_password(const std::string& password)
{
    _password = password;
    set_request(reboot_request(_mac_address, _password));
}

void reboot::print_brief(const boost::asio::ip::udp::endpoint& /*sender*/, const packet& response) const
{
    BOOST_FOREACH(const field& f, response.fields())
        if(f.type() == field::FT_RESULT_MSG)
        {
            std::cout << f.value<std::string>() << std::endl;
            break;
        }
}

} // namespace addp
