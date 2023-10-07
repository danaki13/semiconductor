#define BOOST_TEST_MODULE BoostTest
#include <boost/test/included/unit_test.hpp>
#include "function.h"

BOOST_AUTO_TEST_CASE(test_pn_diode_ideal) {
	double tolerance = 1e-5;
	PNDiodeIdeal objPNDiodeIdeal;
	objPNDiodeIdeal.setValues(0.0, 1e-10, 300);

	BOOST_CHECK_EQUAL(objPNDiodeIdeal.calculateOutputCurrent(), 0.0);
	objPNDiodeIdeal.voltage = -1.0;
	BOOST_CHECK_CLOSE(objPNDiodeIdeal.calculateOutputCurrent(), -1.0e-10, tolerance);
	objPNDiodeIdeal.voltage = 1.0;
	BOOST_CHECK_CLOSE(objPNDiodeIdeal.calculateOutputCurrent(), 6.272071e6, tolerance);
	objPNDiodeIdeal.voltage = -1.0;
	objPNDiodeIdeal.saturation_current = 1.0e-8;
	BOOST_CHECK_CLOSE(objPNDiodeIdeal.calculateOutputCurrent(), -1e-8, tolerance);
	objPNDiodeIdeal.temperature = 200;
	objPNDiodeIdeal.saturation_current = 1.0e-10;
	BOOST_CHECK_CLOSE(objPNDiodeIdeal.calculateOutputCurrent(), -1e-10, tolerance);
}