#include "client.h"

#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>

#include <packet.h>
#include <packets.h>

#include "options.h"

namespace addpc {

client::client(const options& options) :
    _options(options),
    _io_service(),
    _address(boost::asio::ip::address::from_string(options.host())),
    _endpoint(_address, options.port()),
    _sender(),
    _socket(_io_service)
{
    _socket.open(boost::asio::ip::udp::v4());
}

bool client::run()
{
    if(_options.action() == "discover")
        return discover();
    if(_options.action() == "static")
        return static_net_config();
    if(_options.action() == "reboot")
        return reboot();
    if(_options.action() == "dhcp")
        return dhcp_net_config();

    std::cerr << "Unknown option! (" << _options.action() << ")" << std::endl;
    return false;
}

bool client::discover()
{
    addp::discovery_request request;

    if(_options.verbose())
        std::cout << "sending to: " << _endpoint << " packet: " << request
            << std::endl << std::endl;

    boost::asio::ip::udp::endpoint endpoint(
            boost::asio::ip::address::from_string(addp::IP_ADDRESS),
            addp::UDP_PORT);

    _socket.async_send_to(
        boost::asio::buffer(request.raw()), endpoint,
        boost::bind(&client::handle_send_to, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));

    _io_service.run();

    return true;
}

void client::handle_send_to(const boost::system::error_code& /*error*/, size_t /*bytes_sent*/)
{
    _socket.async_receive_from(
        boost::asio::buffer(_data, max_length), _sender,
        boost::bind(&client::handle_receive_from, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void client::handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd)
{
    if(!error && bytes_recvd > 0)
    {
        addp::packet response(_data.data(), bytes_recvd);

        if(!response.parse_fields())
            std::cerr << "failed to parse fields!" << std::endl;

        std::cout << _sender << " " << response << std::endl;
    }
    else
        std::cout << "error: " <<  error.value() << "(" << error.message() << ")"
            << " received: " << bytes_recvd << std::endl;

    _socket.async_receive_from(
        boost::asio::buffer(_data, max_length), _sender,
        boost::bind(&client::handle_receive_from, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

bool client::static_net_config()
{
    return false;
}

bool client::reboot()
{
    return false;
}

bool client::dhcp_net_config()
{
    return false;
}

} // namespace addpc
