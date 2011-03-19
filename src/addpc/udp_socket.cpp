#include "udp_socket.h"

udp_socket::udp_socket(const std::string& ip, uint16_t port) :
    io_service(),
    address(boost::asio::ip::address::from_string(ip)),
    socket(io_service),
    endpoint(address, port)
{
    socket.open(boost::asio::ip::udp::v4());
};

size_t udp_socket::send(const std::vector<uint8_t>& packet)
{
    return socket.send_to(boost::asio::buffer(packet), endpoint);
}

size_t udp_socket::receive(boost::asio::ip::udp::endpoint& sender, boost::asio::mutable_buffer buffer)
{
    return socket.receive_from(boost::asio::buffer(buffer), sender);
}
