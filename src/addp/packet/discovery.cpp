#include "discovery.h"

namespace addp {

discovery_request::discovery_request(
        const mac_address mac
        ) :
    packet(packet::PT_DISCOVERY_REQUEST)
{
    add(mac);
}

discovery_response::discovery_response() :
    packet(packet::PT_DISCOVERY_RESPONSE)
{
}

} // namespace addp
