#include "types.h"
#include <iomanip>

std::ostream& operator<<(std::ostream& os, const addp::mac_address& mac_addr)
{
    os << std::hex << std::setfill('0');

    for(size_t i=0; i<addp::mac_address::len; ++i)
        os << (i ? ":" : "") << std::setw(2) << int(mac_addr.addr >> i & 0xff);

    return os;
}

std::ostream& operator<<(std::ostream& os, const addp::ip_address& ip_addr)
{
    os << std::dec;

    for(size_t i=0; i<addp::ip_address::len; ++i)
        os << (i ? "." : "") << int(ip_addr.addr >> i*8 & 0xff);

    return os;
}
