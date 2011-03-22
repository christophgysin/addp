#ifndef ADDP_TYPES_H
#define ADDP_TYPES_H

#include <stdint.h>
#include <cstring>
#include <ostream>

namespace addp {

struct ip_address
{
    static const size_t len = 4;
    uint8_t data[len];
};
std::ostream& operator<<(std::ostream& os, const addp::ip_address& ip_addr);

struct mac_address
{
    static const size_t len = 6;
    uint8_t data[len];
};
std::ostream& operator<<(std::ostream& os, const addp::mac_address& mac_addr);

struct guid
{
    static const size_t len = 16;
    uint8_t data[len];
};
std::ostream& operator<<(std::ostream& os, const addp::guid& guid);

} // namespace addp

#endif // ADDP_TYPES_H
