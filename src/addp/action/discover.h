#ifndef ADDP_DISCOVER_H
#define ADDP_DISCOVER_H

#include <addp/constants.h>
#include <addp/types.h>
#include <addp/action/action.h>

namespace addp {

class discover : public action
{
public:
    discover(const mac_address& mac_address = MAC_ADDR_BROADCAST);

    void set_mac_address(const std::string& mac);
};

} // namespace addp

#endif // ADDP_DISCOVER_H
