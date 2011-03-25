#include "field.h"

#include <cstring>
#include <sstream>
#include <iomanip>
#include <boost/foreach.hpp>
#include <boost/format.hpp>

#include <addp/types_io.h>

namespace addp {

field::field(field::field_type type)
{
    _header.type = htons(type);
}

field::field(std::vector<uint8_t>::iterator& iter, const std::vector<uint8_t>::iterator& end)
{
    // header
    copy(iter, iter+sizeof(_header), reinterpret_cast<uint8_t*>(&_header));
    std::advance(iter, sizeof(_header));

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

std::string field::type_str() const
{
    return field_type2str(type());
}

template<>
bool field::value() const
{
    return _payload[0] == BF_TRUE;
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
    if(_payload.size() == t.size())
        copy(_payload.begin(), _payload.end(), t.begin());
    return t;
}

std::string field::value_str() const
{
    std::ostringstream os;

    switch(type())
    {
        case FT_DCHP:
            os << (value<bool>() ? "true" : "false");
            break;

        case FT_HW_TYPE:
        case FT_HW_REV:
        case FT_SERIAL_COUNT:
            os << std::dec << int(value<uint8_t>());
            break;

        case FT_VERSION:
            os << std::dec << value<uint16_t>();

        case FT_PORT:
        case FT_SSL_PORT:
            os << std::dec << value<uint32_t>();
            break;

        case FT_NETWORK:
        case FT_DOMAIN:
        case FT_FIRMWARE:
        case FT_RESULT_MSG:
        case FT_DEVICE_NAME:
            os << value<std::string>();
            break;

        case FT_IP_ADDR:
        case FT_NETMASK:
        case FT_GATEWAY:
        case FT_DNS:
            os << value<ip_address>();
            break;

        case FT_MAC_ADDR:
            os << value<mac_address>();
            break;

        case FT_VENDOR:
            os << value<guid>();
            break;

        case FT_CONF_ERR_CODE:
            os << std::dec << value<config_error>();
            break;

        case FT_ERR_CODE:
            os << std::dec << value<error_code>();
            break;

        case FT_RESULT_FLAG:
            os << std::dec << value<result_flag>();
            break;

        default:
        {
            BOOST_FOREACH(uint8_t b, payload())
                os << " " << std::hex << std::setfill('0') << std::setw(2) << int(b);
            break;
        }
    }
    return os.str();
}

size_t field::size() const
{
    return _payload.size();
}

const std::vector<uint8_t>& field::payload() const
{
    return _payload;
}

std::vector<uint8_t> field::raw() const
{
    std::vector<uint8_t> buffer;
    const uint8_t* headerp = reinterpret_cast<const uint8_t*>(&_header);
    copy(headerp, headerp+sizeof(_header), back_inserter(buffer));
    copy(_payload.begin(), _payload.end(), back_inserter(buffer));

    return buffer;
}

std::string field::field_type2str(field_type type)
{
    switch(type)
    {
        case FT_NONE:           return "None";
        case FT_MAC_ADDR:       return "MAC address";
        case FT_IP_ADDR:        return "IP address";
        case FT_NETMASK:        return "Netmask";
        case FT_NETWORK:        return "Network Name";
        case FT_DOMAIN:         return "Domain";
        case FT_HW_TYPE:        return "Hardware type";
        case FT_HW_REV:         return "Hardware Revision";
        case FT_FIRMWARE:       return "Firmware";
        case FT_RESULT_MSG:     return "Result message";
        case FT_RESULT_FLAG:    return "Result flag";
        case FT_GATEWAY:        return "Gateway IP";
        case FT_CONF_ERR_CODE:  return "Configuration error code";
        case FT_DEVICE_NAME:    return "Device name";
        case FT_PORT:           return "Port";
        case FT_DNS:            return "DNS IP";
        case FT_DCHP:           return "DHCP enabled";
        case FT_ERR_CODE:       return "Error code";
        case FT_SERIAL_COUNT:   return "Serial port count";
        case FT_SSL_PORT:       return "Encrypted port";
        case FT_VERSION:        return "Version ID";
        case FT_VENDOR:         return "Vendor GUID";
    };
    return str(boost::format("Unknown (0x%02x)") % type);
}

std::string field::error_code2str(error_code code)
{
    switch(code)
    {
        case EC_SUCCESS:        return "Success";
        case EC_AUTH:           return "Auth";
        case EC_INVALID:        return "Invalid";
        case EC_SAVE:           return "Save";
    }
    return str(boost::format("Unknown (0x%02x)") % code);
}

std::string field::result_flag2str(result_flag flag)
{
    switch(flag)
    {
        case RF_SUCCESS:        return "Success";
        case RF_ERROR:          return "Error";
    }
    return str(boost::format("Unknown (0x%02x)") % flag);
}

std::string field::config_error2str(config_error error)
{
    switch(error)
    {
        case CE_SUCCESS:        return "SUCCESS";
        case CE_ERROR:          return "Error";
    }
    return str(boost::format("Unknown (0x%02x)") % error);
}

} // namespacce addp
