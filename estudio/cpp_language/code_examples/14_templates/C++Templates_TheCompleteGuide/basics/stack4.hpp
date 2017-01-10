#ifndef _STACK4_HPP_
#define _STACK4_HPP_

/*!\file stack4.hpp nontype template arguments.

  \test [k14104] nontype template arguments - "./basics/stack4test.hpp"

*/


#include <stdexcept>


/******************************************************************************/
/* Template DECLARATION section                                               */
/******************************************************************************/
 

template <typename T, int MAXSIZE> // 2nd argument is a value rather than a type
class Stack
{
public:
  
  //constructor
  Stack();

  //destructor
  ~Stack();


  void push(const T&);
  T pop();
  T top()const; //return top element

  bool empty()const
  { return numElems==0; }

  bool full()const
  { return numElems==MAXSIZE; }
  
private:

  T elems[MAXSIZE]; //stack elements
  int numElems;     //current number of elements
  
}; //end_clas_Stack



/******************************************************************************/
/* Template DEFITION section                                                  */
/******************************************************************************/

template <typename T, int MAXSIZE>
inline
Stack<T,MAXSIZE>::Stack()
  :numElems(0)
{
}

//------------------------------------------------------------------------------

template <typename T, int MAXSIZE>
inline
Stack<T,MAXSIZE>::~Stack()
{
  numElems=0;
}


//------------------------------------------------------------------------------

template <typename T, int MAXSIZE>
inline
void Stack<T,MAXSIZE>::push(const T& elem)
{
  if(full())
  {
     throw std::out_of_range("Stack<>::push(): full stack");
  }
  elems[numElems++] = elem;
}

//------------------------------------------------------------------------------

template <typename T, int MAXSIZE>
inline
T Stack<T,MAXSIZE>::pop()
{
  if(empty())
  {
     throw std::out_of_range("Stack<>::pop(): empty stack");
  }

  T elem = elems[--numElems]; //return copy of last element and dec numelems
  return elem; 
}

//------------------------------------------------------------------------------

template<typename T, int MAXSIZE>
inline
T Stack<T,MAXSIZE>::top() const
{
  if(empty())
  {
     throw std::out_of_range("Stack<>::top(): empty stack");
  }
  
  return elems[numElems-1]; //return copy of last element
}

//------------------------------------------------------------------------------


#endif
