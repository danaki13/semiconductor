#define BOOST_TEST_MODULE Configure
#include <boost/test/included/unit_test.hpp>
#include <cmath>
#include "configure.h"
#include "message.h"

#define CFG_FILE_NAME "../test_pn_diode_ideal.cfg"

BOOST_AUTO_TEST_SUITE(TestReadConfigure)

/* Testing the function readCFG() */
BOOST_AUTO_TEST_CASE(test_cfg_A) {
	int flag = 0;
	int test_count = 0, variable_count = 0;
	std::vector<Input> vectorInput;
	flag = readCFG(CFG_FILE_NAME, vectorInput);

	BOOST_CHECK_EQUAL(vectorInput[test_count].simulation, "PN_DIODE_IDEAL");

	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "voltage");
	BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 1.0);
	BOOST_CHECK(std::isnan(vectorInput[test_count].minimum[variable_count]));
	BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -1);

	++variable_count;
	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "saturation_current");
	BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 1e-10);
	BOOST_CHECK(std::isnan(vectorInput[test_count].minimum[variable_count]));
	BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -1);

	++variable_count;
	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "temperature");
	BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 300);
	BOOST_CHECK(std::isnan(vectorInput[test_count].minimum[variable_count]));
	BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -1);

	BOOST_CHECK_EQUAL(vectorInput[test_count].output, "test_pn_diode_ideal_A.plt");

	BOOST_CHECK_EQUAL(flag, 0); /* Function returns 0 in case of correct run. */
}

BOOST_AUTO_TEST_CASE(test_cfg_B) {
	int test_count = 1, variable_count = 0;
	std::vector<Input> vectorInput;
	readCFG(CFG_FILE_NAME, vectorInput);

	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "voltage");
	BOOST_CHECK(std::isnan(vectorInput[test_count].constant[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].minimum[variable_count], -0.5);
	BOOST_CHECK_EQUAL(vectorInput[test_count].maximum[variable_count], 1.0);
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], 100);

	BOOST_CHECK_EQUAL(vectorInput[test_count].output, "test_pn_diode_ideal_B.plt");
}

BOOST_AUTO_TEST_CASE(test_cfg_C) {
	int test_count = 2, variable_count = 0;
	std::vector<Input> vectorInput;
	readCFG(CFG_FILE_NAME, vectorInput);

	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "saturation_current");
	BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 2e-10);
	BOOST_CHECK(std::isnan(vectorInput[test_count].minimum[variable_count]));
	BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -1);

	++variable_count;
	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "temperature");
	BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 320);
	BOOST_CHECK(std::isnan(vectorInput[test_count].minimum[variable_count]));
	BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -1);

	++variable_count;
	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "voltage");
	BOOST_CHECK(std::isnan(vectorInput[test_count].constant[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].minimum[variable_count], -0.5);
	BOOST_CHECK_EQUAL(vectorInput[test_count].maximum[variable_count], 0.5);
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], 10);

	BOOST_CHECK_EQUAL(vectorInput[test_count].output, "test_pn_diode_ideal_C.plt");
}

BOOST_AUTO_TEST_CASE(test_cfg_D) {
	int test_count = 3, variable_count = 0;
	std::vector<Input> vectorInput;
	readCFG(CFG_FILE_NAME, vectorInput);

	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "voltage");
	BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 0.9);
	BOOST_CHECK(std::isnan(vectorInput[test_count].minimum[variable_count]));
	BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -1);

	++variable_count;
	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "saturation_current");
	BOOST_CHECK(std::isnan(vectorInput[test_count].constant[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].minimum[variable_count], 1e-10);
	BOOST_CHECK_EQUAL(vectorInput[test_count].maximum[variable_count], 1e-8);
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], 4);

	++variable_count;
	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "temperature");
	BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 330);
	BOOST_CHECK(std::isnan(vectorInput[test_count].minimum[variable_count]));
	BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -1);

	BOOST_CHECK_EQUAL(vectorInput[test_count].output, "test_pn_diode_ideal_D.plt");
}

BOOST_AUTO_TEST_CASE(test_cfg_E) {
	int test_count = 4, variable_count = 0;
	std::vector<Input> vectorInput;
	readCFG(CFG_FILE_NAME, vectorInput);

	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "voltage");
	BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 0.7);
	BOOST_CHECK(std::isnan(vectorInput[test_count].minimum[variable_count]));
	BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -1);

	++variable_count;
	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "saturation_current");
	BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 1e-8);
	BOOST_CHECK(std::isnan(vectorInput[test_count].minimum[variable_count]));
	BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -1);

	++variable_count;
	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "temperature");
	BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 300);
	BOOST_CHECK(std::isnan(vectorInput[test_count].minimum[variable_count]));
	BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -1);

	BOOST_CHECK_EQUAL(vectorInput[test_count].output, "output.plt");
}

BOOST_AUTO_TEST_CASE(test_cfg_F) {
	int test_count = 5, variable_count = 0;
	std::vector<Input> vectorInput;
	readCFG(CFG_FILE_NAME, vectorInput);

	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "saturation_current");
	BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 1.12e-10);
	BOOST_CHECK(std::isnan(vectorInput[test_count].minimum[variable_count]));
	BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -1);

	++variable_count;
	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "voltage");
	BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 0.7);
	BOOST_CHECK(std::isnan(vectorInput[test_count].minimum[variable_count]));
	BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -1);

	++variable_count;
	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "temperature");
	BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 300);
	BOOST_CHECK(std::isnan(vectorInput[test_count].minimum[variable_count]));
	BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -1);

	BOOST_CHECK_EQUAL(vectorInput[test_count].output, "output.plt");
}

BOOST_AUTO_TEST_CASE(test_cfg_G) {
	int test_count = 6, variable_count = 0;
	std::vector<Input> vectorInput;
	readCFG(CFG_FILE_NAME, vectorInput);

	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "voltage");
	BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 0.8);
	BOOST_CHECK(std::isnan(vectorInput[test_count].minimum[variable_count]));
	BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -1);

	++variable_count;
	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "saturation_current");
	BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 1.0e-8);
	BOOST_CHECK(std::isnan(vectorInput[test_count].minimum[variable_count]));
	BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -1);

	++variable_count;
	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "temperature");
	BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 300);
	BOOST_CHECK(std::isnan(vectorInput[test_count].minimum[variable_count]));
	BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -1);

	BOOST_CHECK_EQUAL(vectorInput[test_count].output, "test_pn_diode_ideal_G.plt");
}

BOOST_AUTO_TEST_CASE(test_cfg_H) {
	int test_count = 7, variable_count = 0;
	std::vector<Input> vectorInput;
	readCFG(CFG_FILE_NAME, vectorInput);

	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "temperature");
	BOOST_CHECK(std::isnan(vectorInput[test_count].constant[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].minimum[variable_count], 290);
	BOOST_CHECK_EQUAL(vectorInput[test_count].maximum[variable_count], 385);
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], 2);

	++variable_count;
	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "voltage");
	BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 0.7);
	BOOST_CHECK(std::isnan(vectorInput[test_count].minimum[variable_count]));
	BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -1);
	
	++variable_count;
	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "saturation_current");
	BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 1.0e-8);
	BOOST_CHECK(std::isnan(vectorInput[test_count].minimum[variable_count]));
	BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -1);
	
	BOOST_CHECK_EQUAL(vectorInput[test_count].output, "output.plt");
}

/* I and J is the same test; that is because test I is not going to be stored, the way I thought to test
 is through the test_count numbering; meaning if I is correctly not read then IJ count should be only +1
 compared to H test_count */
BOOST_AUTO_TEST_CASE(test_cfg_IJ) {
	int test_count = 8, variable_count = 0;
	std::vector<Input> vectorInput;
	readCFG(CFG_FILE_NAME, vectorInput);

	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "voltage");
	BOOST_CHECK(std::isnan(vectorInput[test_count].constant[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].minimum[variable_count], -0.5);
	BOOST_CHECK_EQUAL(vectorInput[test_count].maximum[variable_count], 1.0);
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], 100);
}

BOOST_AUTO_TEST_CASE(test_cfg_K) {
	int test_count = 9, variable_count = 0;
	std::vector<Input> vectorInput;
	readCFG(CFG_FILE_NAME, vectorInput);

	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "voltage");
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], 2);
}

BOOST_AUTO_TEST_CASE(test_cfg_L) {
	int test_count = 10, variable_count = 0;
	std::vector<Input> vectorInput;
	readCFG(CFG_FILE_NAME, vectorInput);

	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "voltage");
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], 2);
}

/* M and N only trigger IGNORE LINE warning messages; tested in warning message output */

BOOST_AUTO_TEST_CASE(test_cfg_O) {
	int test_count = 13, variable_count = 0;
	std::vector<Input> vectorInput;
	readCFG(CFG_FILE_NAME, vectorInput);

	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "voltage");
	BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 1.0);
	BOOST_CHECK(std::isnan(vectorInput[test_count].minimum[variable_count]));
	BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -1);

	++variable_count;
	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "saturation_current");
	BOOST_CHECK(std::isnan(vectorInput[test_count].constant[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].minimum[variable_count], 1e-10);
	BOOST_CHECK_EQUAL(vectorInput[test_count].maximum[variable_count], 1e-8);
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], 123);

	++variable_count;
	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "temperature");
	BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 221);
	BOOST_CHECK(std::isnan(vectorInput[test_count].minimum[variable_count]));
	BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -1);
}

BOOST_AUTO_TEST_CASE(test_cfg_P) {
	int test_count = 14, variable_count = 0;
	std::vector<Input> vectorInput;
	readCFG(CFG_FILE_NAME, vectorInput);

	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "voltage");
	BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 1.0);
	BOOST_CHECK(std::isnan(vectorInput[test_count].minimum[variable_count]));
	BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -1);

	++variable_count;
	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "saturation_current");
	BOOST_CHECK(std::isnan(vectorInput[test_count].constant[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].minimum[variable_count], 1e-11);
	BOOST_CHECK_EQUAL(vectorInput[test_count].maximum[variable_count], 1e-7);
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], 2);

	++variable_count;
	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "temperature");
	BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 222);
	BOOST_CHECK(std::isnan(vectorInput[test_count].minimum[variable_count]));
	BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -1);
}

BOOST_AUTO_TEST_CASE(test_cfg_Q) {
	int test_count = 15, variable_count = 0;
	std::vector<Input> vectorInput;
	readCFG(CFG_FILE_NAME, vectorInput);

	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "voltage");
	BOOST_CHECK(std::isnan(vectorInput[test_count].constant[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].minimum[variable_count], -0.5);
	BOOST_CHECK_EQUAL(vectorInput[test_count].maximum[variable_count], 1.0);
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], 2);
}

BOOST_AUTO_TEST_CASE(test_cfg_R) {
	int flag = 0;
	boost::test_tools::output_test_stream output;
	{
		std::vector<Input> vectorInput;
		cerr_redirect guard(output.rdbuf());
		flag = readCFG("non_existent.cfg", vectorInput);
	}
	BOOST_CHECK(output.is_equal("ERROR: configuration file does not exist!\n"));
	BOOST_CHECK_EQUAL(flag, 2); /* Function returns 2 in case of ERROR. */
}

/* Testing the function updateVector() */
BOOST_AUTO_TEST_CASE(test_updateVector_A) {
	Input vectorTemp;
	std::vector<Input> vectorInput;
	int test_count = 0, variable_count = 0, loop = 3, dummy_flag = 0;

	for(int i = 0; i < loop; i++) {
		vectorTemp.simulation = "PN_DIODE_IDEAL";
		updateVector(vectorTemp.simulation, vectorTemp, vectorInput, dummy_flag);

		test_count = i;
		variable_count = 0;
		BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "voltage");
		BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 0.7);
		BOOST_CHECK(std::isnan(vectorInput[test_count].minimum[variable_count]));
		BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
		BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -1);
		
		++variable_count;
		BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "saturation_current");
		BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 1e-8);
		BOOST_CHECK(std::isnan(vectorInput[test_count].minimum[variable_count]));
		BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
		BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -1);
		
		++variable_count;
		BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "temperature");
		BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 300);
		BOOST_CHECK(std::isnan(vectorInput[test_count].minimum[variable_count]));
		BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
		BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -1);

		BOOST_CHECK_EQUAL(vectorInput[test_count].output, "output.plt");
	}
	BOOST_CHECK_EQUAL(vectorInput.size(), loop);
}

BOOST_AUTO_TEST_CASE(test_updateVector_B) {
	Input vectorTemp;
	std::vector<Input> vectorInput;
	int test_count = 0, variable_count = 0, dummy_flag = 0;

	vectorTemp.simulation = "PN_DIODE_IDEAL";
	vectorTemp.output = "out.plt";

	vectorTemp.variable.push_back("voltage");
	vectorTemp.constant.push_back(1.7);
	vectorTemp.minimum.push_back(1.2);
	vectorTemp.maximum.push_back(2.0);
	vectorTemp.points.push_back(-10);

	vectorTemp.variable.push_back("saturation_current");
	vectorTemp.constant.push_back(1);
	vectorTemp.minimum.push_back(2);
	vectorTemp.maximum.push_back(3);
	vectorTemp.points.push_back(20);

	vectorTemp.variable.push_back("temperature");
	vectorTemp.constant.push_back(std::numeric_limits<double>::quiet_NaN());
	vectorTemp.minimum.push_back(1.23);
	vectorTemp.maximum.push_back(std::numeric_limits<double>::quiet_NaN());
	vectorTemp.points.push_back(10);

	updateVector(vectorTemp.simulation, vectorTemp, vectorInput, dummy_flag);

	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "voltage");
	BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 1.7);
	BOOST_CHECK_EQUAL(vectorInput[test_count].minimum[variable_count], 1.2);
	BOOST_CHECK_EQUAL(vectorInput[test_count].maximum[variable_count], 2.0);
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], -10);
	
	++variable_count;
	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "saturation_current");
	BOOST_CHECK_EQUAL(vectorInput[test_count].constant[variable_count], 1);
	BOOST_CHECK_EQUAL(vectorInput[test_count].minimum[variable_count], 2);
	BOOST_CHECK_EQUAL(vectorInput[test_count].maximum[variable_count], 3);
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], 20);
	
	++variable_count;
	BOOST_CHECK_EQUAL(vectorInput[test_count].variable[variable_count], "temperature");
	BOOST_CHECK(std::isnan(vectorInput[test_count].constant[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].minimum[variable_count], 1.23);
	BOOST_CHECK(std::isnan(vectorInput[test_count].maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorInput[test_count].points[variable_count], 10);

	BOOST_CHECK_EQUAL(vectorInput[test_count].output, "out.plt");
}

BOOST_AUTO_TEST_CASE(test_updateVector_C) {
	Input vectorTemp;
	std::vector<Input> vectorInput;
	int dummy_flag = 0;

	vectorTemp.simulation = "WARNING";
	updateVector(vectorTemp.simulation, vectorTemp, vectorInput, dummy_flag);
	BOOST_CHECK_EQUAL(vectorInput.size(), 0);
}

/* Testing the function initialisePNDiodeIdeal() */
BOOST_AUTO_TEST_CASE(test_initialisePNDiodeIdeal_A) {
	Input vectorTemp;
	bool flag_voltage = true, flag_saturation_current = true, flag_temperature = true;

	initialisePNDiodeIdeal(vectorTemp, flag_voltage, flag_saturation_current, flag_temperature);

	BOOST_CHECK_EQUAL(vectorTemp.variable.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_initialisePNDiodeIdeal_B) {
	Input vectorTemp;
	int variable_count = 0;
	bool flag_voltage = false, flag_saturation_current = true, flag_temperature = true;

	initialisePNDiodeIdeal(vectorTemp, flag_voltage, flag_saturation_current, flag_temperature);

	BOOST_CHECK_EQUAL(vectorTemp.variable.size(), 1);

	BOOST_CHECK_EQUAL(vectorTemp.variable[variable_count], "voltage");
	BOOST_CHECK_EQUAL(vectorTemp.constant[variable_count], 0.7);
	BOOST_CHECK(std::isnan(vectorTemp.minimum[variable_count]));
	BOOST_CHECK(std::isnan(vectorTemp.maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorTemp.points[variable_count], -1);
}

BOOST_AUTO_TEST_CASE(test_initialisePNDiodeIdeal_C) {
	Input vectorTemp;
	int variable_count = 0;
	bool flag_voltage = true, flag_saturation_current = false, flag_temperature = false;

	initialisePNDiodeIdeal(vectorTemp, flag_voltage, flag_saturation_current, flag_temperature);

	BOOST_CHECK_EQUAL(vectorTemp.variable.size(), 2);
	
	BOOST_CHECK_EQUAL(vectorTemp.variable[variable_count], "saturation_current");
	BOOST_CHECK_EQUAL(vectorTemp.constant[variable_count], 1e-8);
	BOOST_CHECK(std::isnan(vectorTemp.minimum[variable_count]));
	BOOST_CHECK(std::isnan(vectorTemp.maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorTemp.points[variable_count], -1);
	
	++variable_count;
	BOOST_CHECK_EQUAL(vectorTemp.variable[variable_count], "temperature");
	BOOST_CHECK_EQUAL(vectorTemp.constant[variable_count], 300);
	BOOST_CHECK(std::isnan(vectorTemp.minimum[variable_count]));
	BOOST_CHECK(std::isnan(vectorTemp.maximum[variable_count]));
	BOOST_CHECK_EQUAL(vectorTemp.points[variable_count], -1);
}

BOOST_AUTO_TEST_SUITE_END()