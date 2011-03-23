#ifndef ADDPD_OPTIONS_H
#define ADDPD_OPTIONS_H

#include <options.h>

#include <string>
#include <boost/program_options.hpp>

namespace addpd {

class options : public addp::options
{
public:
    options(int argc, char* argv[]);

    std::string logfile() const;

    std::string host() const;
    uint16_t port() const;

protected:
    virtual boost::program_options::options_description all_options();
};

} // namespace addpd

#endif // ADDPD_OPTIONS_H