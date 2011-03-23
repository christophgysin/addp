#ifndef ADDP_PACKET_IO_H
#define ADDP_PACKET_IO_H

#include <ostream>

#include "packet.h"

std::ostream& operator<<(std::ostream& os, const addp::packet& packet);

#endif // ADDP_PACKET_IO_H
