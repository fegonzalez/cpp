#include "stack8.hpp"
#include <iostream>
#include <string>
#include <cstdlib> //EXIT_FAILURE
#include <vector>
// #include <algorithm>

/*!\file stack8test.cpp Template Template Parameters example [k14108]

  \test [k14108] Template Template Parameters - "./basics/stack8test.cpp

*/
 
//------------------------------------------------------------------------------

void booktest();

int main()
{
  std::cout << "\ntest [k14108] Template Template Parameters.";
  
  booktest();
  
  std::cout << std::endl;
  return 0;
}

//-----------------------------------------------------------------------------

template <typename T, template<typename,typename> class CONT>
void print_stack(const Stack<T,CONT> & src)
{
  std::cout  << std::endl << "{ ";
  for(typename Stack<T,CONT>::const_iterator citr= src.cbegin();
      citr!=src.cend();
      ++citr)
    {std::cout << *citr << ' ';}
  std::cout << '}' << std::endl;
}

//------------------------------------------------------------------------------

void booktest()
{ 
  try
    {
      std::cout << "\nusing the default  internal container" << std::endl;

      typedef Stack<int> intStack;
      typedef Stack<double> doubleStack;
      

      intStack istack;
      istack.push(42);
      istack.push(7);
      doubleStack dstack;
      dstack.push(7.7);

      dstack = istack;
      print_stack<double>(dstack);
      print_stack<int>(istack);
      dstack.pop();
      dstack.pop();
      dstack.pop(); //rise exception
    } 
  catch(std::exception const& ex)
    {
      std::cerr << "Error: " << __FILE__
		<< " : in function " << __func__
		<< " Exception: " << ex.what() << std::endl;
    }

  //using a vector as an internal container

  try
    {
      std::cout << std::endl;
      std::cout << "\nusing a vector as an internal container" << std::endl;
      typedef Stack<int,std::vector> vintStack;
      vintStack vistack;
      vistack.push(42);
      vistack.push(7);
      std::cout << vistack.top();
      print_stack<int>(vistack);
    } 
  catch(std::exception const& ex)
    {
      std::cerr << "Error: " << __FILE__
		<< " : in function " << __func__
		<< " Exception: " << ex.what() << std::endl;
    }   
}
