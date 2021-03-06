#ifndef ADDP_CONSTANTS_H
#define ADDP_CONSTANTS_H

#include <stdint.h>
#include <string>

#include <addp/types.h>

namespace addp {

static const std::string MCAST_IP_ADDRESS = "224.0.5.128";
static const uint16_t UDP_PORT = 2362;
static const mac_address MAC_ADDR_BROADCAST = {{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }};
static const ssize_t MAX_UDP_MESSAGE_LEN = 4096;
static const std::string DEFAULT_PASSWORD = "dbps";
static const size_t DEFAULT_TIMEOUT = 2000;
static const size_t DEFAULT_MAX_COUNT = 0;

} // namespace addp

#endif // ADDP_CONSTANTS_H
