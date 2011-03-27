#ifndef ADDP_REBOOT_H
#define ADDP_REBOOT_H

#include <addp/constants.h>
#include <addp/types.h>
#include <addp/action/action.h>

namespace addp {

class reboot : public action
{
public:
    reboot(const mac_address& mac_address = MAC_ADDR_BROADCAST,
            const std::string& password = DEFAULT_PASSWORD);

    void set_mac_address(const std::string& mac);
    void set_password(const std::string& password);

private:
    mac_address _mac_address;
    std::string _password;
};

} // namespace addp

#endif // ADDP_REBOOT_H
