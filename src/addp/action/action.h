#ifndef ADDP_ACTION_ACTION_H
#define ADDP_ACTION_ACTION_H

#include <list>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/function.hpp>

#include <addp/constants.h>
#include <addp/types.h>
#include <addp/packet/packet.h>

namespace addp {

class action
{
public:
    typedef boost::function<void (boost::asio::ip::udp::endpoint sender, packet)> callback_t;

    action(const packet& request);

    void set_listen_address(const std::string& listen_ip, uint16_t port = UDP_PORT);
    void set_dest_address(const std::string& dest_ip, uint16_t port = UDP_PORT);
    void set_request(const packet& request);
    void set_timeout(size_t timeout_ms);
    void set_max_count(size_t max_count);
    void set_verbose(size_t verbose);
    void set_callback(callback_t callback);

    bool run();
    void stop();

protected:
    virtual void print_brief(const boost::asio::ip::udp::endpoint& sender, const packet&) const;
    virtual void print_verbose(const boost::asio::ip::udp::endpoint& sender, const packet&) const;

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
    callback_t _callback;

    size_t _count;
    size_t _max_count;
    size_t _timeout_ms;
    size_t _verbose;
};

} // namespace addp

#endif // ADDP_ACTION_ACTION_H
