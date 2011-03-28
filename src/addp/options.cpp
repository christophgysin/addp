#include "options.h"

#include <iostream>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>

#include "constants.h"

namespace addp {

options::options(int argc, char* argv[])
{
    parse(argc, argv);
}

boost::program_options::options_description options::all_options() const
{
    boost::program_options::options_description opts = generic_options::all_options();

    const std::string usage = "ADDP options";

    boost::program_options::options_description addp_opts(usage);
    addp_opts.add_options()
        ("logfile,l",
            boost::program_options::value<std::string>()->default_value("/dev/stdout"),
            "logfile")
        ("listen,L",
            boost::program_options::value<std::string>()->default_value("0.0.0.0"),
            "ip address to listen")
        ("port,p",
            boost::program_options::value<uint16_t>()->default_value(UDP_PORT),
            "udp port")
        ;

    opts.add(addp_opts);
    return opts;
}

std::string options::logfile() const
{
    return _vm["logfile"].as<std::string>();
}

std::string options::listen() const
{
    return _vm["listen"].as<std::string>();
}

uint16_t options::port() const
{
    return _vm["port"].as<uint16_t>();
}

} // namespace addp
