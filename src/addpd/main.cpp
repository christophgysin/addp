#include <boost/asio/io_service.hpp>

#include "options.h"
#include "server.h"

int main(int argc, char* argv[])
{
    addpd::options options(argc, argv);

    boost::asio::io_service io_service;
    server s(io_service, options.port());
    io_service.run();

    return 0;
}
