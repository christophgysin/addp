#include <cctype>
#include <iostream>
#include <iomanip>
#include <boost/foreach.hpp>

#include <addp.h>
#include <udp_socket.h>

#include "addp_options.h"

class addpc {
public:
    static std::string version()
    {
        return "0.1";
    }
};

int main(int argc, char* argv[])
{
    addp_options options(argc, argv);

    if(options.version())
    {
        std::cout << "libaddp version: " << addp::version() << std::endl;
        std::cout << "addpc version:   " << addpc::version() << std::endl;
        return 0;
    }

    udp_socket socket(options.host(), options.port());

    addp::discovery_request request;

    if(options.verbose())
        std::cout << "sending packet: " << request << std::endl;

    socket.send(request.raw());

    while(true)
    {
        boost::asio::ip::udp::endpoint sender;
        boost::array<uint8_t, 1024> buffer;
        size_t len = socket.receive(sender, boost::asio::buffer(buffer));

        addp::packet response(buffer.data(), len);

        //if(options.verbose())
        std::cout << sender << " " << response << std::endl;
        /*
        BOOST_FOREACH(uint8_t b, buffer)
            std::cout << " " << std::hex << std::setfill('0') << std::setw(2) << int(b);
        std::cout << std::endl;
        */

    }
    return 0;
}
