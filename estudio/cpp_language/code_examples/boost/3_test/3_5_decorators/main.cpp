/*!\file cpp_language/code_examples/boost/3_test/3_5_decorators/main.cpp

  \test [k3_3]. Testing boost's test library, 3.5 Decorators

*/


//==============================================================================
/*
  Test-Level Decorator
*/
/*!\bug compilation error:

g++ -c -I . -I OOST_ROOT  -std=c++11  -Wall -Wextra  -Werror       -g  main.cpp  -o main.o 
main.cpp:30:59: error: macro "BOOST_AUTO_TEST_CASE" passed 2 arguments, but takes just 1
*/



//Renaning the Master Suite
#define BOOST_TEST_MODULE decorator_01

// Shared library usage variant
#ifndef BOOST_TEST_DYN_LINK
#define BOOST_TEST_DYN_LINK
#endif
// boost precompiled library
#include <boost/test/unit_test.hpp>

namespace utf = boost::unit_test;

// a concrete test case with decoration
BOOST_AUTO_TEST_CASE(test_case1, (* utf::label("trivial")))
{
  //BOOST_TEST(true);
  BOOST_CHECK((true));
}

// a concrete test case with (aa different) decoration
//
// BOOST_AUTO_TEST_CASE(test_case2,
//   * utf::label("trivial")
//   * utf::label("cmp")
//   * utf::description("testing equality of ones"))
// {
//   BOOST_TEST(1 == 1);
// }




//==============================================================================
/*
  suite-Level Decorator
*/

/*!\bug compilation error:

main.cpp:70:54: error: macro "BOOST_AUTO_TEST_SUITE" passed 2 arguments, but takes just 1


//Renaning the Master Suite
#define BOOST_TEST_MODULE decorator_02

// Shared library usage variant
#ifndef BOOST_TEST_DYN_LINK
#define BOOST_TEST_DYN_LINK
#endif
// boost precompiled library
#include <boost/test/unit_test.hpp>

namespace utf = boost::unit_test;

//defining a decorator for the entire suite
BOOST_AUTO_TEST_SUITE(suite1, * utf::label("trivial"))

BOOST_AUTO_TEST_CASE(test_case1)
{
  BOOST_TEST(true);
}

BOOST_AUTO_TEST_CASE(test_case2)
{
  BOOST_TEST(1 == 1);
}

BOOST_AUTO_TEST_SUITE_END()
*/


//==============================================================================
/*
  suite-Level Decorator
*/
/*
#define BOOST_TEST_MODULE decorator_00

#ifndef BOOST_TEST_DYN_LINK
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
//#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

namespace utf  = boost::unit_test;
namespace data = boost::unit_test::data;

BOOST_TEST_DECORATOR(* utf::description("with description"))
BOOST_DATA_TEST_CASE(test_1, data::xrange(4))
{
  BOOST_TEST(sample >= 0);
}
*/
