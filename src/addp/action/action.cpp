#include "action.h"

#include <iostream>
#include <boost/bind.hpp>
#include <boost/format.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <addp/packet/packet.h>
#include <addp/packet/packet_io.h>
#include <addp/types_io.h>

namespace addp {

action::action(const packet& request) :
    _listen_address(boost::asio::ip::udp::v4(), UDP_PORT),
    _dest_address(boost::asio::ip::address::from_string(MCAST_IP_ADDRESS), UDP_PORT),
    _sender_address(),
    _io_service(),
    _socket(_io_service),
    _deadline(_socket.get_io_service()),
    _request(request),
    _callback(boost::bind(&action::print_brief, this, _1, _2)),
    _count(0),
    _max_count(DEFAULT_MAX_COUNT),
    _timeout_ms(DEFAULT_TIMEOUT),
    _verbose(0)
{
    // disable timer by setting expiry time to infinity
    _deadline.expires_at(boost::posix_time::pos_infin);
    check_timeout();
}

void action::set_listen_address(const std::string& listen_ip, uint16_t port)
{
    _listen_address = boost::asio::ip::udp::endpoint(
            boost::asio::ip::address::from_string(listen_ip), port);
}

void action::set_dest_address(const std::string& dest_ip, uint16_t port)
{
    _dest_address = boost::asio::ip::udp::endpoint(
            boost::asio::ip::address::from_string(dest_ip), port);
}

void action::set_request(const packet& request)
{
    _request = request;
}

void action::set_timeout(size_t timeout_ms)
{
    _timeout_ms = timeout_ms;
}

void action::set_max_count(size_t max_count)
{
    _max_count = max_count;
}

void action::set_verbose(size_t verbose)
{
    _verbose = verbose;

    if(verbose)
        set_callback(boost::bind(&action::print_verbose, this, _1, _2));
    else
        set_callback(boost::bind(&action::print_brief, this, _1, _2));
}

void action::set_callback(callback_t callback)
{
    _callback = callback;
}

bool action::run()
{
    _socket.open(boost::asio::ip::udp::v4());
    _socket.bind(_listen_address);

    if(_verbose)
        std::cout << "sending to: " << _dest_address << " packet: " << _request
            << std::endl << std::endl;

    // send request to multicast address
    _socket.async_send_to(
        boost::asio::buffer(_request.raw()),
        _dest_address,
        boost::bind(&action::handle_send_to, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));

    // set timeout from now
    if(_timeout_ms)
        _deadline.expires_from_now(boost::posix_time::milliseconds(_timeout_ms));

    try
    {
        _io_service.run();
    }
    catch (const boost::system::system_error& error)
    {
        std::cerr <<
            str(boost::format("Error: %s (%d)")
                    % error.code().message()
                    % error.code().value())
            << std::endl;
        return false;
    }

    return true;
}

void action::stop()
{
    _socket.cancel();
    _io_service.stop();
}

void action::check_timeout()
{
    if(_deadline.expires_at() <= boost::asio::deadline_timer::traits_type::now())
    {
        if(_verbose >= 2)
            std::cout << "timeout reached (" << std::dec << _timeout_ms << "ms)" << std::endl;

        stop();
        _deadline.expires_at(boost::posix_time::pos_infin);
    }
    _deadline.async_wait(boost::bind(&action::check_timeout, this));
}

void action::handle_send_to(const boost::system::error_code& error, size_t bytes_sent)
{
    if(error)
        std::cerr << "error: " <<  error.value() << "(" << error.message() << ")"
            << " sent: " << bytes_sent << std::endl;

    _socket.async_receive_from(
        boost::asio::buffer(_data, MAX_UDP_MESSAGE_LEN), _sender_address,
        boost::bind(&action::handle_receive_from, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void action::handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd)
{
    if(!error && bytes_recvd > 0)
    {
        packet response(_data.data(), bytes_recvd);

        if(!response.parse_fields())
            std::cerr << "failed to parse fields!" << std::endl;

        _callback(_sender_address, response);

        ++_count;
    }

    // max count reached?
    if(_max_count && _count == _max_count)
    {
        if(_verbose >= 2)
            std::cout << "max_count reached (" << std::dec << _max_count << ")" << std::endl;

        stop();
        return;
    }

    // timeout reached?
    if(error == boost::asio::error::operation_aborted)
    {
        return;
    }

    // other error?
    if(error)
        std::cerr << "error: " <<  error.value() << "(" << error.message() << ")"
            << " received: " << bytes_recvd << std::endl;

    // continue receiving
    _socket.async_receive_from(
        boost::asio::buffer(_data, MAX_UDP_MESSAGE_LEN), _sender_address,
        boost::bind(&action::handle_receive_from, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void action::print_brief(const boost::asio::ip::udp::endpoint& sender, const packet& /*pckt*/) const
{
    std::cout << sender.address() << std::endl;
}

void action::print_verbose(const boost::asio::ip::udp::endpoint& sender, const packet& pckt) const
{
    std::cout << sender << " " << pckt << std::endl;
}

} // namespace addp
