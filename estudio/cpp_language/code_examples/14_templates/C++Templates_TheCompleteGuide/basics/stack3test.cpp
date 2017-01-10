#include "stack3.hpp"
#include <iostream>
#include <string>
#include <cstdlib> //EXIT_FAILURE
#include <deque>


/*!\file stack3.hpp class template's  default template arguments example.

  \test [k14103] default template arguments

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
      //typedef Stack<int> intStack;
      typedef Stack<int,std::deque<int> > intStack;

      Stack<std::string,std::deque<std::string> > stringStack;
      intStack an_int_stack;
    
      an_int_stack.push(3);
      std::cout << an_int_stack.top() << std::endl;

      stringStack.push("test [k14103] default template arguments");
      std::cout << stringStack.top() << std::endl;
						  
      an_int_stack.pop();
      std::cout << stringStack.pop() <<  std::endl;

      //an_int_stack.pop(); //rise exception in the primary template Stack<T>
      
      //stringStack.pop();  //rise exception in the default template class
			    //template class Stack<T,CONT>

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
