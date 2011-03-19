#include <stdint.h>
#include <string>
#include <vector>

namespace addp {

static const std::string IP_ADDRESS = "224.0.5.128";
static const uint16_t UDP_PORT = 2362;

std::string version();

std::vector<uint8_t> discovery_request(const uint64_t mac_addr = 0xffffffffffff);

} // namespace addp
