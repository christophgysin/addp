#ifndef ADDP_TYPES_IO_H
#define ADDP_TYPES_IO_H

#include <ostream>

#include "types.h"

namespace addp {

std::ostream& operator<<(std::ostream& os, const ip_address& ip_addr);
std::ostream& operator<<(std::ostream& os, const mac_address& mac_addr);
std::ostream& operator<<(std::ostream& os, const guid& guid);

} // namespace addp

#endif // ADDP_TYPES_IO_H
