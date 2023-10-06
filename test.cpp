#define BOOST_TEST_MODULE BoostTest
#include <boost/test/included/unit_test.hpp>
#include "function.h"

BOOST_AUTO_TEST_CASE(test_pn_diode_ideal) {
	double tolerance = 1e-5;
	ObjPNDiodeIdeal.set_values(0.0, 1e-10, 300);

	BOOST_CHECK_EQUAL(ObjPNDiodeIdeal.pn_diode_ideal(), 0.0);
	ObjPNDiodeIdeal.Voltage = -1.0;
	BOOST_CHECK_CLOSE(ObjPNDiodeIdeal.pn_diode_ideal(), -1.0e-10, tolerance);
	ObjPNDiodeIdeal.Voltage = 1.0;
	BOOST_CHECK_CLOSE(ObjPNDiodeIdeal.pn_diode_ideal(), 6.272071e6, tolerance);
	ObjPNDiodeIdeal.Voltage = -1.0;
	ObjPNDiodeIdeal.CurrentSaturartion = 1.0e-8;
	BOOST_CHECK_CLOSE(ObjPNDiodeIdeal.pn_diode_ideal(), -1e-8, tolerance);
	ObjPNDiodeIdeal.Temperature = 200;
	ObjPNDiodeIdeal.CurrentSaturartion = 1.0e-10;
	BOOST_CHECK_CLOSE(ObjPNDiodeIdeal.pn_diode_ideal(), -1e-10, tolerance);
}

//BOOST_AUTO_TEST_CASE(test_pn_diode_ideal_current_temperature) {
//	double tolerance = 1e-5;

//	BOOST_CHECK_CLOSE(pn_diode_ideal(-1.0, 1e-8), -1e-8, tolerance);
//	BOOST_CHECK_CLOSE(pn_diode_ideal(-1.0, 1e-10, 200), -1e-10, tolerance);
//}