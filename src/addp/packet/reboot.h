#ifndef ADDP_PACKET_REBOOT_H
#define ADDP_PACKET_REBOOT_H

#include <addp/types.h>
#include <addp/packet/packet.h>

namespace addp {

class reboot_request : public packet
{
public:
    reboot_request(
        const mac_address& mac = MAC_ADDR_BROADCAST,
        const std::string& auth = DEFAULT_PASSWORD
        );
};

class reboot_response : public packet
{
public:
    reboot_response();
};

} // namespace addp

#endif // ADDP_PACKET_REBOOT_H
