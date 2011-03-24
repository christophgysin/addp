#ifndef ADDP_DISCOVER_H
#define ADDP_DISCOVER_H

#include <list>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/deadline_timer.hpp>

#include "constants.h"
#include "types.h"
#include "packet.h"

namespace addp {

class discover
{
public:
    discover(const std::string& listen, uint16_t port,
            const mac_address& mac_address = MAC_ADDR_BROADCAST);

    void set_verbose(bool verbose);
    void set_mac_address(const mac_address& mac_address);
    void set_mcast_address(const std::string& mcast_address, uint16_t port = UDP_PORT);
    void set_timeout(ssize_t timeout_ms);
    void set_max_count(ssize_t max_count);

    bool run();
    void stop();

    const std::list<packet>& packets() const;

private:
    void handle_send_to(const boost::system::error_code& error, size_t bytes_sent);
    void handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd);

    void check_timeout();
    static void handle_receive(const boost::system::error_code& ec, size_t bytes_recvd,
        boost::system::error_code* out_ec, size_t* out_bytes_recvd);

    boost::asio::io_service _io_service;
    boost::asio::ip::udp::endpoint _listen;
    boost::asio::ip::udp::socket _socket;
    boost::asio::ip::udp::endpoint _mcast_address;
    boost::asio::ip::udp::endpoint _sender_address;
    boost::asio::deadline_timer _deadline;
    boost::array<uint8_t, MAX_UDP_MESSAGE_LEN> _data;

    mac_address _mac_address;
    ssize_t _count;
    ssize_t _max_count;
    ssize_t _timeout_ms;
    bool _verbose;

    std::list<packet> _packets;
};

} // namespace addp

#endif // ADDP_DISCOVER_H
