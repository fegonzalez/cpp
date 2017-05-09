/*!\file cpp_language/code_examples/boost/3_test/3_1_framework_tutorial/main.cpp

  \test [k3_2]. Testing boost's test library, 3.2.3 Shared library usage variant

*/

#include <iostream>


//#define AUTO_DEFINED


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#ifdef AUTO_DEFINED
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#define BOOST_TEST_MODULE BoostTestHowto_SharedUsageVariant //required
#ifndef BOOST_TEST_DYN_LINK
#define BOOST_TEST_DYN_LINK
#endif

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(first_test)
{
  BOOST_CHECK_EQUAL(77, 111);
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#else // AUTO_DEFINED
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


#define BOOST_TEST_MODULE BoostTestHowto_SharedUsageVariant
#ifndef BOOST_TEST_DYN_LINK
#define BOOST_TEST_DYN_LINK
#endif


// Manually Defined entry point and init. function
#define BOOST_TEST_NO_MAIN         // required


#include <boost/test/unit_test.hpp>


// Manually Defined entry point and init. function
// Entry point function
int main(int argc, char* argv[])   // required
{
  return boost::unit_test::unit_test_main( &init_unit_test, argc, argv );
}

// Manually Defined entry point and init. function
// Initialization function
// bool init_unit_test() 	    // forbiden
// { return true; }


BOOST_AUTO_TEST_CASE(first_test)
{
  BOOST_CHECK_EQUAL(77, 111);
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#endif // AUTO_DEFINED
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


