#ifndef ADDP_OPTIONS_H
#define ADDP_OPTIONS_H

#include "options.h"

#include <string>
#include <boost/program_options.hpp>

class addp_options : public options
{
public:
    addp_options(int argc, char* argv[]);

    std::string logfile() const;
    std::string host() const;
    uint16_t port() const;
    unsigned int timeout() const;

protected:
    virtual boost::program_options::options_description all_options();
};

#endif // OPTIONS_H
