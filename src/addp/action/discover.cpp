#include "discover.h"

#include <iostream>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
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

void discover::print_brief(const boost::asio::ip::udp::endpoint& sender, const packet& response) const
{
    std::string mac_addr;
    std::string name;
    std::string device;
    std::string firmware;

    BOOST_FOREACH(const field& f, response.fields())
    {
        switch(f.type())
        {
            case field::FT_MAC_ADDR:
                mac_addr = f.value_str();
                break;
            case field::FT_NAME:
                name = f.value_str();
                break;
            case field::FT_DEVICE:
                device = f.value_str();
                break;
            case field::FT_FIRMWARE:
                firmware = f.value_str();
                break;
            default:
                break;
        }
    }

    std::cout << str(
        boost::format("%-15.15s  %-15.15s  %-17.17s  %-15.15s  %s")
            % sender.address()
            % name
            % mac_addr
            % device
            % firmware
        ) << std::endl;
}

} // namespace addp
