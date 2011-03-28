#ifndef ADDP_PACKET_FIELD_IO_H
#define ADDP_PACKET_FIELD_IO_H

#include <ostream>

#include <addp/packet/field.h>

namespace addp {

std::ostream& operator<<(std::ostream& os, const field& field);

} // namespace addp

#endif // ADDP_PACKET_FIELD_IO_H
