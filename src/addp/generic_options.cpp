#include "generic_options.h"

#include <iostream>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>

namespace addp {

generic_options::generic_options() :
    _usage("Usage: %s [options...]\n")
{
}

generic_options::generic_options(int argc, char* argv[]) :
    _usage("Usage: %s [options...]\n")
{
    parse(argc, argv);
}

void generic_options::parse(int argc, char* argv[])
{
    _progname = boost::filesystem::path(argv[0]).filename();

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
    std::cout
        << str(boost::format(_usage) % _progname) << std::endl
        << visible_options();
}

boost::program_options::options_description generic_options::all_options() const
{
    boost::program_options::options_description opts("Generic options");
    opts.add_options()
        ("help,h",
            "produce help message")
        ("version,V",
            boost::program_options::value<bool>()
                ->default_value(false)
                ->zero_tokens(),
            "program version")
        ("verbose,v",
            boost::program_options::value<size_t>()
                ->default_value(0)
                ->implicit_value(1)
                ->zero_tokens(),
            "verbose")
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

size_t generic_options::verbose() const
{
    return _vm["verbose"].as<size_t>();
}

} // namespace addp
