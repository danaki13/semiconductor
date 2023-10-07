#define BOOST_TEST_MODULE PNDiode
#include <boost/test/included/unit_test.hpp>
#include "function.h"

BOOST_AUTO_TEST_SUITE(TestPNDiodeIdeal)

BOOST_AUTO_TEST_CASE(test_voltage_1) {
	double tolerance = 1e-5;
	PNDiodeIdeal objPNDiodeIdeal;
	objPNDiodeIdeal.setValues(0.0, 1e-10, 300);

	BOOST_CHECK_EQUAL(objPNDiodeIdeal.calculateOutputCurrent(), 0.0);
	objPNDiodeIdeal.voltage = -1.0;
	BOOST_CHECK_CLOSE(objPNDiodeIdeal.calculateOutputCurrent(), -1.0e-10, tolerance);
	objPNDiodeIdeal.voltage = 1.0;
	BOOST_CHECK_CLOSE(objPNDiodeIdeal.calculateOutputCurrent(), 6.272071e6, tolerance);
}

BOOST_AUTO_TEST_CASE(test_saturation_current_2) {
	double tolerance = 1e-5;
	PNDiodeIdeal objPNDiodeIdeal;
	objPNDiodeIdeal.setValues(-1.0, 1e-8, 300);

	BOOST_CHECK_CLOSE(objPNDiodeIdeal.calculateOutputCurrent(), -1e-8, tolerance);
}

BOOST_AUTO_TEST_CASE(test_temperature_3) {
	double tolerance = 1e-5;
	PNDiodeIdeal objPNDiodeIdeal;
	objPNDiodeIdeal.setValues(-1.0, 1e-10, 200);

	BOOST_CHECK_CLOSE(objPNDiodeIdeal.calculateOutputCurrent(), -1e-10, tolerance);
}

BOOST_AUTO_TEST_SUITE_END()