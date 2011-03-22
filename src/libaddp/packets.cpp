#include "packets.h"

namespace addp {

discovery_request::discovery_request(const uint64_t mac_addr) :
    packet(addp::packet::PT_DISCOVERY_REQUEST)
{
    add_raw(reinterpret_cast<const uint8_t*>(&mac_addr), 6);
}

} // namespace addp
