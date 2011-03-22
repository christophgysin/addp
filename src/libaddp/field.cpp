#include "field.h"

#include <cstring>

namespace addp {

field::field()
{
}

field::field(field::field_type type)
{
    _header.type = htons(type);
}

field::field(uint8_t* data, size_t len)
{
    // header
    memcpy(&_header, data, std::min(sizeof(field_header), len));

    // payload
    if(len > sizeof(field_header))
    {
        _payload.clear();
        _payload.reserve(len - sizeof(field_type));
        copy(data+sizeof(field_type), data+len, back_inserter(_payload));
    }
}

field::field_type field::type() const
{
    return static_cast<field::field_type>(ntohs(_header.type));
}

size_t field::size() const
{
    return _payload.size();
}

const std::vector<uint8_t>& field::payload() const
{
    return _payload;
}

void field::add_raw(const uint8_t* data, size_t len)
{
    copy(data, data+len, back_inserter(_payload));
    _header.size = htons(_payload.size());
}

std::vector<uint8_t> field::raw() const
{
    std::vector<uint8_t> buffer;
    const uint8_t* headerp = reinterpret_cast<const uint8_t*>(&_header);
    copy(headerp, headerp+sizeof(field_header), back_inserter(buffer));
    copy(_payload.begin(), _payload.end(), back_inserter(buffer));

    return buffer;
}

std::string addp::field::field_type2str(field_type type)
{
    switch(type)
    {
        case FT_NONE:
            return "None";
        case FT_MAC_ADDR:
            return "6 byte MAC address";
        case FT_IP_ADDR:
            return "4 byte IP address";
        case FT_NETMASK:
            return "4 byte netmask";
        case FT_NETWORK:
            return "string network Name";
        case FT_DOMAIN:
            return "domain";
        case FT_HW_TYPE:
            return "hardware type";
        case FT_HW_REV:
            return "hardware Revision";
        case FT_FIRMWARE:
            return "string firmware";
        case FT_RESULT_MSG:
            return "string result message";
        case FT_RESULT_FLAG:
            return "1 byte result flag";
        case FT_GATEWAY:
            return "4 byte gateway IP";
        case FT_CONF_ERR_CODE:
            return "2 byte configuration error code";
        case FT_DEVICE_NAME:
            return "string device name";
        case FT_PORT:
            return "4 byte port";
        case FT_DNS:
            return "4 byte DNS IP";
        case FT_DCHP:
            return "bool DHCP enabled";
        case FT_ERR_CODE:
            return "1 byte error code";
        case FT_SERIAL_COUNT:
            return "1 byte serial port count";
        case FT_SSL_PORT:
            return "4 byte encryFTed port";
        case FT_VERSION:
            return "version ID";
        case FT_VENDOR:
            return "vendor GUID";
    };
    return "Unknown";
}

template<typename T>
T field::value()
{
    T t;
    return t;
}

} // namespacce addp

std::ostream& operator<<(std::ostream& os, const addp::field& field)
{
    os << addp::field::field_type2str(field.type());

    return os;
}
