#include "field_io.h"

std::ostream& operator<<(std::ostream& os, const addp::field& field)
{
#ifdef ADDP_FIELD_DEBUG
    os << std::endl;
    os << "field raw():" << std::endl;
    BOOST_FOREACH(uint8_t b, field.raw())
        os << " " << std::hex << std::setfill('0') << std::setw(2) << int(b);
    os << std::endl;
    os << "field payload():";
    BOOST_FOREACH(uint8_t b, field.payload())
        os << " " << std::hex << std::setfill('0') << std::setw(2) << int(b);
    os << std::endl;
#endif // ADDP_FIELD_DEBUG

    if(field.type() == addp::field::FT_NONE)
        return os;

    return os << field.type_str() << " = " << field.value_str() << std::endl;
}
