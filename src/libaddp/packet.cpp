#include <cstring>
#include <packet.h>

namespace addp {

const char* packet::MAGIC = "DIGI";

packet::packet()
{
}

packet::packet(packet::packet_type type)
{
    _header.packet_type = htons(type);
}

packet::packet(uint8_t* data, size_t len)
{
    // header
    memcpy(&_header, data, sizeof(packet_type));

    // payload
    _payload.clear();
    _payload.reserve(len - sizeof(packet_type));
    copy(data+sizeof(packet_type), data+len, back_inserter(_payload));
}

bool packet::check()
{
    if(_payload.size() != _header.payload_size)
        return false;

    return true;
}

packet::packet_type packet::type() const
{
    return static_cast<packet::packet_type>(ntohs(_header.packet_type));
}

const std::vector<uint8_t>& packet::payload() const
{
    return _payload;
}

void packet::add_raw(const uint8_t* data, size_t len)
{
    copy(data, data+len, back_inserter(_payload));
    _header.payload_size = htons(_payload.size());
}

std::vector<uint8_t> packet::raw() const
{
    std::vector<uint8_t> buffer;
    const uint8_t* headerp = reinterpret_cast<const uint8_t*>(&_header);
    copy(headerp, headerp+sizeof(packet_header), back_inserter(buffer));
    copy(_payload.begin(), _payload.end(), back_inserter(buffer));

    return buffer;
}

std::string addp::packet::packet_type2str(packet_type type)
{
    switch(type)
    {
        case PT_NONE:
            return "None";
        case PT_DISCOVERY_REQUEST:
            return "Discovery Request";
        case PT_DISCOVERY_RESPONSE:
            return "Discovery Response";
        case PT_STATIC_NET_CONFIG_REQUEST:
            return "Net Config Request";
        case PT_STATIC_NET_CONFIG_REPONSE:
            return "Net Config Response";
        case PT_REBOOT_REQUEST:
            return "Reboot Request";
        case PT_REBOOT_REPONSE:
            return "Reboot Response";
        case PT_DHCP_NET_CONFIG_REQUEST:
            return "DHCP Net Config Request";
        case PT_DHCP_NET_CONFIG_REPONSE:
            return "DHCP Net Config Response";
    };
    return "Unknown";
}

/* discovery request */

discovery_request::discovery_request(const uint64_t mac_addr) :
    packet(addp::packet::PT_DISCOVERY_REQUEST)
{
    add_raw(reinterpret_cast<const uint8_t*>(&mac_addr), 6);
}

} // namespace addp

std::ostream& operator<<(std::ostream& os, const addp::packet& packet)
{
    os << addp::packet::packet_type2str(packet.type());

    switch(packet.type())
    {
        case addp::packet::PT_DISCOVERY_REQUEST:
            os << std::hex << std::setfill('0');

            BOOST_FOREACH(uint8_t b, packet.payload())
                os << ":" << int(b);
            break;

        default:
            break;
    }

    os << " (";
    BOOST_FOREACH(uint8_t b, packet.raw())
        os << " " << std::hex << std::setfill('0') << std::setw(2) << int(b);
    os << ")";

    return os;
}
