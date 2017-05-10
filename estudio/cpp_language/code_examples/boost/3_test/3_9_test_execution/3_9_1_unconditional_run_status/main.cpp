/*!\file cpp_language/code_examples/boost/3_test/3_9_test_execution/3_9_1_unconditional_run_status/main.cpp

  \test [k3_6]. Testing boost's test library, 3.9 Enabling or disabling test unit execution:  decorators "disabled" & "enabled"

*/


//==============================================================================
/*
  suite-Level Decorator
*/

#define BOOST_TEST_MODULE decorator_05

#ifndef BOOST_TEST_DYN_LINK
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
//#include <boost/test/included/unit_test.hpp>

namespace utf  = boost::unit_test;

BOOST_AUTO_TEST_SUITE(suite1, * utf::disabled())

BOOST_AUTO_TEST_CASE(test1)
{ BOOST_CHECK(1!=1); }

BOOST_AUTO_TEST_CASE(test2, * utf::enabled())
{ BOOST_TEST(2 != 2); }

BOOST_AUTO_TEST_SUITE_END()   
