#include <iostream>
#include <addp.h>

#include "addp_options.h"
#include "udp_socket.h"

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

    std::vector<uint8_t> packet = addp::discovery_request();
    socket.send(packet);

    while(true)
    {
        boost::asio::ip::udp::endpoint sender;
        boost::array<char, 1024> buffer;
        size_t len = socket.receive(sender, boost::asio::buffer(buffer));

        std::cout << sender << " ";
        std::cout.write(buffer.data(), len);
        std::cout << std::endl;
    }

    return 0;
}
