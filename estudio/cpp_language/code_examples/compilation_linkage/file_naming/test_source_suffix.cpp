/*\file test_source_suffix.cpp

  - Checking "c++.howto", A.2. File naming: Compilers actually do care
    about the form of the source file.

    Test: g++ test_source_suffix.cpp
    Expected: printing ERR_MSG_SRC (at this file), and ERR_MSG_HEADER
              (at test_header.h)
    Obtained: the expected result.
 */

#include <iostream>  // cout 

#include "test_header.h"

int main()
{
  const std::string ERR_MSG_SRC = "WARNING Compilers actually do care about the form of the source file.";

  std::cout << ERR_MSG_SRC << std::endl;
  std::cout << ERR_MSG_HEADER << std::endl;
  return 0;
}
