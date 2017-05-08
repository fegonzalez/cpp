/*!\file cpp_language/code_examples/boost/3_test/3_1_framework_tutorial/main.cpp

  \test [k3_2]. Testing boost's test library, 3.2.3 Shared library usage variant

*/


/*!\warning "can't use testing tools before framework is initialized" error

  #define BOOST_TEST_DYN_LINK 

  without: runtime error:
  "can't use testing tools before framework is initialized"

  with: compilation error: a main() already exists at unit_test.hpp
  solution: namespace the test unit.
  
*/



//==============================================================================
// Customizing the module's entry point
//==============================================================================

/*!\warning Not need anymore if the init function
  (init_unit_test()) is defined
*/	
#define BOOST_TEST_MODULE BoostTestHowto_SharedUsageVariant
#define BOOST_TEST_NO_MAIN  //# (its value is irrelevant)


#ifndef BOOST_TEST_DYN_LINK
#define BOOST_TEST_DYN_LINK
#endif

#include <boost/test/unit_test.hpp>


//==============================================================================
// (MANUALLY DEFINED) initialization function:
//==============================================================================

// bool init_unit_test()
// {
//   return true;
// }


//==============================================================================
// (MANUALLY DEFINED) entry point:
//==============================================================================

int main(int argc, char* argv[])
{
  return boost::unit_test::unit_test_main( &init_unit_test, argc, argv );
}

//==============================================================================
/*!\test Aby test case 

Running 1 test case...
main.cpp(60): error in "first_test": check i == 2 failed

*** 1 failure detected in test suite "BoostTestHowto_SharedUsageVariant"

*/
BOOST_AUTO_TEST_CASE(first_test)
{
  int i = 1;
  // Before boost 1.59 BOOST_TEST was not yet defined
  BOOST_CHECK(i);
  BOOST_CHECK(i == 2);
}
