#include "field.h"

#include <cstring>
#include <iostream>
#include <iomanip>
#include <boost/foreach.hpp>
#include <boost/format.hpp>

namespace addp {

field::field(field::field_type type)
{
    _header.type = htons(type);
}

field::field(std::vector<uint8_t>::iterator& iter, const std::vector<uint8_t>::iterator& end)
{
    // header
    copy(iter, iter+sizeof(field_header), reinterpret_cast<uint8_t*>(&_header));
    std::advance(iter, sizeof(field_header));

    // payload
    _payload.clear();
    copy(iter, iter+_header.size, back_inserter(_payload));
    std::advance(iter, _header.size);
}

bool field::check() const
{
    if(_payload.size() != _header.size)
        return false;

    return true;
}

field::field_type field::type() const
{
    return static_cast<field::field_type>(_header.type);
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
            return "none";
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
            return "4 byte encrypted port";
        case FT_VERSION:
            return "version ID";
        case FT_VENDOR:
            return "vendor GUID";
    };
    return str(boost::format("unknown (0x%02x)") % type);
}

template<>
std::string field::value() const
{
    std::string s;
    copy(_payload.begin(), _payload.end(), back_inserter(s));
    return s;
}

template<typename T>
T field::value() const
{
    T t;

    return t;
}

} // namespacce addp

std::ostream& operator<<(std::ostream& os, const addp::field& field)
{
#ifdef ADDP_FIELD_DEBUG
    os << std::endl;
    os << "field raw():" << std::endl;
    BOOST_FOREACH(uint8_t b, field.raw())
        os << " " << std::hex << std::setfill('0') << std::setw(2) << int(b);
    os << std::endl;
    os << "field payload():";
    BOOST_FOREACH(uint8_t b, field.payload())
        os << " " << std::hex << std::setfill('0') << std::setw(2) << int(b);
    os << std::endl;
#endif // ADDP_FIELD_DEBUG

    os << addp::field::field_type2str(field.type()) << " = ";

    switch(field.type())
    {
        case addp::field::FT_NONE:
            break;

        case addp::field::FT_MAC_ADDR:
            //os << field.value<mac_address>();
            os << "xx:xx:xx:xx:xx:xx";
            break;

        case addp::field::FT_IP_ADDR:
        case addp::field::FT_NETMASK:
        case addp::field::FT_GATEWAY:
        case addp::field::FT_DNS:
            //os << field.value<ip_address>();
            os << "xxx.xxx.xxx.xxx";
            break;

        case addp::field::FT_NETWORK:
        case addp::field::FT_DOMAIN:
        case addp::field::FT_FIRMWARE:
        case addp::field::FT_RESULT_MSG:
        case addp::field::FT_DEVICE_NAME:
            os << field.value<std::string>();
            break;

        case addp::field::FT_HW_TYPE:
        case addp::field::FT_HW_REV:
        case addp::field::FT_PORT:
        case addp::field::FT_SSL_PORT:
            //os << field.value<int>();
            os << "int";
            break;

        case addp::field::FT_RESULT_FLAG:
        case addp::field::FT_CONF_ERR_CODE:
        case addp::field::FT_DCHP:
        case addp::field::FT_ERR_CODE:
        case addp::field::FT_SERIAL_COUNT:
        case addp::field::FT_VERSION:
        case addp::field::FT_VENDOR:
            //os << field.value<int>();
            os << "custom";
            break;

        default:
        {
            BOOST_FOREACH(uint8_t b, field.payload())
                os << " " << std::hex << std::setfill('0') << std::setw(2) << int(b);
            break;
        }
    }
    return os << std::endl;
}
