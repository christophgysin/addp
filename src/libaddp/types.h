#ifndef ADDP_TYPES_H
#define ADDP_TYPES_H

#include <stdint.h>
#include <ostream>

namespace addp {

struct ip_address
{
    static const size_t len = 4;
    uint32_t addr;
};

struct mac_address
{
    static const size_t len = 6;
    uint64_t addr;
    mac_address(uint64_t mac_addr) : addr(mac_addr) {};
};

} // namespace addp

std::ostream& operator<<(std::ostream& os, const addp::mac_address& mac_addr);
std::ostream& operator<<(std::ostream& os, const addp::ip_address& ip_addr);

#endif // ADDP_TYPES_H
