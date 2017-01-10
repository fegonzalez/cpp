#ifndef _STACK1_HPP_
#define _STACK1_HPP_

/*!\file stack1.hpp Class template example.

  \test [k14101] class template 

*/


#include <vector>
#include <stdexcept>


/******************************************************************************/
/* Template DECLARATION section                                               */
/******************************************************************************/
 

template <typename T>
class Stack
{
public:
  
  inline void push(const T&);
  inline T pop();
  T top()const; //return top element

  bool empty()const
  { return elems.empty(); }
  
private:

  std::vector<T> elems;  //stack elements
  
}; //end_clas_Stack



/******************************************************************************/
/* Template DEFITION section                                                  */
/******************************************************************************/


template <typename T>
void Stack<T>::push(const T& elem)
{
  elems.push_back(elem);
}

//------------------------------------------------------------------------------

template <typename T>
T Stack<T>::pop()
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

template<typename T>
inline T Stack<T>::top() const
{
  if(empty())
  {
     throw std::out_of_range("Stack<>::top(): empty stack");
  }
  return elems.back(); //return copy of last element
}

//------------------------------------------------------------------------------


#endif
