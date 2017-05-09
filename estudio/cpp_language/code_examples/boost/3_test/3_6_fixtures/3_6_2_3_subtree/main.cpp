/*!\file cpp_language/code_examples/boost/3_test/3_5_decorators/main.cpp

  \test [k3_4]. Testing boost's test library, 3.6 Fixtures; Single
  test case fixture with BOOST_FIXTURE_TEST_CASE

*/

//==============================================================================


#define BOOST_TEST_MODULE example

#ifndef BOOST_TEST_DYN_LINK
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>


// Fixture class
struct F
{
  F():the_i(0){ BOOST_TEST_MESSAGE( "setup fixture" ); }

  ~F() { BOOST_TEST_MESSAGE( "teardown fixture" ); }
    
  int the_i;
};

//test cases

BOOST_FIXTURE_TEST_SUITE(suite_subtree, F)

BOOST_AUTO_TEST_CASE(test_case1)
{
  BOOST_TEST_MESSAGE("running test_case1");
  BOOST_CHECK_EQUAL( the_i, 0 ); 
  ++the_i;  // direct access to the fixture from the test body
}

BOOST_AUTO_TEST_CASE( test_case2 )
{
  BOOST_TEST_MESSAGE("running test_case2");
  BOOST_CHECK_EQUAL( the_i, 0 );
}

BOOST_AUTO_TEST_SUITE_END()
