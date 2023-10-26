#define BOOST_TEST_MODULE Configure
#include <boost/test/included/unit_test.hpp>
#include <cmath>
#include "configure.h"
#include "message.h"

BOOST_AUTO_TEST_SUITE(TestReadConfigure)

BOOST_AUTO_TEST_CASE(test_cfg_1) {
	int flag = 0;
	boost::test_tools::output_test_stream output;
	{
		std::vector<Input> vectorInput;
		cout_redirect guard(output.rdbuf());
		flag = readCFG("non_existent.cfg", vectorInput);
	}
	BOOST_CHECK(output.is_equal("ERROR: configuration file does not exist!\n"));
	BOOST_CHECK_EQUAL(flag, 2); /* Function returns two in case of ERROR. */
}

BOOST_AUTO_TEST_CASE(test_cfg_2) {
	int flag = 0;
	std::vector<Input> vectorInput;
	readCFG("pn_diode_ideal.cfg", vectorInput);

	/* Simulation types */
	BOOST_CHECK_EQUAL(vectorInput[0].simulation, "PN_DIODE_IDEAL");
	BOOST_CHECK_EQUAL(vectorInput[1].simulation, "WARNING_NOT_INT");
	BOOST_CHECK_EQUAL(vectorInput[2].simulation, "WARNING_NO_OUTPUT");
	BOOST_CHECK_EQUAL(vectorInput[3].simulation, "WARNING_NO_POINTS");
	BOOST_CHECK_EQUAL(vectorInput[4].simulation, "WARNING_POINTS_0");
	BOOST_CHECK_EQUAL(vectorInput[5].simulation, "WARNING_POINTS_NEGATIVE");
	BOOST_CHECK_EQUAL(vectorInput[6].simulation, "WARNING_LEFT_IS_LARGER");
	BOOST_CHECK_EQUAL(vectorInput.size(), 8);
	BOOST_CHECK_EQUAL(flag, 0); /* Function returns two in case of correct run. */
}

BOOST_AUTO_TEST_CASE(test_cfg_3) {
	std::vector<Input> vectorInput;
	readCFG("pn_diode_ideal.cfg", vectorInput);

	/* NAME of the variable */
	BOOST_CHECK_EQUAL(vectorInput[0].variable[0], "voltage");
	/* If variable has two VALUES than it will expand to MIN/MAX
	and should be followed by POINTS */
	BOOST_CHECK(std::isnan(vectorInput[0].constant[0]));
	BOOST_CHECK_EQUAL(vectorInput[0].minimum[0], -0.5);
	BOOST_CHECK_EQUAL(vectorInput[0].maximum[0], 1.0);
	BOOST_CHECK_EQUAL(vectorInput[0].points[0], 100);
	/* If after variable there is a single value then it is a CONSTANT */
	BOOST_CHECK_EQUAL(vectorInput[0].variable[1], "saturation_current");
	BOOST_CHECK_EQUAL(vectorInput[0].constant[1], 1e-10);
	BOOST_CHECK(std::isnan(vectorInput[0].minimum[1]));
	BOOST_CHECK(std::isnan(vectorInput[0].maximum[1]));
	BOOST_CHECK_EQUAL(vectorInput[0].points[1], -1);
	BOOST_CHECK_EQUAL(vectorInput[0].variable[2], "temperature");
	BOOST_CHECK_EQUAL(vectorInput[0].constant[2], 300.0);
	/* Name of the file where the result is saved */
	BOOST_CHECK_EQUAL(vectorInput[0].output, "pn_diode_ideal.plt");
}

BOOST_AUTO_TEST_CASE(test_cfg_4) {
	int flag = 0;
	boost::test_tools::output_test_stream output;
	{
		std::vector<Input> vectorInput;
		cout_redirect guard(output.rdbuf());
		flag = readCFG("pn_diode_ideal.cfg", vectorInput);
	}
	BOOST_CHECK_EQUAL(flag, 1); /* Function returns two in case of WARNING. */

	/* ISSUE with this that it must comply with the same order which makes it  quite inconvinient for the future to adopt. */
	BOOST_CHECK(output.is_equal("WARNING: points must be an integer, and equal or greater than 1! Setting to default 1.\n"
								"WARNING: no output is defined, using default.plt!\n"
								"WARNING: no points are defined for the [voltage] with [-0.5,1]! Setting to default 1.\n"
								"WARNING: points must be an integer, and equal or greater than 1! Setting to default 1.\n"
								"WARNING: points must be an integer, and equal or greater than 1! Setting to default 1.\n"
								"WARNING: for [voltage] with [0.5,-1] the left side value must be smaller than the right! Swapping.\n"
								"WARNING: for [voltage] with [0.5,-1] the left side value must be smaller than the right! Swapping.\n"
								));

	// for these i am going to use try/throw/catch
	/* e.g. 
		try {
			if(points < 1) {
				throw std::runtime_error("ERROR: points must be equal or greater than 1!");
			} catch (std::runtime_error) {
				std::cerr << "Error: " << ex.what() << std::endl; // Print basically the message and then ask if ready to quit or set it to 1?
			}

	*/
}

BOOST_AUTO_TEST_SUITE_END()