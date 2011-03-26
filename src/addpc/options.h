#ifndef ADDPC_OPTIONS_H
#define ADDPC_OPTIONS_H

#include <string>
#include <boost/program_options.hpp>
#include <addp/addp.h>

namespace addpc {

class options : public addp::options
{
public:
    options(int argc, char* argv[]);

    std::string logfile() const;

    std::string listen() const;
    uint16_t port() const;
    std::string multicast() const;

    std::string mac() const;
    std::string password() const;

    ssize_t timeout() const;
    ssize_t max_count() const;

    std::string action() const;

protected:
    virtual boost::program_options::options_description all_options() const;
};

} // namespace addpc

#endif // ADDPC_OPTIONS_H
