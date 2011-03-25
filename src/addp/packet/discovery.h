#ifndef ADDP_PACKETS_H
#define ADDP_PACKETS_H

#include <addp/types.h>
#include <addp/packet/packet.h>

namespace addp {

class discovery_request : public packet
{
public:
    discovery_request(const mac_address mac = MAC_ADDR_BROADCAST);
};

class discovery_response : public packet
{
public:
    discovery_response();
};

} // namespace addp

#endif // ADDP_PACKETS_H
