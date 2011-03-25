#ifndef ADDP_REBOOT_H
#define ADDP_REBOOT_H

#include <list>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/deadline_timer.hpp>

#include <addp/constants.h>
#include <addp/types.h>
#include <addp/packet/packet.h>

namespace addp {

class reboot
{
public:
    reboot(const std::string& listen, uint16_t port,
            const mac_address& mac_address = MAC_ADDR_BROADCAST,
            const std::string& password = DEFAULT_PASSWORD);

    void set_verbose(bool verbose);
    void set_mac_address(const std::string& mac);
    void set_password(const std::string& password);
    void set_mcast_address(const std::string& mcast_address, uint16_t port = UDP_PORT);
    void set_timeout(ssize_t timeout_ms);
    void set_max_count(ssize_t max_count);

    bool run();
    void stop();

    const std::list<packet>& packets() const;

private:
    void check_timeout();
    void handle_send_to(const boost::system::error_code& error, size_t bytes_sent);
    void handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd);

    boost::asio::io_service _io_service;
    boost::asio::ip::udp::endpoint _listen;
    boost::asio::ip::udp::socket _socket;
    boost::asio::ip::udp::endpoint _mcast_address;
    boost::asio::ip::udp::endpoint _sender_address;
    boost::asio::deadline_timer _deadline;
    boost::array<uint8_t, MAX_UDP_MESSAGE_LEN> _data;

    mac_address _mac_address;
    std::string _password;
    ssize_t _count;
    ssize_t _max_count;
    ssize_t _timeout_ms;
    bool _verbose;

    std::list<packet> _packets;
};

} // namespace addp

#endif // ADDP_REBOOT_H
