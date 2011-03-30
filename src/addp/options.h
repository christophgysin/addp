#ifndef ADDP_OPTIONS_H
#define ADDP_OPTIONS_H

#include <stdint.h>
#include <string>
#include <boost/program_options.hpp>

#include "generic_options.h"

namespace addp {

class options : public generic_options
{
public:
    options(){}
    options(int argc, char* argv[]);

    std::string logfile() const;

    std::string listen() const;
    uint16_t port() const;

protected:
    virtual boost::program_options::options_description all_options() const;
};

} // namespace addp

#endif // ADDP_OPTIONS_H
