#include "addval.hpp"
#include <iostream>
#include <string>
#include <cstdlib> //EXIT_FAILURE
#include <vector>
#include <algorithm>

/*!\file addvaltest.cpp nontype function template parameters example.

  \test [k14105] nontype function template args.

*/

//------------------------------------------------------------------------------

int test();

int main()
{
  test();
  
  std::cout << std::endl;
  return 0;
}

//------------------------------------------------------------------------------

int test()
{
  std::cout << "\ntest [k14105] nontype function template args.";
  
  try
    {
      std::vector<int> source {1,2,3,4,5};
      std::vector<int> dest {10,20,30};

      // std::vector<int> source;
      // source.push_back(1);
      // source.push_back(2);
      // source.push_back(3);
      // source.push_back(4);
      // source.push_back(5);
      // std::vector<int> dest;
      // dest.push_back(10);
      // dest.push_back(20);
      // dest.push_back(30);

      
      std::cout << "\nBefore std::transform. dest = ";
      /*!\warning C++98 can't use 'auto' */

      //
      //!\test typename use example
      //
      typename std::vector<int>::const_iterator citr;
      typename std::vector<int>::const_iterator citr_end = dest.end();
      for (citr = dest.begin();
	   citr != citr_end;
	   ++citr)
      {
	std::cout << *citr << " ";
      }
	      
      std::transform
	(source.begin(), source.end(),
	 dest.begin(),
	 // operation (function template) (*14_3_2)
	 addValue<int,5>);  // after C++03 (*14_3_2)
	 // (int(*)(const int&)) addValue<int,5>);  //before C++03

      
      std::cout << "\nAfter std::transform. dest = ";  // 6 7 8 expected
      /*!\warning C++98 can't use 'auto' */
#ifndef auto
      for (std::vector<int>::const_iterator citr = dest.begin();
	   citr != dest.end();
	   ++citr)
      {
	std::cout << *citr << " ";
      }
#else
      for (auto citr = dest.begin();
	   citr != dest.end();
	   ++citr)
      {
	std::cout << *citr << " ";
      }
#endif
      
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
