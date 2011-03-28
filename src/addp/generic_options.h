#ifndef ADDP_GENERIC_OPTIONS_H
#define ADDP_GENERIC_OPTIONS_H

#include <string>
#include <boost/program_options.hpp>

namespace addp {

class generic_options
{
public:
    generic_options(){}
    generic_options(int argc, char* argv[]);

    void parse(int argc, char* argv[]);
    std::string usage() const;

    bool version() const;
    int verbose() const;

protected:
    virtual boost::program_options::options_description all_options() const;

    boost::program_options::variables_map _vm;

private:
    std::string _progname;
    std::string _usage;
};

} // namespace addp

#endif // ADDP_GENERIC_OPTIONS_H
