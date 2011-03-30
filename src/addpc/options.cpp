#include "options.h"

#include <iostream>
#include <boost/lexical_cast.hpp>

namespace addpc {

options::options(int argc, char* argv[])
{
    _usage = std::string() +
        "Usage: %s [options...] <action> [args...]\n" +
        "\n" +
        " actions:\n" +
        "  discover [device]\n" +
        "  reboot <device> [passwd]\n" +
        "  config <device> <ip> <netmask> <gateway> [passwd]\n" +
        "  dhcp <device> <on|off> [passwd]\n";

    parse(argc, argv);
}

void options::parse(int argc, char* argv[])
{
    addp::options::parse(argc, argv);

    if(_vm.count("action") == 0)
    {
        std::cerr << "No action given" << std::endl << std::endl;
        usage();
        std::exit(1);
    }

    /*
     *  discover [device]
     *  reboot <device> [passwd]
     *  config <device> <ip> <netmask> <gateway> [passwd]
     *  dhcp <device> <on|off> [passwd]
     */

    size_t min = 0;
    size_t max = 0;

    const std::string& action = this->action();

    if(action == "discover")
    {
        min = 0;
        max = 0;
    }
    else
    {
        // must have a specific device address for further actions
        if(boost::lexical_cast<addp::mac_address>(mac()) == addp::MAC_ADDR_BROADCAST)
        {
            std::cerr << "Please select a device's mac address" << std::endl << std::endl;
            usage();
            std::exit(1);
        }

        if(action == "reboot")
        {
            min = 0;
            max = 1;
        }
        else if(action == "config")
        {
            min = 3;
            max = 4;
        }
        else if(action == "dhcp")
        {
            min = 1;
            max = 2;
        }
        else
        {
            std::cerr << "Unknown action \"" << action << "\"" << std::endl << std::endl;
            usage();
            std::exit(1);
        }
    }

    size_t count = args().size();
    if(count < min || count > max)
    {
        usage();
        std::exit(1);
    }

    // optional password is always the last argument
    _password_index = max - 1;
}

boost::program_options::options_description options::addpc_options() const
{
    const std::string usage = "ADDP client options";

    boost::program_options::options_description addpc_opts(usage);
    addpc_opts.add_options()
        ("multicast,m",
            boost::program_options::value<std::string>()
                ->default_value(addp::MCAST_IP_ADDRESS),
            "multicast address for discovery")
        ("timeout,t",
            boost::program_options::value<size_t>()
                ->default_value(addp::DEFAULT_TIMEOUT),
            "response timeout (in ms)")
        ("max_count,c",
            boost::program_options::value<size_t>()
                ->default_value(addp::DEFAULT_MAX_COUNT),
            "stop after receiving n responses")
        ;
    return addpc_opts;
}

boost::program_options::options_description options::addpc_hidden_options() const
{
    boost::program_options::options_description hidden_opts;
    hidden_opts.add_options()
        ("action",
            boost::program_options::value<std::string>(),
            "action (discover/static/reboot/dhcp)")
        ("mac",
            boost::program_options::value<std::string>()
                ->default_value("ff:ff:ff:ff:ff:ff"),
            "mac address of target device")
        ("args",
            boost::program_options::value<std::vector<std::string> >()
                ->default_value(std::vector<std::string>(), "")
                ->multitoken(),
            "action arguments")
        ;
    return hidden_opts;
}

boost::program_options::options_description options::visible_options() const
{
    boost::program_options::options_description opts = addp::options::all_options();
    opts.add(addpc_options());
    return opts;
}

boost::program_options::options_description options::all_options() const
{
    boost::program_options::options_description opts = addp::options::all_options();
    opts.add(addpc_options());
    opts.add(addpc_hidden_options());
    return opts;
}

boost::program_options::positional_options_description options::positional_options() const
{
    boost::program_options::positional_options_description positional = addp::options::positional_options();
    positional
        .add("action", 1)
        .add("mac", 1)
        .add("args", -1)
        ;
    return positional;
}

std::string options::multicast() const
{
    return _vm["multicast"].as<std::string>();
}

size_t options::timeout() const
{
    return _vm["timeout"].as<size_t>();
}

size_t options::max_count() const
{
    return _vm["max_count"].as<size_t>();
}

std::string options::action() const
{
    return _vm["action"].as<std::string>();
}

std::string options::mac() const
{
    return _vm["mac"].as<std::string>();
}

std::vector<std::string> options::args() const
{
    return _vm["args"].as<std::vector<std::string> >();
}

std::string options::password() const
{
    if(args().size() <= _password_index)
        return addp::DEFAULT_PASSWORD;

    return args()[_password_index];
}

std::string options::ip() const
{
    return args()[0];
}

std::string options::subnet() const
{
    return args()[1];
}

std::string options::gateway() const
{
    return args()[2];
}

bool options::dhcp() const
{
    std::string value = args()[0];

    if(value == "on")
        return true;

    if(value == "off")
        return false;

    std::cerr << "illegal value for dhcp: \"" << value << "\"" << std::endl << std::endl;
    usage();
    std::exit(1);
}

} // namespace addpc
