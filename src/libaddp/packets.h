#include "packet.h"

namespace addp {

class discovery_request : public packet
{
    static const uint64_t MAC_ADDR_BROADCAST = 0xffffffffffff;
public:
    discovery_request(const uint64_t mac_addr = MAC_ADDR_BROADCAST);
};

} // namespace addp
