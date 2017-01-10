#include "trickybasics.hpp"

#include <iostream>
#include <string>
#include <cstdlib> //EXIT_FAILURE


/*!\file trickybasicstest.cpp 14.4 Tricky Basics examples

  \test [k14106]  14.4.2 Using this->

*/

//------------------------------------------------------------------------------

int test_this();

int main()
{
  test_this();
  
  std::cout << std::endl;
  return 0;
}

//------------------------------------------------------------------------------

int test_this()
{
  std::cout << "\ntest [k14106]  14.4.2 Using this->";
  
  try
    {
      Derived<int> der;
      der.foo();
      return EXIT_SUCCESS;
    }
  catch(std::exception const& ex)
    {
      std::cerr << "Error: " << __FILE__
		<< " : in function " << __func__
		<< " at line " << __LINE__ << std::endl
		<< " Compiled on " << __DATE__
		<< " at " << __TIME__ << std::endl
		<< " Exception: " << ex.what() << std::endl;
      return EXIT_FAILURE;
    }

}

//------------------------------------------------------------------------------
