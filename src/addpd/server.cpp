#include "server.h"

#include <iostream>
#include <boost/asio/buffer.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/ip/multicast.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>

#include "connection.h"

server::server(uint16_t port, const std::string& mcast_ip) :
    _io_service(),
    _listen_address(boost::asio::ip::udp::v4(), port),
    _socket(_io_service, _listen_address),
    _thread_count(4)
{
    _socket.set_option(
            boost::asio::ip::multicast::join_group(
                boost::asio::ip::address::from_string(mcast_ip)
            )
        );

    _socket.async_receive_from(
        boost::asio::buffer(_data), _sender_address,
        boost::bind(&server::handle_receive_from, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void server::run()
{
    std::vector<boost::shared_ptr<boost::thread> > threads;
    for(size_t i=0; i < _thread_count; ++i)
    {
        boost::shared_ptr<boost::thread> thread(
                new boost::thread(boost::bind(&boost::asio::io_service::run, &_io_service)));
        threads.push_back(thread);
    }

    for(size_t i=0; i < threads.size(); ++i)
        threads[i]->join();
}

void server::stop()
{
    _io_service.stop();
}

void server::handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd)
{
    if(!error && bytes_recvd > 0)
        new connection(_socket, _sender_address, addp::packet(_data.data(), bytes_recvd));
    else
        std::cerr << "error: " << error.message() << " (" << error.value() << ") "
            << "bytes_recvd: " << bytes_recvd << std::endl;

    _socket.async_receive_from(
        boost::asio::buffer(_data), _sender_address,
        boost::bind(&server::handle_receive_from, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

