/*\file dummy_c++_code.cpp
  \brief Dummy, not main(), c code to check dual compilation:
         g++ -c -x c dummy_c_code.c -x c++ dummy_c++_code.cpp
*/


#include <iostream> 

int dummy_gcc()
{
  // cout used just to watch a result
  std::cout << "C++ via cout: Compiling and Executing C++ code.\n";

  return 0;
}
