/*!\file cpp_language/code_examples/boost/3_test/3_1_framework_tutorial/main.cpp

  \test [k3_2]. Testing boost's test library, 3.2.3 Shared library usage variant

*/

#include <iostream>

//1. First add the following line to ALL TRANSLATION UNITS in a test module...
#include <boost/test/unit_test.hpp>

//... and ONLY ONE translation unit should include following lines:
#define BOOST_TEST_MODULE BoostTestHowto Static UsageVariant //o


BOOST_AUTO_TEST_CASE(first_test)
{
  BOOST_CHECK_EQUAL(77, 111);
}

//  2. The second step is to link with the Unit Test Framework static library
//     -lboost_unit_test_framework


