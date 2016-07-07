/*\file c++_code.cpp

  \test Checking the difference between gcc & g++ over a C++ file

  // one step
  g++ c++_code.cpp           // OK

  gcc c++_code.cpp           // Error (compilation OK, but link error)
  gcc c++_code.cpp -lstdc++  // OK


  // two steps
  gcc -c c++_code.cpp        // Compilation OK

  gcc c++_code.o             // Link error
  gcc c++_code.o -lstdc++    // OK. 
 */

#include <iostream>  // cout 

int main()
{
  // cout used just to watch a result
  std::cout << "C++ via cout: Compiling and Executing C++ code.\n";

  return 0;
}


