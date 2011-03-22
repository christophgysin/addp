#ifndef ADDP_PACKET_H
#define ADDP_PACKET_H

#include <stdint.h>
#include <arpa/inet.h>
#include <cstring>
#include <vector>
#include <ostream>
#include <iomanip>
#include <algorithm>

#include <boost/foreach.hpp>

#include "field.h"

namespace addp {

class packet
{
public:
    static const char* MAGIC;

    struct packet_header {
        char magic[4];
        uint16_t type;
        uint16_t size;
        packet_header() { strncpy(magic, MAGIC, 4); }
    };

    enum packet_type {
        PT_NONE = 0x00,
        PT_DISCOVERY_REQUEST,
        PT_DISCOVERY_RESPONSE,
        PT_STATIC_NET_CONFIG_REQUEST,
        PT_STATIC_NET_CONFIG_REPONSE,
        PT_REBOOT_REQUEST,
        PT_REBOOT_REPONSE,
        PT_DHCP_NET_CONFIG_REQUEST,
        PT_DHCP_NET_CONFIG_REPONSE,
    };

    packet();
    packet(packet_type t);
    packet(uint8_t* data, size_t len);

    bool check();
    packet_type type() const;
    uint16_t size() const;
    const std::vector<uint8_t>& payload() const;
    void add_raw(const uint8_t* data, size_t len);
    std::vector<uint8_t> raw() const;
    static std::string packet_type2str(packet_type type);

private:
    packet_header _header;
    std::vector<uint8_t> _payload;
    std::vector<field> _fields;
};

class discovery_request : public packet
{
    static const uint64_t MAC_ADDR_BROADCAST = 0xffffffffffff;
public:
    discovery_request(const uint64_t mac_addr = MAC_ADDR_BROADCAST);
};

} // namespace addp

std::ostream& operator<<(std::ostream& os, const addp::packet& packet);

#endif // ADDP_PACKET_H
