#include <iostream>
#include <vector>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <boost/program_options.hpp>
namespace po = boost::program_options;

std::pair<std::string, std::string> verbosity(const std::string& s)
{
    if(s.find("-v") == 0)
    {
        size_t value = 1;
        try {
            value = boost::lexical_cast<size_t>(s.substr(2));
        }
        catch(...)
        {
            std::string::const_iterator it = s.begin();
            const std::string::const_iterator end = s.end();

            for(std::advance(it, 2); it != end && *it == 'v'; ++it)
                ++value;
        }
        return std::make_pair("verbose", boost::lexical_cast<std::string>(value));
    }
    return std::make_pair(std::string(), std::string());
}

int main(int argc, char *argv[])
{
    po::options_description desc;
    desc.add_options()
        ("verbose,v", po::value<std::vector<std::string> >(), "verbose");
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc, 0, verbosity), vm);
    po::notify(vm);

    size_t verbosity = 0;
    if(vm.count("verbose"))
        BOOST_FOREACH(const std::string& s, vm["verbose"].as<std::vector<std::string> >())
            verbosity += boost::lexical_cast<int>(s);
    std::cout << "verbosity: " << verbosity << std::endl;

    return 0;
}
