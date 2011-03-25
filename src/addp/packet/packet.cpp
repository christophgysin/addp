#include "packet.h"

#include <cstring>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/numeric/conversion/cast.hpp>

namespace addp {

const char* packet::MAGIC = "DIGI";

packet::packet(packet::packet_type type)
{
    _header.type = htons(type);
}

packet::packet(const uint8_t* data, size_t len)
{
    // header
    memcpy(&_header, data, std::min(sizeof(_header), len));

    // payload
    if(len > sizeof(_header))
    {
        _payload.clear();
        _payload.reserve(len - sizeof(_header));
        copy(data+sizeof(_header), data+len, back_inserter(_payload));
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

std::string packet::type_str() const
{
    return packet_type2str(type());
}

const std::vector<uint8_t>& packet::payload() const
{
    return _payload;
}

template<> void packet::add(const field::bool_flag& data)
{
    _payload.push_back(data);
    _header.size = htons(_payload.size());
}

template<> void packet::add(const std::string& str)
{
    // 1 byte length
    _payload.push_back(boost::numeric_cast<uint8_t>(str.size()));

    const uint8_t* data = reinterpret_cast<const uint8_t*>(str.data());
    copy(data, data+str.size(), back_inserter(_payload));
    _header.size = htons(_payload.size());
}

std::vector<uint8_t> packet::raw() const
{
    std::vector<uint8_t> buffer;
    buffer.reserve(sizeof(_header) + _payload.size());
    const uint8_t* headerp = reinterpret_cast<const uint8_t*>(&_header);
    copy(headerp, headerp+sizeof(_header), back_inserter(buffer));
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
    return _fields;
}

std::string packet::packet_type2str(packet_type type)
{
    switch(type)
    {
        case PT_NONE:                       return "None";
        case PT_DISCOVERY_REQUEST:          return "Discovery Request";
        case PT_DISCOVERY_RESPONSE:         return "Discovery Response";
        case PT_STATIC_NET_CONFIG_REQUEST:  return "Net Config Request";
        case PT_STATIC_NET_CONFIG_RESPONSE:  return "Net Config Response";
        case PT_REBOOT_REQUEST:             return "Reboot Request";
        case PT_REBOOT_RESPONSE:             return "Reboot Response";
        case PT_DHCP_NET_CONFIG_REQUEST:    return "DHCP Net Config Request";
        case PT_DHCP_NET_CONFIG_RESPONSE:    return "DHCP Net Config Response";
    };
    return str(boost::format("unknown (0x%02x)") % type);
}

} // namespace addp
