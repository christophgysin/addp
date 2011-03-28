#ifndef ADDP_OPTIONS_H
#define ADDP_OPTIONS_H

#include <string>
#include <boost/program_options.hpp>

namespace addp {

class options
{
public:
    options(){}
    options(int argc, char* argv[]);

    void parse(int argc, char* argv[]);
    std::string usage() const;

    size_t count(const char* key) const;

    bool version() const;
    int verbose() const;

protected:
    virtual boost::program_options::options_description all_options() const;

    boost::program_options::variables_map _vm;

private:
    virtual boost::program_options::options_description generic_options() const;

    std::string _progname;
    std::string _usage;
};

} // namespace addp

#endif // ADDP_OPTIONS_H
