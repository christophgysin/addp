#include "udp_socket.h"

udp_socket::udp_socket(boost::asio::io_service& io_service, const std::string& ip, uint16_t port) :
    _io_service(io_service),
    _address(boost::asio::ip::address::from_string(ip)),
    _socket(io_service),
    _endpoint(_address, port)
{
    _socket.open(boost::asio::ip::udp::v4());
}

size_t udp_socket::send(const std::vector<uint8_t>& packet)
{
    return _socket.send_to(boost::asio::buffer(packet), _endpoint);
}

size_t udp_socket::receive(boost::asio::ip::udp::endpoint& sender, boost::asio::mutable_buffer buffer)
{
    return _socket.receive_from(boost::asio::buffer(buffer), sender);
}
