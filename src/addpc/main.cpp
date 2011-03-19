#include <iostream>
#include <addp.h>

#include <iomanip>
#include <boost/foreach.hpp>

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/system/system_error.hpp>

class addpc {
public:
    static std::string version()
    {
        return "0.1";
    }
};

class udp_socket
{
public:
    udp_socket(const std::string& ip, uint16_t port) :
        io_service(),
        address(boost::asio::ip::address::from_string(ip)),
        socket(io_service),
        endpoint(address, port)
    {
        socket.open(boost::asio::ip::udp::v4());
    };

    size_t send(const std::vector<uint8_t>& packet)
    {
        return socket.send_to(boost::asio::buffer(packet), endpoint);
    }

    size_t receive()
    {
        boost::asio::ip::udp::endpoint sender_endpoint;
        boost::array<char, 1024> recv_buf;
        size_t len = socket.receive_from(
                boost::asio::buffer(recv_buf), sender_endpoint);

        std::cout << sender_endpoint;
        std::cout.write(recv_buf.data(), len);

        return len;
    }

private:
    boost::asio::io_service io_service;
    boost::asio::ip::address address;
    boost::asio::ip::udp::socket socket;
    boost::asio::ip::udp::endpoint endpoint;
};

int main(int argc, char* argv[])
{
    std::cout << "libaddp version: " << addp::version() << std::endl;
    std::cout << "addpc version:   " << addpc::version() << std::endl;

    udp_socket socket(addp::IP_ADDRESS, addp::UDP_PORT);

    std::vector<uint8_t> packet = addp::discovery_request();
    socket.send(packet);

    std::cout << "sending discovery request: " << std::hex;
    BOOST_FOREACH(uint8_t byte, packet)
        std::cout << std::setfill('0') << std::setw(2) << int(byte);
    std::cout << std::endl;

    while(true)
    {
        socket.receive();
    }

    return 0;
}
