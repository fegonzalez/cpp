#ifndef _STACK3_HPP_
#define _STACK3_HPP_


/*!\file stack3.hpp class template's  default template arguments example.

  \test [k14103] default template arguments

  \warning Re-declaration of class Stack => stack1.hpp and stack3.hpp
  are incompatibles.
*/


#include <vector>
#include <stdexcept>


/******************************************************************************/
/* Template DECLARATION section                                               */
/******************************************************************************/


template <typename T, typename CONT = std::vector<T> >
class Stack
{
public:
  
  inline void push(const T&);
  inline T pop();
  inline T top()const; //return top element

  bool empty()const
  { return elems.empty(); }
  
private:

  CONT elems;  //stack elements
  
}; //end_clas_Stack


/******************************************************************************/
/* Template DEFITION section                                                  */
/******************************************************************************/


template <typename T, typename CONT>
void Stack<T,CONT>::push(const T& elem)   // type: Stack<T,CONT>
{
  elems.push_back(elem);
}

//------------------------------------------------------------------------------

template <typename T, typename CONT>
T Stack<T,CONT>::pop()
{
  if(empty())
  {
     throw std::out_of_range("Stack<>::pop(): empty stack");
  }
  T elem = elems.back(); //return copy of last element
  elems.pop_back();
  return elem; 
}

//------------------------------------------------------------------------------

template <typename T, typename CONT>
inline T Stack<T,CONT>::top() const
{
  if(empty())
  {
     throw std::out_of_range("Stack<>::top(): empty stack");
  }
  return elems.back(); //return copy of last element
}

//------------------------------------------------------------------------------


#endif
