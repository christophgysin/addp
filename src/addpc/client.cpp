#include "client.h"

#include <iostream>

#include <packet.h>
#include <packets.h>

#include "options.h"

namespace addpc {

client::client(const options& options) :
    _options(options),
    _socket(options.host(), options.port())
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
    addp::discovery_request request;

    if(_options.verbose())
        std::cout << "sending packet: " << request << std::endl;

    _socket.send(request.raw());

    while(true)
    {
        boost::asio::ip::udp::endpoint sender;
        boost::array<uint8_t, 1024> buffer;
        size_t len = _socket.receive(sender, boost::asio::buffer(buffer));

        addp::packet response(buffer.data(), len);

        if(!response.parse_fields())
            std::cerr << "failed to parse fields!" << std::endl;

        std::cout << sender << " " << response << std::endl;
    }

    return false;
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
