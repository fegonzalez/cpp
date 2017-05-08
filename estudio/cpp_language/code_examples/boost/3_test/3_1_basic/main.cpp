/*!\file cpp_language/code_examples/boost/3_test/3_1_framework_tutorial/main.cpp

  \brief Testing boost's test library. 

*/


/*!\warning "can't use testing tools before framework is initialized" error

  #define BOOST_TEST_DYN_LINK 

  without: runtime error:
  "can't use testing tools before framework is initialized"

  with: compilation error: a main() already exists at unit_test.hpp
  solution: namespace the test unit.
  
*/



#define BOOST_TEST_MODULE BoostTestHowto
//#include <boost/test/unit_test.hpp> //main must be explicitly defined
#include <boost/test/included/unit_test.hpp> //main defined inside

/*!\test [k3_1] Basic library test

 */
BOOST_AUTO_TEST_CASE(first_test)
{
  int i = 1;

  /* Only since boost 1.59
  BOOST_TEST(i);
  BOOST_TEST(i == 2);
  */

  //  Just in case before boost 1.59
  BOOST_CHECK(i);
  BOOST_CHECK(i == 2);

}


/*!\test [k3_1] Seven ways to detect and report the same error.

  (1)
	
  This approach uses the BOOST_CHECK tool, which displays an error
  message (by default on std::cout) that includes the expression that
  failed, the source file name, and the source file line number. It also
  increments the error count. At program termination, the error count
  will be displayed automatically by the Unit Test Framework.


  (2)
	
  This approach uses the BOOST_REQUIRE tool, is similar to approach #1,
  except that after displaying the error, an exception is thrown, to be
  caught by the Unit Test Framework. This approach is suitable when
  writing an explicit test program, and the error would be so severe as
  to make further testing impractical. BOOST_REQUIRE differs from the
  C++ Standard Library's assert() macro in that it is always generated,
  and channels error detection into the uniform Unit Test Framework
  reporting procedure.


  (3)
	
  This approach is similar to approach #1, except that the error
  detection and error reporting are coded separately. This is most
  useful when the specific condition being tested requires several
  independent statements and/or is not indicative of the reason for
  failure.


  (4)	

  This approach is similar to approach #2, except that the error
  detection and error reporting are coded separately. This is most
  useful when the specific condition being tested requires several
  independent statements and/or is not indicative of the reason for
  failure.


  (5)	

  This approach throws an exception, which will be caught and reported
  by the Unit Test Framework. The error message displayed when the
  exception is caught will be most meaningful if the exception is
  derived from std::exception, or is a char* or std::string.


  (6)
	
  This approach uses the BOOST_CHECK_MESSAGE tool, is similar to
  approach #1, except that similar to the approach #3 displays an
  alternative error message specified as a second argument.


  (7)	

  This approach uses the BOOST_CHECK_EQUAL tool and functionally is
  similar to approach #1. This approach is most attractive for checking
  equality of two variables, since in case of error it shows mismatched values.
*/


int add( int i, int j ) { return i+j; }

BOOST_AUTO_TEST_CASE( k3_1_test )
{
  BOOST_CHECK( add(2,2) == 4 );  // #1 continues on error 
}


// int main()
// {
//   return 0;
// }

