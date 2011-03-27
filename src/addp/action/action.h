#ifndef ADDP_action_H
#define ADDP_action_H

#include <list>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/deadline_timer.hpp>

#include <addp/constants.h>
#include <addp/types.h>
#include <addp/packet/packet.h>

namespace addp {

class action
{
public:
    action(const packet& request);

    void set_listen_address(const std::string& listen_ip, uint16_t port = UDP_PORT);
    void set_dest_address(const std::string& dest_ip, uint16_t port = UDP_PORT);
    void set_request(const packet& request);
    void set_timeout(ssize_t timeout_ms);
    void set_max_count(ssize_t max_count);
    void set_verbose(bool verbose);

    bool run();
    void stop();

private:
    void check_timeout();
    void handle_send_to(const boost::system::error_code& error, size_t bytes_sent);
    void handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd);

    boost::asio::ip::udp::endpoint _listen_address;
    boost::asio::ip::udp::endpoint _dest_address;
    boost::asio::ip::udp::endpoint _sender_address;
    boost::asio::io_service _io_service;
    boost::asio::ip::udp::socket _socket;
    boost::asio::deadline_timer _deadline;
    boost::array<uint8_t, MAX_UDP_MESSAGE_LEN> _data;

    packet _request;

    ssize_t _count;
    ssize_t _max_count;
    ssize_t _timeout_ms;
    bool _verbose;
};

} // namespace addp

#endif // ADDP_action_H
