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
        PT_STATIC_NET_CONFIG_RESPONSE,
        PT_REBOOT_REQUEST,
        PT_REBOOT_RESPONSE,
        PT_DHCP_NET_CONFIG_REQUEST,
        PT_DHCP_NET_CONFIG_RESPONSE,
    };

    packet(packet_type t);
    packet(const uint8_t* data, size_t len);

    bool check() const;

    packet_type type() const;
    std::string type_str() const;

    uint16_t size() const;
    void add_raw(const uint8_t* data, size_t len);
    const std::vector<uint8_t>& payload() const;
    std::vector<uint8_t> raw() const;

    bool parse_fields();
    const std::vector<field>& fields() const;

private:
    static std::string packet_type2str(packet_type type);

    packet_header _header;
    std::vector<uint8_t> _payload;
    std::vector<field> _fields;
};

} // namespace addp

std::ostream& operator<<(std::ostream& os, const addp::packet& packet);

#endif // ADDP_PACKET_H
