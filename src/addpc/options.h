#ifndef ADDPC_OPTIONS_H
#define ADDPC_OPTIONS_H

#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <addp/addp.h>

namespace addpc {

class options : public addp::options
{
public:
    options(int argc, char* argv[]);

    std::string listen() const;
    size_t timeout() const;
    size_t max_count() const;

    std::string action() const;
    std::string mac() const;
    std::vector<std::string> args() const;

    // action options
    std::string password() const;
    std::string ip() const;
    std::string subnet() const;
    std::string gateway() const;
    bool dhcp() const;

protected:
    void parse(int argc, char* argv[]);

    virtual boost::program_options::options_description all_options() const;
    virtual boost::program_options::positional_options_description positional_options() const;
    virtual boost::program_options::options_description visible_options() const;

private:
    boost::program_options::options_description addpc_options() const;
    boost::program_options::options_description addpc_hidden_options() const;

    size_t _password_index;
};

} // namespace addpc

#endif // ADDPC_OPTIONS_H
