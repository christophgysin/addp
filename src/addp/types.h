#ifndef ADDP_TYPES_H
#define ADDP_TYPES_H

#include <stdint.h>
#include <boost/array.hpp>

namespace addp {

typedef boost::array<uint8_t, 4> ip_address;
typedef boost::array<uint8_t, 6> mac_address;
typedef boost::array<uint8_t, 16> guid;

} // namespace addp

#endif // ADDP_TYPES_H
