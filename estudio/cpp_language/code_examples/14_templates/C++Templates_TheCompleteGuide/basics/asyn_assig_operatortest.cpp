#include "asyn_assig_operator.hpp"
#include <iostream>
#include <string>
#include <cstdlib> //EXIT_FAILURE
// #include <vector>
// #include <algorithm>

/*!\file asyn_assig_operatortest.cpp The Asymmetric Assignment
   Operator example [k14107]

  \test [k14107] Member templates, The Asymmetric Assignment Operator

*/

//------------------------------------------------------------------------------

int test();

int main()
{
  test();
  
  std::cout << std::endl;
  return 0;
}

//-----------------------------------------------------------------------------

template <typename T>
void print_stack(const Stack<T> & src)
{
  std::cout  << std::endl << "{ ";
  for(typename Stack<T>::const_iterator citr= src.cbegin();
      citr!=src.cend();
      ++citr)
    {std::cout << *citr << ' ';}
  std::cout << '}' << std::endl;
}

//------------------------------------------------------------------------------

int test()
{
  std::cout << "\ntest [k14107] Member templates, The Asymmetric Assignment Operator.";
  
  try
    {
      typedef Stack<int> intStack;
      typedef Stack<double> doubleStack;
      

      intStack istack;
      istack.push(1);
      istack.push(2);
      doubleStack dstack;
      dstack.push(10.0);
      dstack.push(20.70);
      dstack.push(-33.33);

      print_stack<int>(istack);
      istack = dstack;
      print_stack<int>(istack);

      // typedef Stack<std::string> stringStack;
      // stringStack sstack;
      // istack = sstack; //error: invalid conversion from std::string to int
      
 
	
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
