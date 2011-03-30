#include "generic_options.h"

#include <iostream>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>

namespace addp {

generic_options::generic_options(int argc, char* argv[])
{
    parse(argc, argv);
}

void generic_options::parse(int argc, char* argv[])
{
    _progname = boost::filesystem::path(argv[0]).filename();
    _usage = str(boost::format(
                "Usage: %s [options]...\n"
                "\n"
                "Generic options")
            % _progname);

    boost::program_options::command_line_parser parser(argc, argv);
    boost::program_options::store(
            parser
                .options(all_options())
                .positional(positional_options())
                .run(),
            _vm);
    boost::program_options::notify(_vm);

    if(_vm.count("help"))
    {
        usage();
        std::exit(1);
    }
}

void generic_options::usage() const
{
    std::cout << visible_options();
}

boost::program_options::options_description generic_options::all_options() const
{
    boost::program_options::options_description opts(_usage);
    opts.add_options()
        ("help,h",
            "produce help message")
        ("version,V",
            boost::program_options::value<bool>()
                ->default_value(false)
                ->zero_tokens(),
            "program version")
        ("verbose,v",
            boost::program_options::value<int>()
                ->default_value(0)
                ->implicit_value(1),
            "verbosity level")
        ;
    return opts;
}

boost::program_options::positional_options_description generic_options::positional_options() const
{
    boost::program_options::positional_options_description positional;
    return positional;
}

boost::program_options::options_description generic_options::visible_options() const
{
    return all_options();
}

bool generic_options::version() const
{
    return _vm["version"].as<bool>();
}

int generic_options::verbose() const
{
    return _vm["verbose"].as<int>();
}

} // namespace addp
