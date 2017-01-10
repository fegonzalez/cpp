#include "stack4.hpp"
#include <iostream>
#include <string>
#include <cstdlib> //EXIT_FAILURE


/*!\file stack4test.cpp nontype template arguments.

  \test [k14104] nontype template arguments

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
  try
    {
      typedef Stack<int,20> Int20Stack;
      typedef Stack<std::string,20> String20Stack;
      typedef Stack<int,40> Int40Stack;

      Int20Stack int20;
      String20Stack string20;
  
      int20.push(21);
      std::cout << int20.top() << std::endl;
      std::cout << int20.pop() << std::endl;

      string20.push("test [k14104] nontype template arguments");
      std::cout << string20.top() << std::endl;
      std::cout << string20.pop() <<  std::endl;
      //int20.pop();    //rise exception in the primary template Stack<T>
      //string20.pop();    //rise exception in the primary template Stack<T>

      Int40Stack int40;
      int40.push(41);
      std::cout << int40.top() << std::endl;
      std::cout << int40.pop() << std::endl;
      
      /*!\bug Compilation error: No automatic type conversion is
         allowed in calls to function templates. [k14104]

      stack4test.cpp:60:13: error: no match for ‘operator=’ (operand types are ‘Int20Stack {aka Stack<int, 20>}’ and ‘Int40Stack {aka Stack<int, 40>}’)
       int20 = int40;
      */
      
      //int20 = int40;


      
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
