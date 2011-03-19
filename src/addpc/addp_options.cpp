#include "addp_options.h"

#include <addp.h>

addp_options::addp_options(int argc, char* argv[])
{
    parse(argc, argv);
}

boost::program_options::options_description addp_options::all_options()
{
    boost::program_options::options_description options = options::all_options();

    const std::string usage = "ADDP options";

    boost::program_options::options_description addp_options(usage);
    options.add_options()
        ("port,p",
            boost::program_options::value<uint16_t>()->default_value(addp::UDP_PORT),
            "udp port")
        ("host,u",
            boost::program_options::value<std::string>()->default_value(addp::IP_ADDRESS),
            "host")
        ("logfile,l",
            boost::program_options::value<std::string>()->default_value("/dev/stdout"),
            "logfile")
        ("timeout,t",
            boost::program_options::value<unsigned int>(),
            "response timeout")
    ;

    options.add(addp_options);
    return options;
}

uint16_t addp_options::port() const
{
    return _vm["port"].as<uint16_t>();
}

std::string addp_options::host() const
{
    return _vm["host"].as<std::string>();
}

std::string addp_options::logfile() const
{
    return _vm["logfile"].as<std::string>();
}

unsigned int addp_options::timeout() const
{
    return _vm["timeout"].as<unsigned int>();
}
