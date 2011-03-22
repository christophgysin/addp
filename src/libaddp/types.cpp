#include "types.h"

#include <iomanip>

namespace addp {

std::ostream& operator<<(std::ostream& os, const addp::ip_address& ip_addr)
{
    os << std::dec;

    for(size_t i=0; i<addp::ip_address::len; ++i)
        os << (i ? "." : "") << int(ip_addr.data[i]);

    return os;
}

std::ostream& operator<<(std::ostream& os, const addp::mac_address& mac_addr)
{
    os << std::hex << std::setfill('0');

    for(size_t i=0; i<addp::mac_address::len; ++i)
        os << (i ? ":" : "") << std::setw(2) << int(mac_addr.data[i]);

    return os;
}

std::ostream& operator<<(std::ostream& os, const addp::guid& guid)
{
    os << std::hex << std::setfill('0');

    for(size_t i=0; i<addp::mac_address::len; ++i)
    {
        switch(i)
        {
            case 4:
            case 4+2:
            case 4+2+2:
            case 4+2+2+2:
                os << "-";
        }
        os << std::setw(2) << int(guid.data[i]);
    }

    return os;
}

} // namespace addp
