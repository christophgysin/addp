#include "options.h"

#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>

options::options(int argc, char* argv[])
{
    parse(argc, argv);
}

void options::parse(int argc, char* argv[])
{
    _progname = boost::filesystem::path(argv[0]).filename();

    boost::program_options::options_description all_options = this->all_options();

    boost::program_options::command_line_parser parser(argc, argv);
    boost::program_options::store(parser.options(all_options).run(), _vm);
    boost::program_options::notify(_vm);

    if(_vm.count("help"))
    {
        std::cout << all_options << std::endl;
        std::exit(1);
    }
}

std::string options::usage()
{
    return str(boost::format(
                "Usage: %s [options]...\n"
                "\n"
                "options")
            % _progname);
}

boost::program_options::options_description options::all_options()
{
    boost::program_options::options_description options = generic_options();
    return options;
}

boost::program_options::options_description options::generic_options()
{
    boost::program_options::options_description options(usage());
    options.add_options()
        ("help,h",
            "produce help message")
        ("version,V",
            boost::program_options::value<bool>()->default_value(false)->zero_tokens(),
            "program version")
        ("verbose,v",
            boost::program_options::value<int>()->default_value(0),
            "verbosity level")
        ;
    return options;
}

size_t options::count(const char* key) const
{
    return _vm.count(key);
}

bool options::version() const
{
    return _vm["version"].as<bool>();
}

int options::verbose() const
{
    return _vm["verbose"].as<int>();
}
