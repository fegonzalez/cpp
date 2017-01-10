#ifndef _STACK2_HPP_
#define _STACK2_HPP_

/*!\file stack2.hpp (Explicit) class template specialization example.

  \test [k14102] class template specialization

*/

//#include "stack1.hpp" // Stack<T>
#include "stack3.hpp"   // Stack<T,CONT>

#include <string>
#include <deque>


/******************************************************************************/
/* Template DECLARATION section                                               

9) If you specialize a class template, you MUST also specialize all
   member functions.

*/
/******************************************************************************/
 

template <>
class Stack<std::string>
{
public:
  
  inline void push(const std::string&);
  inline std::string pop();
  inline std::string top()const; //return top element

  bool empty()const
  { return elems.empty(); }
  
private:

  /*!\notice deque instead vector just to demonstrate that the
     implementation of a specializations might look very different
  */
  std::deque<std::string> elems;  
  
}; //end_clas_Stack



/******************************************************************************/
/* Template DEFITION section                                                  */
/******************************************************************************/


void Stack<std::string>::push(const std::string& elem)
{
  elems.push_back(elem);
}

//------------------------------------------------------------------------------

std::string Stack<std::string>::pop()
{
  if(empty())
  {
     throw std::out_of_range("Stack<std::string>::pop(): empty stack");
  }

  std::string elem = elems.back(); //return copy of last element
  elems.pop_back();
  return elem; 
}

//------------------------------------------------------------------------------

std::string Stack<std::string>::top() const
{
  if(empty())
  {
     throw std::out_of_range("Stack<std::string>::top(): empty stack");
  }
  return elems.back(); //return copy of last element
}

//------------------------------------------------------------------------------

#endif
