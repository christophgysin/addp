#ifndef ADDP_H
#define ADDP_H

#include <stdint.h>
#include <string>

namespace addp {

static const std::string IP_ADDRESS = "224.0.5.128";
static const uint16_t UDP_PORT = 2362;

std::string version();

} // namespace addp

#endif // ADDP_H
