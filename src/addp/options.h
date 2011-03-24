#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>
#include <boost/program_options.hpp>

namespace addp {

class options
{
public:
    options(){}
    options(int argc, char* argv[]);
    void parse(int argc, char* argv[]);

    size_t count(const char* key) const;

    bool version() const;
    int verbose() const;

protected:
    virtual std::string usage();

    virtual boost::program_options::options_description all_options();
    virtual boost::program_options::options_description generic_options();

    boost::program_options::variables_map _vm;
    std::string _progname;
};

} // namespace addp

#endif // OPTIONS_H
