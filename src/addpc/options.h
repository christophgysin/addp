#ifndef ADDPC_OPTIONS_H
#define ADDPC_OPTIONS_H

#include <options.h>

#include <string>
#include <boost/program_options.hpp>

namespace addpc {

class options : public addp::options
{
public:
    options(int argc, char* argv[]);

    std::string logfile() const;

    std::string host() const;
    uint16_t port() const;

    unsigned int timeout() const;

    std::string action() const;

protected:
    virtual boost::program_options::options_description all_options();
};

} // namespace addpc

#endif // ADDPC_OPTIONS_H
