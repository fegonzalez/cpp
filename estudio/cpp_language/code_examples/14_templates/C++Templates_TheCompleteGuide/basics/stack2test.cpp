#include "stack2.hpp"
#include <iostream>
#include <string>
#include <cstdlib> //EXIT_FAILURE


/*!\file stack2.hpp (Explicit) class template specialization example.

  \test [k14102] class template specialization

        template <>
        class Stack<std::string>
*/

//------------------------------------------------------------------------------


int class_template();

int main()
{
  class_template();
  
  std::cout << std::endl;
  return 0;
}

//------------------------------------------------------------------------------

int class_template()
{
  try
    {
      Stack<std::string> stringStack;
      stringStack.push("TEST [k14102] class template specialization ");
      std::cout << stringStack.top() << std::endl;
      std::cout << stringStack.pop() << std::endl;
      //stringStack.pop();  //rise exception in the specialization:
			  //template class Stack<std::string>
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
