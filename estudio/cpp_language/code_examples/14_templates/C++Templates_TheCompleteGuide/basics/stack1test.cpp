#include "stack1.hpp"
//#include "stack2.hpp"  // Error: re-definition of Stack
#include <iostream>
#include <string>
#include <cstdlib> //EXIT_FAILURE


/*!\file stack1test.cpp Class template example.

  \test [k14101] class template 

*/

//------------------------------------------------------------------------------

int test_class_template();
int test_nontype_stringliteral_parameter();


int main()
{
  test_class_template();
  test_nontype_stringliteral_parameter();
  
  std::cout << std::endl;
  return 0;
}

//------------------------------------------------------------------------------

int test_class_template()
{
  try
    {
      typedef Stack<int> intStack;

      Stack<std::string> stringStack;
      intStack an_int_stack;
    
      an_int_stack.push(1);
      std::cout << an_int_stack.top() << std::endl;

      stringStack.push("test [k14101] class template");
      std::cout << stringStack.top() << std::endl;
						  
      an_int_stack.pop();
      std::cout << stringStack.pop() <<  std::endl;

      //an_int_stack.pop(); //rise exception in the primary template Stack<T>
      
      //stringStack.pop();  //rise exception (in the specialization
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

int test_nontype_stringliteral_parameter()
  {
  try
    {
      /*stack1test.cpp:77:13: error: the value of ‘internal_linkage’
	is not usable in a constant expression
       */
      //const char* internal_linkage = "hello";
      //Stack<internal_linkage> x;

      /*!\bug Expected OK; Obtained: compialtion error:

	error: ‘external_linkage’ has both ‘extern’ and initializer
	extern const char external_linkage[] = "hello";
      */
      // extern const char external_linkage[] = "hello";
      // Stack<external_linkage> x;
      
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
