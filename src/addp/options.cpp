#include "options.h"

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
        ("multicast,m",
            boost::program_options::value<std::string>()
                ->default_value(addp::MCAST_IP_ADDRESS),
            "multicast address for discovery")
        ("port,p",
            boost::program_options::value<uint16_t>()
                ->default_value(UDP_PORT),
            "udp port")
        ;

    opts.add(addp_opts);
    return opts;
}

std::string options::multicast() const
{
    return _vm["multicast"].as<std::string>();
}

uint16_t options::port() const
{
    return _vm["port"].as<uint16_t>();
}

} // namespace addp
