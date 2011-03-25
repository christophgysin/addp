#include <sstream>
#include <string>
#include <limits>
#include <boost/numeric/conversion/converter_policies.hpp>

#define BOOST_TEST_MODULE type_io_tests
#include <boost/test/included/unit_test.hpp>

#include <addp/types_io.h>
using namespace addp;

BOOST_AUTO_TEST_SUITE( type_io_suite )

BOOST_AUTO_TEST_CASE( mac_address_parse_single_values )
{
    addp::mac_address mac;
    std::istringstream is;
    std::ostringstream os;

    is.str("1:2:3:7:8:9");
    BOOST_CHECKPOINT("1");
    is >> mac;
    BOOST_CHECKPOINT("2");
    os << mac;
    BOOST_CHECK_EQUAL(os.str(), "01:02:03:07:08:09");
}

BOOST_AUTO_TEST_CASE( mac_address_dont_parse_octal )
{
    addp::mac_address mac;
    std::istringstream is;
    std::ostringstream os;

    is.str("01:02:03:07:08:09");
    BOOST_CHECKPOINT("3");
    is >> mac;
    BOOST_CHECKPOINT("4");
    os << mac;
    BOOST_CHECK_EQUAL(os.str(), "01:02:03:07:08:09");
}

BOOST_AUTO_TEST_CASE( mac_address_parse_hex_to_lower )
{
    addp::mac_address mac;
    std::istringstream is;
    std::ostringstream os;

    is.str("01:23:45:67:89:AB");
    BOOST_CHECKPOINT("5");
    is >> mac;
    BOOST_CHECKPOINT("6");
    os << mac;
    BOOST_CHECK_EQUAL(os.str(), "01:23:45:67:89:ab");
}


BOOST_AUTO_TEST_CASE( mac_address_throw_on_invalid_hex_value )
{
    addp::mac_address mac;
    std::istringstream is;

    is.str("01:23:45:67:89:az");
    BOOST_CHECK_THROW(is >> mac, boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE( mac_address_throw_on_value_overflow )
{
    addp::mac_address mac;
    std::istringstream is;

    is.str("01:23:45:67:89:123");
    BOOST_CHECK_THROW(is >> mac, boost::numeric::positive_overflow);
}

BOOST_AUTO_TEST_CASE( mac_address_throw_on_value_underflow )
{
    addp::mac_address mac;
    std::istringstream is;

    is.str("01:23:45:67:89:-1");
    BOOST_CHECK_THROW(is >> mac, boost::numeric::negative_overflow);
}

BOOST_AUTO_TEST_CASE( mac_address_throw_if_too_short )
{
    addp::mac_address mac;
    std::istringstream is;

    is.str("01:23:45:67:89");
    BOOST_CHECK_THROW(is >> mac, boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE( mac_address_throw_if_too_long )
{
    addp::mac_address mac;
    std::istringstream is;

    is.str("01:23:45:67:89:ab:cd");
    BOOST_CHECK_THROW(is >> mac, boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_SUITE_END()
