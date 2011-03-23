#ifndef ADDP_FIELD_IO_H
#define ADDP_FIELD_IO_H

#include <ostream>

#include "field.h"

std::ostream& operator<<(std::ostream& os, const addp::field& field);

#endif // ADDP_FIELD_IO_H
