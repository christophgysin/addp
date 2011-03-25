#include <sstream>
#include <string>
#include <limits>
#define BOOST_TEST_MODULE type_io_tests
#include <boost/test/included/unit_test.hpp>
#include <boost/numeric/conversion/converter_policies.hpp>
#include <boost/lexical_cast.hpp>
#include <addp/types_io.h>

BOOST_AUTO_TEST_SUITE( mac_io_suite )

BOOST_AUTO_TEST_CASE( mac_address_format )
{
    addp::mac_address mac = {{ 0x01, 0x20, 0x03, 0x4d, 0xfe, 0xef }};
    std::ostringstream os;
    os << mac;
    BOOST_CHECK_EQUAL(os.str(), "01:20:03:4d:fe:ef");
}

BOOST_AUTO_TEST_CASE( mac_address_parse )
{
    addp::mac_address mac;
    std::istringstream is("01:20:03:4d:fe:ef");
    is >> mac;
    BOOST_CHECK_EQUAL(mac[0], 0x01);
    BOOST_CHECK_EQUAL(mac[1], 0x20);
    BOOST_CHECK_EQUAL(mac[2], 0x03);
    BOOST_CHECK_EQUAL(mac[3], 0x4d);
    BOOST_CHECK_EQUAL(mac[4], 0xfe);
    BOOST_CHECK_EQUAL(mac[5], 0xef);
}

BOOST_AUTO_TEST_CASE( mac_address_format_lexical_cast )
{
    addp::mac_address mac = {{ 0x01, 0x20, 0x03, 0x4d, 0xfe, 0xef }};
    std::string str(boost::lexical_cast<std::string>(mac));
    BOOST_CHECK_EQUAL(str, "01:20:03:4d:fe:ef");
}

BOOST_AUTO_TEST_CASE( mac_address_parse_lexical_cast )
{
    addp::mac_address mac = boost::lexical_cast<addp::mac_address>("01:20:03:4d:fe:ef");
    BOOST_CHECK_EQUAL(mac[0], 0x01);
    BOOST_CHECK_EQUAL(mac[1], 0x20);
    BOOST_CHECK_EQUAL(mac[2], 0x03);
    BOOST_CHECK_EQUAL(mac[3], 0x4d);
    BOOST_CHECK_EQUAL(mac[4], 0xfe);
    BOOST_CHECK_EQUAL(mac[5], 0xef);
}

BOOST_AUTO_TEST_CASE( mac_address_parse_single_values )
{
    std::istringstream is("1:2:3:7:8:9");
    addp::mac_address mac;
    is >> mac;
    std::ostringstream os;
    os << mac;
    BOOST_CHECK_EQUAL(os.str(), "01:02:03:07:08:09");
}

BOOST_AUTO_TEST_CASE( mac_address_dont_parse_octal )
{
    std::istringstream is("01:02:03:07:08:09");
    addp::mac_address mac;
    is >> mac;
    std::ostringstream os;
    os << mac;
    BOOST_CHECK_EQUAL(os.str(), "01:02:03:07:08:09");
}

BOOST_AUTO_TEST_CASE( mac_address_parse_hex_to_lower )
{
    std::istringstream is("01:23:45:67:89:AB");
    addp::mac_address mac;
    is >> mac;
    std::ostringstream os;
    os << mac;
    BOOST_CHECK_EQUAL(os.str(), "01:23:45:67:89:ab");
}


BOOST_AUTO_TEST_CASE( mac_address_throw_on_invalid_hex_value )
{
    std::istringstream is("01:23:45:67:89:az");
    addp::mac_address mac;
    BOOST_CHECK_THROW(is >> mac, boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE( mac_address_throw_on_value_overflow )
{
    std::istringstream is("01:23:45:67:89:123");
    addp::mac_address mac;
    BOOST_CHECK_THROW(is >> mac, boost::numeric::positive_overflow);
}

BOOST_AUTO_TEST_CASE( mac_address_throw_on_value_underflow )
{
    std::istringstream is("01:23:45:67:89:-1");
    addp::mac_address mac;
    BOOST_CHECK_THROW(is >> mac, boost::numeric::negative_overflow);
}

BOOST_AUTO_TEST_CASE( mac_address_throw_if_too_short )
{
    std::istringstream is("01:23:45:67:89");
    addp::mac_address mac;
    BOOST_CHECK_THROW(is >> mac, boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_CASE( mac_address_throw_if_too_long )
{
    std::istringstream is("01:23:45:67:89:ab:cd");
    addp::mac_address mac;
    BOOST_CHECK_THROW(is >> mac, boost::bad_lexical_cast);
}

BOOST_AUTO_TEST_SUITE_END()
