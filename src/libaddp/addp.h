#ifndef ADDP_H
#define ADDP_H

#include <stdint.h>
#include <string>

namespace addp {

static const std::string MCAST_IP_ADDRESS = "224.0.5.128";
static const size_t RESPONSE_TIMEOUT = 2000; // ms
static const size_t RESPONSE_MAX_COUNT = 10;
static const uint16_t UDP_PORT = 2362;

std::string version();

} // namespace addp

#endif // ADDP_H
