#include "field.h"

#include <cstring>
#include <iostream>
#include <iomanip>
#include <boost/foreach.hpp>
#include <boost/format.hpp>

#include "types.h"

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
            return "None";
        case FT_MAC_ADDR:
            return "MAC address";
        case FT_IP_ADDR:
            return "IP address";
        case FT_NETMASK:
            return "Netmask";
        case FT_NETWORK:
            return "Network Name";
        case FT_DOMAIN:
            return "Domain";
        case FT_HW_TYPE:
            return "Hardware type";
        case FT_HW_REV:
            return "Hardware Revision";
        case FT_FIRMWARE:
            return "Firmware";
        case FT_RESULT_MSG:
            return "Result message";
        case FT_RESULT_FLAG:
            return "Result flag";
        case FT_GATEWAY:
            return "Gateway IP";
        case FT_CONF_ERR_CODE:
            return "Configuration error code";
        case FT_DEVICE_NAME:
            return "Device name";
        case FT_PORT:
            return "Port";
        case FT_DNS:
            return "DNS IP";
        case FT_DCHP:
            return "DHCP enabled";
        case FT_ERR_CODE:
            return "Error code";
        case FT_SERIAL_COUNT:
            return "Serial port count";
        case FT_SSL_PORT:
            return "Encrypted port";
        case FT_VERSION:
            return "Version ID";
        case FT_VENDOR:
            return "Vendor GUID";
    };
    return str(boost::format("Unknown (0x%02x)") % type);
}

std::string addp::field::error_code2str(error_code code)
{
    switch(code)
    {
        case EC_SUCCESS:
            return "Success";
        case EC_AUTH:
            return "Auth";
        case EC_INVALID:
            return "Invalid";
        case EC_SAVE:
            return "Save";
    }
    return str(boost::format("Unknown (0x%02x)") % code);
}

std::string addp::field::result_flag2str(result_flag flag)
{
    switch(flag)
    {
        case RF_SUCCESS:
            return "Success";
        case RF_ERROR:
            return "Error";
    }
    return str(boost::format("Unknown (0x%02x)") % flag);
}

std::string addp::field::config_error2str(config_error error)
{
    switch(error)
    {
        case CE_SUCCESS:
            return "SUCCESS";
        case CE_ERROR:
            return "Error"; // Digi in different subnet than sender
    }
    return str(boost::format("Unknown (0x%02x)") % error);
}

template<>
bool field::value() const
{
    return _payload[0] == 0x00;
}

template<>
uint8_t field::value() const
{
    return _payload[0];
}

template<>
uint16_t field::value() const
{
    return ntohs(*reinterpret_cast<const uint16_t*>(_payload.data()));
}

template<>
uint32_t field::value() const
{
    return ntohl(*reinterpret_cast<const uint32_t*>(_payload.data()));
}

template<>
std::string field::value() const
{
    std::string s;
    copy(_payload.begin(), _payload.end(), back_inserter(s));
    return s;
}

template<>
field::config_error field::value() const
{
    return static_cast<field::config_error>(value<uint16_t>());
}

template<>
field::error_code field::value() const
{
    return static_cast<field::error_code>(value<uint8_t>());
}

template<>
field::result_flag field::value() const
{
    return static_cast<field::result_flag>(value<uint8_t>());
}

template<typename T>
T field::value() const
{
    T t;
    if(_payload.size() == T::len)
        copy(_payload.begin(), _payload.end(), reinterpret_cast<uint8_t*>(&t.data));
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

    if(field.type() == addp::field::FT_NONE)
        return os;

    os << addp::field::field_type2str(field.type()) << " = ";

    switch(field.type())
    {
        case addp::field::FT_DCHP:
            os << (field.value<bool>() ? "true" : "false");
            break;

        case addp::field::FT_HW_TYPE:
        case addp::field::FT_HW_REV:
        case addp::field::FT_SERIAL_COUNT:
            os << std::dec << int(field.value<uint8_t>());
            break;

        case addp::field::FT_VERSION:
            os << std::dec << field.value<uint16_t>();

        case addp::field::FT_PORT:
        case addp::field::FT_SSL_PORT:
            os << std::dec << field.value<uint32_t>();
            break;

        case addp::field::FT_NETWORK:
        case addp::field::FT_DOMAIN:
        case addp::field::FT_FIRMWARE:
        case addp::field::FT_RESULT_MSG:
        case addp::field::FT_DEVICE_NAME:
            os << field.value<std::string>();
            break;

        case addp::field::FT_IP_ADDR:
        case addp::field::FT_NETMASK:
        case addp::field::FT_GATEWAY:
        case addp::field::FT_DNS:
            os << field.value<addp::ip_address>();
            break;

        case addp::field::FT_MAC_ADDR:
            os << field.value<addp::mac_address>();
            break;

        case addp::field::FT_VENDOR:
            os << field.value<addp::guid>();
            break;

        case addp::field::FT_CONF_ERR_CODE:
            os << std::dec << field.value<addp::field::config_error>();
            break;

        case addp::field::FT_ERR_CODE:
            os << std::dec << field.value<addp::field::error_code>();
            break;

        case addp::field::FT_RESULT_FLAG:
            os << std::dec << field.value<addp::field::result_flag>();
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
