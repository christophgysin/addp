#ifndef ADDP_GENERIC_OPTIONS_H
#define ADDP_GENERIC_OPTIONS_H

#include <string>
#include <boost/program_options.hpp>

namespace addp {

class generic_options
{
public:
    generic_options();
    generic_options(int argc, char* argv[]);

    void usage() const;

    bool version() const;
    size_t verbose() const;
    std::string logfile() const;

protected:
    void parse(int argc, char* argv[]);

    virtual boost::program_options::options_description all_options() const;
    virtual boost::program_options::positional_options_description positional_options() const;
    virtual boost::program_options::options_description visible_options() const;

    boost::program_options::variables_map _vm;
    std::string _usage;

private:
    std::string _progname;
};

} // namespace addp

#endif // ADDP_GENERIC_OPTIONS_H
