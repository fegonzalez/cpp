/*\file test_header_suffix.cpp

  - Checking "c++.howto", A.2. File naming: Compilers usually don’t
    care about the form of header file names, but IDEs sometimes do.


    Test: g++ test_source_suffix.cpp

    Expected: printing ERR_MSG_NOHEADER ("test_header") and
              ERR_MSG_NONUSUAL_HEADER ("test_header.any_dummy_SUFFIX")

    Obtained: the expected result.
 */

#include <iostream>  // cout 

#include "test_header.any_dummy_SUFFIX"
#include "test_header"

int main()
{
  std::cout << ERR_MSG_NOHEADER << std::endl;
  std::cout << ERR_MSG_NONUSUAL_HEADER << std::endl;
  return 0;
}
