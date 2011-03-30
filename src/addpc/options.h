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

    std::string multicast() const;

    ssize_t timeout() const;

    std::string mac() const;
    std::string password() const;

    ssize_t max_count() const;

    std::string action() const;

protected:
    virtual boost::program_options::options_description all_options() const;
    virtual boost::program_options::positional_options_description positional_options() const;
    virtual boost::program_options::options_description visible_options() const;

private:
    boost::program_options::options_description addpc_options() const;
    boost::program_options::options_description addpc_hidden_options() const;
};

} // namespace addpc

#endif // ADDPC_OPTIONS_H
