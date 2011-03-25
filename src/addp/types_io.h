#ifndef ADDP_TYPES_IO_H
#define ADDP_TYPES_IO_H

#include <ostream>
#include <istream>

#include <addp/types.h>

namespace std {

std::ostream& operator<<(std::ostream& os, const addp::ip_address& ip_addr);
std::istream& operator>>(std::istream& is, addp::ip_address& ip_addr);
std::ostream& operator<<(std::ostream& os, const addp::mac_address& mac_addr);
std::istream& operator>>(std::istream& is, addp::mac_address& mac_addr);
std::ostream& operator<<(std::ostream& os, const addp::guid& guid);
//std::istream& operator>>(std::istream& is, addp::guid& guid);

} // namespace std

#endif // ADDP_TYPES_IO_H
