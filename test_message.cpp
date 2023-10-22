#define BOOST_TEST_MODULE Message
#include <boost/test/included/unit_test.hpp>
#include <boost/test/tools/output_test_stream.hpp>
#include "message.h"

BOOST_AUTO_TEST_SUITE(TestMessage)

struct cout_redirect {
	cout_redirect(std::streambuf *new_buffer) 
		: old(std::cout.rdbuf(new_buffer))
	{}

	~cout_redirect() {
		std::cout.rdbuf(old);
	}

private:
	std::streambuf *old;
};

BOOST_AUTO_TEST_CASE(test_debug_1)
{
	boost::test_tools::output_test_stream output;
	{
		cout_redirect guard(output.rdbuf());
		printMessage(VERBOSITY, DEBUG, "Debug message");
	}
	BOOST_CHECK(output.is_equal("Debug message\n"));
}

BOOST_AUTO_TEST_CASE(test_info_no_debug_2)
{
	boost::test_tools::output_test_stream output;
	{
		/* Redirect stdout to the output_test_stream */
		cout_redirect guard(output.rdbuf());
		printMessage(INFO, DEBUG, "Debug message");
	}
	/* Check if the captured output matches your intended text */
	BOOST_CHECK(output.is_equal(""));
}

BOOST_AUTO_TEST_CASE(test_info_3)
{
	boost::test_tools::output_test_stream output;
	{
		cout_redirect guard(output.rdbuf());
		printMessage(INFO, INFO, "Informational message");
	}
	BOOST_CHECK(output.is_equal("Informational message\n"));
}

BOOST_AUTO_TEST_CASE(test_info_warning_error_4)
{
	boost::test_tools::output_test_stream output;
	{
		cout_redirect guard(output.rdbuf());
		printMessage(INFO, DEBUG, "Debug message");
		printMessage(INFO, INFO, "Informational message");
		printMessage(INFO, WARNING, "Warning message");
		printMessage(INFO, ERROR, "Error message");
	}
	BOOST_CHECK(output.is_equal("Informational message\nWarning message\nError message\n"));
}

BOOST_AUTO_TEST_CASE(test_error_5)
{
	boost::test_tools::output_test_stream output;
	{
		cout_redirect guard(output.rdbuf());
		printMessage(ERROR, DEBUG, "Debug message");
		printMessage(ERROR, INFO, "Informational message");
		printMessage(ERROR, WARNING, "Warning message");
		printMessage(ERROR, ERROR, "Error message");
	}
	BOOST_CHECK(output.is_equal("Error message\n"));
}

BOOST_AUTO_TEST_SUITE_END()