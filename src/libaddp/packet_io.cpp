#include "packet_io.h"
#include "field_io.h"

#include <iomanip>

std::ostream& operator<<(std::ostream& os, const addp::packet& packet)
{
#ifdef ADDP_PACKET_DEBUG
    os << std::endl;
    os << "packet raw():" << std::endl;
    BOOST_FOREACH(uint8_t b, packet.raw())
        os << " " << std::hex << std::setfill('0') << std::setw(2) << int(b);
    os << std::endl << std::endl;
    os << "packet payload():";
    BOOST_FOREACH(uint8_t b, packet.payload())
        os << " " << std::hex << std::setfill('0') << std::setw(2) << int(b);
    os << std::endl;
#endif // ADDP_PACKET_DEBUG

    os << packet.type_str() << std::endl;

    BOOST_FOREACH(const addp::field& f, packet.fields())
        if(f.type() != addp::field::FT_NONE)
            os << "  " << f;

    switch(packet.type())
    {
        case addp::packet::PT_DISCOVERY_REQUEST:
        {
            os << std::hex << std::setfill('0');

            std::vector<uint8_t> payload = packet.payload();
            for(size_t i=0; i<payload.size(); ++i)
                os << (i ? ":" : " ") << int(payload[i]);
            break;
        }

        default:
            break;
    }

    return os;
}
