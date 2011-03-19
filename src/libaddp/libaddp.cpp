#include "addp.h"
#include "libaddp.h"
#include "endian.h"

namespace addp {

std::string version()
{
    return "0.1";
}

std::vector<uint8_t> discovery_request(const uint64_t mac_addr)
{
    static const size_t MAC_ADDR_LEN = 6;

    const size_t size = sizeof(packet_header) + MAC_ADDR_LEN;
    uint8_t packet[size];

    packet_header* header = (packet_header*)&packet;
    big_endian<uint16_t>(PT_DISCOVERY_REQUEST, &header->packet_type);
    strncpy(header->magic, MAGIC, 4);

    for(int i=MAC_ADDR_LEN-1; i>=0; --i)
        header->payload[i] = mac_addr >> (i*8);
    big_endian<uint16_t>(MAC_ADDR_LEN, &header->payload_size);

    return std::vector<uint8_t>(packet, packet+size);
}

} // namespace addp
