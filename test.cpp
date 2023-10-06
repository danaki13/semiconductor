#define BOOST_TEST_MODULE BoostTest
#include <boost/test/included/unit_test.hpp>
#include "function.h"

BOOST_AUTO_TEST_CASE(test_pn_diode_ideal) {
	double tolerance = 1e-5;

	BOOST_CHECK_EQUAL(pn_diode_ideal(0.0), 0.0);
	BOOST_CHECK_CLOSE(pn_diode_ideal(-1.0), -1.0e-10, tolerance);
	BOOST_CHECK_CLOSE(pn_diode_ideal(1.0), 6.272071e6, tolerance);
}