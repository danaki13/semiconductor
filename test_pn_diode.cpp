#define BOOST_TEST_MODULE PNDiode
#include <boost/test/included/unit_test.hpp>
#include <boost/test/tools/output_test_stream.hpp>
#include "function.h"

#define TOLERANCE 1e-5

/*struct cout_redirect {
	cout_redirect(std::streambuf *new_buffer) 
		: old(std::cout.rdbuf(new_buffer))
	{}

	~cout_redirect() {
		std::cout.rdbuf(old);
	}

private:
	std::streambuf *old;
};*/

BOOST_AUTO_TEST_SUITE(TestPNDiodeIdeal)

BOOST_AUTO_TEST_CASE(test_voltage_1) {
	PNDiodeIdeal objPNDiodeIdeal;
	objPNDiodeIdeal.setValues(0.0, 1e-10, 300);

	BOOST_CHECK_EQUAL(objPNDiodeIdeal.calculateOutputCurrent(), 0.0);
	objPNDiodeIdeal.voltage = -1.0;
	BOOST_CHECK_CLOSE(objPNDiodeIdeal.calculateOutputCurrent(), -1.0e-10, TOLERANCE);
	objPNDiodeIdeal.voltage = 1.0;
	BOOST_CHECK_CLOSE(objPNDiodeIdeal.calculateOutputCurrent(), 6.272071e6, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(test_saturation_current_2) {
	PNDiodeIdeal objPNDiodeIdeal;
	objPNDiodeIdeal.setValues(-1.0, 1e-8, 300);

	BOOST_CHECK_CLOSE(objPNDiodeIdeal.calculateOutputCurrent(), -1e-8, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(test_temperature_3) {
	PNDiodeIdeal objPNDiodeIdeal;
	objPNDiodeIdeal.setValues(-1.0, 1e-10, 200);

	BOOST_CHECK_CLOSE(objPNDiodeIdeal.calculateOutputCurrent(), -1e-10, TOLERANCE);
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

	BOOST_CHECK_EQUAL(objPNDiodeIdeal.datasets[0], "voltage");
	BOOST_CHECK_EQUAL(objPNDiodeIdeal.datasets[1], "saturation current");
	BOOST_CHECK_EQUAL(objPNDiodeIdeal.datasets[2], "temperature");
	BOOST_CHECK_EQUAL(objPNDiodeIdeal.datasets[3], "output current");
}

/*BOOST_AUTO_TEST_CASE(test_header_4) {
	PNDiodeIdeal objPNDiodeIdeal;
	objPNDiodeIdeal.writeHeader();
	objPNDiodeIdeal.readHeader();

	boost::test_tools::output_test_stream output;
	{
		cout_redirect guard(output.rdbuf());
		std::cout << "Version: ";
	}
	BOOST_CHECK(output.is_equal("\\b\\w+Version\\b"));
}*/

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestPNDiodeIdealData)

BOOST_AUTO_TEST_CASE(test_data_1) {
	PNDiodeIdeal objPNDiodeIdeal;
	objPNDiodeIdeal.setValues(1.0, 1e-10, 300);
	objPNDiodeIdeal.calculateOutputCurrent();
	objPNDiodeIdeal.writeData();
	objPNDiodeIdeal.setValues(0.0, 1e-8, 100);
	objPNDiodeIdeal.readData();

	BOOST_CHECK_EQUAL(objPNDiodeIdeal.data[0][0], 1.0);
	BOOST_CHECK_EQUAL(objPNDiodeIdeal.data[0][1], 1e-10);
	BOOST_CHECK_EQUAL(objPNDiodeIdeal.data[0][2], 300.0);
	BOOST_CHECK_CLOSE(objPNDiodeIdeal.data[0][3], 6.272071e6, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(test_data_2) {
	PNDiodeIdeal objPNDiodeIdeal;
	objPNDiodeIdeal.writeHeader();
	for(int i = 0; i < 10; i++) {
		objPNDiodeIdeal.setValues(0.1*i, 1e-10, 300);
		objPNDiodeIdeal.calculateOutputCurrent();
		objPNDiodeIdeal.writeData();
	}
	objPNDiodeIdeal.readData();

	BOOST_CHECK_CLOSE(objPNDiodeIdeal.data[4][3], 5.235574e-04, TOLERANCE);
	BOOST_CHECK_EQUAL(objPNDiodeIdeal.data[5][2], 300.0);
}

// TEST printing

BOOST_AUTO_TEST_SUITE_END()