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

BOOST_AUTO_TEST_SUITE(TestPNDiodeIdealHeader)

BOOST_AUTO_TEST_CASE(test_header_1) {
	PNDiodeIdeal objPNDiodeIdeal;
	objPNDiodeIdeal.writeHeader();
	objPNDiodeIdeal.readHeader();

	BOOST_CHECK_EQUAL(objPNDiodeIdeal.version, "1.0");
}

BOOST_AUTO_TEST_CASE(test_header_2) {
	PNDiodeIdeal objPNDiodeIdeal;
	objPNDiodeIdeal.writeHeader();
	objPNDiodeIdeal.readHeader();

	BOOST_CHECK_EQUAL(objPNDiodeIdeal.type, "xyplot");
}

BOOST_AUTO_TEST_CASE(test_header_3) {
	PNDiodeIdeal objPNDiodeIdeal;
	objPNDiodeIdeal.writeHeader();
	objPNDiodeIdeal.readHeader();

	BOOST_CHECK_EQUAL(objPNDiodeIdeal.datasets[0], "time");
	BOOST_CHECK_EQUAL(objPNDiodeIdeal.datasets[1], "drain OuterVoltage");
	BOOST_CHECK_EQUAL(objPNDiodeIdeal.datasets[2], "drain TotalCurrent");
}

//BOOST_AUTO_TEST_CASE(test_header_4) {
//	PNDiodeIdeal objPNDiodeIdeal;
//	objPNDiodeIdeal.writeHeader();
//	objPNDiodeIdeal.readHeader();
//	objPNDiodeIdeal.printHeader();

	//BOOST_CHECK_EQUAL(objPNDiodeIdeal.type, "xyplot");
//}

BOOST_AUTO_TEST_SUITE_END()

/*BOOST_AUTO_TEST_SUITE(TestPNDiodeIdealData)

BOOST_AUTO_TEST_CASE(test_data_1) {
	PNDiodeIdeal objPNDiodeIdeal;
	objPNDiodeIdeal.writeData();
	objPNDiodeIdeal.readData();

	//BOOST_CHECK_EQUAL(objPNDiodeIdeal.version, "1.0");
}

BOOST_AUTO_TEST_CASE(test_data_2) {
	PNDiodeIdeal objPNDiodeIdeal;
	objPNDiodeIdeal.writeData();
	objPNDiodeIdeal.readData();
	objPNDiodeIdeal.printData();

	//BOOST_CHECK_EQUAL(objPNDiodeIdeal.version, "1.0");
}

BOOST_AUTO_TEST_SUITE_END()*/