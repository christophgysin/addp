#include "options.h"

#include <addp.h>

namespace addpd {

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
        ("port,p",
            boost::program_options::value<uint16_t>()->default_value(addp::UDP_PORT),
            "udp port")
        ("host,u",
            boost::program_options::value<std::string>()->default_value(addp::IP_ADDRESS),
            "host")
    ;

    opts.add(addpc_opts);
    return opts;
}

std::string options::logfile() const
{
    return _vm["logfile"].as<std::string>();
}

uint16_t options::port() const
{
    return _vm["port"].as<uint16_t>();
}

std::string options::host() const
{
    return _vm["host"].as<std::string>();
}

} // namespace addpd
