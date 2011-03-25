#include "reboot.h"

namespace addp {

reboot_request::reboot_request(
        const mac_address& mac,
        const std::string& auth
        ) :
    packet(packet::PT_REBOOT_REQUEST)
{
    add(mac);
    add(auth);
}

reboot_response::reboot_response() :
    packet(packet::PT_REBOOT_RESPONSE)
{
}

} // namespace addp
