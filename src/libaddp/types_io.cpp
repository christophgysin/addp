#include "types_io.h"

#include <iomanip>

namespace addp {

std::ostream& operator<<(std::ostream& os, const ip_address& ip_addr)
{
    os << std::dec;

    for(size_t i=0; i<ip_address::len; ++i)
        os << (i ? "." : "") << int(ip_addr.data[i]);

    return os;
}

std::ostream& operator<<(std::ostream& os, const mac_address& mac_addr)
{
    os << std::hex << std::setfill('0');

    for(size_t i=0; i<mac_address::len; ++i)
        os << (i ? ":" : "") << std::setw(2) << int(mac_addr.data[i]);

    return os;
}

std::ostream& operator<<(std::ostream& os, const guid& guid)
{
    os << std::hex << std::setfill('0');

    for(size_t i=0; i<mac_address::len; ++i)
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
