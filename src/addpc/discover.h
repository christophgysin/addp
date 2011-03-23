#ifndef ADDPC_DISCOVER_H
#define ADDPC_DISCOVER_H

#include <list>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>

#include <addp.h>
#include <types.h>
#include <packet.h>
#include <packets.h>

namespace addpc {

class discover
{
public:
    discover(boost::asio::ip::udp::socket& socket,
            const addp::mac_address& mac_address = addp::MAC_ADDR_BROADCAST);

    void set_mac_address(const addp::mac_address& mac_address);
    void set_mcast_address(const std::string& mcast_address);
    void set_timeout(ssize_t timeout_ms);
    void set_max_count(ssize_t max_count);

    bool run();

private:
    void handle_send_to(const boost::system::error_code& error, size_t bytes_sent);
    void handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd);

    boost::asio::ip::udp::socket& _socket;
    boost::asio::ip::udp::endpoint _sender;
    enum { max_length = 4096 };
    boost::array<uint8_t, max_length> _data;

    addp::mac_address _mac_address;
    std::string _mcast_address;
    ssize_t _timeout_ms;
    ssize_t _max_count;

    std::list<addp::packet> _packets;
};

} // namespace addpc

#endif // ADDPC_DISCOVER_H
