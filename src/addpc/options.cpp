#include "options.h"

#include <addp.h>

namespace addpc {

options::options(int argc, char* argv[])
{
    parse(argc, argv);
}

boost::program_options::options_description options::all_options()
{
    boost::program_options::options_description opts = addp::options::all_options();

    const std::string usage = "ADDP options";

    boost::program_options::options_description addpc_opts(usage);
    addpc_opts.add_options()
        ("logfile,l",
            boost::program_options::value<std::string>()->default_value("/dev/stdout"),
            "logfile")
        ("listen,L",
            boost::program_options::value<std::string>()->default_value("0.0.0.0"),
            "ip address to listen")
        ("port,p",
            boost::program_options::value<uint16_t>()->default_value(addp::UDP_PORT),
            "udp port")
        ("multicast,m",
            boost::program_options::value<std::string>()->default_value(addp::MCAST_IP_ADDRESS),
            "multicast address for discovery")
        ("action,a",
            boost::program_options::value<std::string>()->default_value("discover"),
            "action (discover/static/reboot/dhcp)")
        ("timeout,t",
            boost::program_options::value<ssize_t>()->default_value(2000),
            "response timeout (in ms)")
        ("max_count,c",
            boost::program_options::value<ssize_t>()->default_value(0),
            "stop after receiving n responses")
    ;

    opts.add(addpc_opts);
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

std::string options::multicast() const
{
    return _vm["multicast"].as<std::string>();
}

std::string options::action() const
{
    return _vm["action"].as<std::string>();
}

ssize_t options::timeout() const
{
    return _vm["timeout"].as<ssize_t>();
}

ssize_t options::max_count() const
{
    return _vm["max_count"].as<ssize_t>();
}


} // namespace addpc
