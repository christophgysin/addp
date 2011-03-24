#ifndef ADDP_TYPES_H
#define ADDP_TYPES_H

#include <stdint.h>
#include <cstddef>

namespace addp {

struct ip_address
{
    static const size_t len = 4;
    uint8_t data[len];
};

struct mac_address
{
    static const size_t len = 6;
    uint8_t data[len];
};

struct guid
{
    static const size_t len = 16;
    uint8_t data[len];
};

} // namespace addp

#endif // ADDP_TYPES_H
