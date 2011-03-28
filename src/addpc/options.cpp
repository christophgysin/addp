#include "options.h"

namespace addpc {

options::options(int argc, char* argv[])
{
    parse(argc, argv);
}

boost::program_options::options_description options::all_options() const
{
    boost::program_options::options_description opts = addp::options::all_options();

    const std::string usage = "ADDP client options";

    boost::program_options::options_description addpc_opts(usage);
    addpc_opts.add_options()
        ("multicast,m",
            boost::program_options::value<std::string>()->default_value(addp::MCAST_IP_ADDRESS),
            "multicast address for discovery")
        ("timeout,t",
            boost::program_options::value<ssize_t>()->default_value(addp::DEFAULT_TIMEOUT),
            "response timeout (in ms)")
        ("max_count,c",
            boost::program_options::value<ssize_t>()->default_value(addp::DEFAULT_MAX_COUNT),
            "stop after receiving n responses")
        ("action,a",
            boost::program_options::value<std::string>()->default_value("discover"),
            "action (discover/static/reboot/dhcp)")
        ("mac,M",
            boost::program_options::value<std::string>()->default_value("ff:ff:ff:ff:ff:ff"),
            "mac address of target device")
        ("password,p",
            boost::program_options::value<std::string>()->default_value(addp::DEFAULT_PASSWORD),
            "device password")
    ;

    opts.add(addpc_opts);
    return opts;
}

std::string options::multicast() const
{
    return _vm["multicast"].as<std::string>();
}

ssize_t options::timeout() const
{
    return _vm["timeout"].as<ssize_t>();
}

ssize_t options::max_count() const
{
    return _vm["max_count"].as<ssize_t>();
}

std::string options::action() const
{
    return _vm["action"].as<std::string>();
}

std::string options::mac() const
{
    return _vm["mac"].as<std::string>();
}

std::string options::password() const
{
    return _vm["password"].as<std::string>();
}

} // namespace addpc
