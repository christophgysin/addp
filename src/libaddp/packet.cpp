#include "packet.h"

#include <cstring>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <boost/foreach.hpp>
#include <boost/format.hpp>

namespace addp {

const char* packet::MAGIC = "DIGI";

packet::packet(packet::packet_type type)
{
    _header.type = htons(type);
}

packet::packet(uint8_t* data, size_t len)
{
    // header
    memcpy(&_header, data, std::min(sizeof(packet_header), len));

    // payload
    if(len > sizeof(packet_header))
    {
        _payload.clear();
        _payload.reserve(len - sizeof(packet_type));
        copy(data+sizeof(packet_type), data+len, back_inserter(_payload));
    }
}

bool packet::check() const
{
    if(_payload.size() != _header.size)
        return false;

    return true;
}

packet::packet_type packet::type() const
{
    return static_cast<packet::packet_type>(ntohs(_header.type));
}

const std::vector<uint8_t>& packet::payload() const
{
    return _payload;
}

void packet::add_raw(const uint8_t* data, size_t len)
{
    copy(data, data+len, back_inserter(_payload));
    _header.size = htons(_payload.size());
}

std::vector<uint8_t> packet::raw() const
{
    std::vector<uint8_t> buffer;
    const uint8_t* headerp = reinterpret_cast<const uint8_t*>(&_header);
    copy(headerp, headerp+sizeof(packet_header), back_inserter(buffer));
    copy(_payload.begin(), _payload.end(), back_inserter(buffer));

    return buffer;
}

bool packet::parse_fields()
{
    std::vector<uint8_t>::iterator iter = _payload.begin();
    const std::vector<uint8_t>::iterator end = _payload.end();

    while(static_cast<size_t>(std::distance(iter, end)) > sizeof(field::field_header))
    {
        field f(iter, end);

        if(!f.check())
            return false;

        _fields.push_back(f);
    }

    return std::distance(iter, end) == 0;
}

const std::vector<field>& packet::fields() const
{
    /*
    if(fields.empty() && !payload.empty())
        parse_fields();
    */

    return _fields;
}

std::string addp::packet::packet_type2str(packet_type type)
{
    switch(type)
    {
        case PT_NONE:
            return "none";
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
    return str(boost::format("unknown (0x%02x)") % type);
}

} // namespace addp

std::ostream& operator<<(std::ostream& os, const addp::packet& packet)
{
    os << addp::packet::packet_type2str(packet.type()) << std::endl;

#ifdef ADDP_PACKET_DEBUG
    os << std::endl;
    os << "packet raw():" << std::endl;
    BOOST_FOREACH(uint8_t b, packet.raw())
        os << " " << std::hex << std::setfill('0') << std::setw(2) << int(b);
    os << std::endl << std::endl;
    os << "packet payload():";
    BOOST_FOREACH(uint8_t b, packet.payload())
        os << " " << std::hex << std::setfill('0') << std::setw(2) << int(b);
    os << std::endl;
#endif // ADDP_PACKET_DEBUG

    BOOST_FOREACH(const addp::field& f, packet.fields())
        os << "  " << f;

    switch(packet.type())
    {
        case addp::packet::PT_DISCOVERY_REQUEST:
        {
            os << std::hex << std::setfill('0');

            std::vector<uint8_t> payload = packet.payload();
            for(size_t i=0; i<payload.size(); ++i)
                os << (i ? ":" : " ") << int(payload[i]);
            break;
        }

        default:
            break;
    }

    return os;
}
