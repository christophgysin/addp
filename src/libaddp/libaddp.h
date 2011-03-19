#include <stdint.h>
#include <cstring>

namespace addp {

static const char* MAGIC = "DIGI";

/*
 * ADDP packet format
 *
 * +--------------+
 * | magic        |                  +-------------+
 * +--------------+                / | field type  |
 * | packet type  |               /  +-------------+
 * +--------------+    +-------+ /   | field size  |
 * | payload size |  / | field |     +-------------+
 * +--------------+ /  +-------+ \   |             |
 * |              |    | field |  \  | field value |
 * | payload      |    +-------+   \ |             |
 * |              |    | field |     +-------------+
 * +--------------+ \  +-------+
 *                   \ | ...   |
 *                     +-------+
 */

struct packet_header {
    char magic[4];
    uint16_t packet_type;
    uint16_t payload_size;
    uint8_t payload[0];

    packet_header() { strncpy(magic, MAGIC, 4); }
};

struct field {
    uint8_t type;
    uint8_t size;
    uint8_t value[0];
};

enum packet_type {
    PT_NONE = 0x00,
    PT_DISCOVERY_REQUEST,
    PT_DISCOVERY_RESPONSE,
    PT_STATIC_NET_CONFIG_REQUEST,
    PT_STATIC_NET_CONFIG_REPONSE,
    PT_REBOOT_REQUEST,
    PT_REBOOT_REPONSE,
    PT_DHCP_NET_CONFIG_REQUEST,
    PT_DHCP_NET_CONFIG_REPONSE,
};

enum field_type {
    FT_NONE = 0x00,
    FT_MAC_ADDR,      // 6 byte MAC address
    FT_IP_ADDR,       // 4 byte IP address
    FT_NETMASK,       // 4 byte netmask
    FT_NETWORK,       // string network Name
    FT_DOMAIN,        // domain
    FT_HW_TYPE,       // hardware type
    FT_HW_REV,        // hardware Revision
    FT_FIRMWARE,      // string firmware
    FT_RESULT_MSG,    // string result message
    FT_RESULT_FLAG,   // 1 byte result flag
    FT_GATEWAY,       // 4 byte gateway IP
    FT_CONF_ERR_CODE, // 2 byte configuration error code
    FT_DEVICE_NAME,   // string device name
    FT_PORT,          // 4 byte port
    FT_DNS,           // 4 byte DNS IP
    FT_DCHP,          // bool DHCP enabled
    FT_ERR_CODE,      // 1 byte error code
    FT_SERIAL_COUNT,  // 1 byte serial port count
    FT_SSL_PORT,      // 4 byte encrypted port
    FT_VERSION,       // version ID
    FT_VENDOR,        // vendor GUID
};

// FT_ERR_CODE
enum error_code {
    EC_SUCCESS = 0x00,
    EC_AUTH,
    EC_INVALID = 0x03,
    EC_SAVE = 0x06,
};

// FT_RESULT_FLAG
enum result_flag {
    RF_SUCCESS = 0x00,
    RF_ERROR = 0xff,
};

// FT_CONF_ERR_CODE
enum config_error {
    CE_SUCCESS = 0x00,
    CE_ERROR, // Digi in different subnet than sender
};

// FT_DCHP
enum bool_flag {
    BF_FALSE = 0x00,
    BF_TRUE = 0x01,
};

} // namespace addp
