#include "types.h"
#include "packet.h"

namespace addp {

static const mac_address MAC_ADDR_BROADCAST = {{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }};

class discovery_request : public packet
{
public:
    discovery_request(const mac_address mac_addr = MAC_ADDR_BROADCAST);
};

} // namespace addp
