#include "options.h"

namespace addpd {

options::options(int argc, char* argv[])
{
    parse(argc, argv);
}

boost::program_options::options_description options::all_options() const
{
    boost::program_options::options_description opts = addp::options::all_options();

    const std::string usage = "ADDP daemon options";

    boost::program_options::options_description addpd_opts(usage);
    addpd_opts.add_options()
        ("threads,t",
            boost::program_options::value<size_t>()
                ->default_value(2),
            "number of threads to handle requests")
    ;

    opts.add(addpd_opts);
    return opts;
}

size_t options::threads() const
{
    return _vm["threads"].as<ssize_t>();
}

} // namespace addpd
