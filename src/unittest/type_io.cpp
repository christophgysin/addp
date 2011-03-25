#include <sstream>
#include <string>

#define BOOST_TEST_MODULE type_io_tests
#include <boost/test/included/unit_test.hpp>

#include <addp/types_io.h>
using namespace addp;

BOOST_AUTO_TEST_SUITE( type_io_suite )

BOOST_AUTO_TEST_CASE( mac_address )
{
    addp::mac_address mac;

    std::ostringstream os;
    os << mac;
    BOOST_CHECK_EQUAL(os.str(), "00:00:00:00:00:00");

    std::string mac_str("01:23:45:67:89:AB");
    std::istringstream is(mac_str);
    is >> mac;
    os.clear();
    os << mac;
    BOOST_CHECK_EQUAL(mac_str, os.str());

    is.str("01:23:45:67:89:AZ");
    BOOST_CHECK_THROW(is >> mac, std::bad_cast);
}

BOOST_AUTO_TEST_CASE( ip_address )
{
    addp::ip_address ip;

    std::ostringstream os;
    os << ip;
    BOOST_CHECK_EQUAL(os.str(), "0.0.0.0");

    std::string ip_str("1.2.3.4");
    std::istringstream is(ip_str);
    is >> ip;
    os.clear();
    os << ip;
    BOOST_CHECK_EQUAL(ip_str, os.str());

    is.str("1.2.3.a");
    BOOST_CHECK_THROW(is >> ip, std::bad_cast);
}

BOOST_AUTO_TEST_SUITE_END()
