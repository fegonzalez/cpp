#ifndef _STACK5DECL_HPP_
#define _STACK5DECL_HPP_


/*!\file stack5decl.hpp The Asymmetric Assignment Operator example [k14107]

  \test [k14107] Member templates, The Asymmetric Assignment Operator

*/


#include <deque>
#include <stdexcept>


/******************************************************************************/
/* Template DECLARATION section                                               */
/******************************************************************************/


//------------------------------------------------------------------------------

template <typename T>
class Stack
{
  
public:

  inline void push(const T&);
  inline T pop();
  T top()const; //return top element

  bool empty()const
  { return elems.empty(); }

  
  // member template
  template <typename T2>
  Stack<T>& operator=(const Stack<T2>&);


  // class iterators
  typedef typename std::deque<T>::const_iterator const_iterator;
  typedef typename std::deque<T>::iterator iterator;
  iterator begin() { return elems.begin();}
  iterator end() { return elems.end();}
  const_iterator cbegin() const { return elems.begin();}
  const_iterator cend() const { return elems.end();}
  
private:

  std::deque<T> elems;  //stack elements
  
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

template <typename T>
template <typename T2>
Stack<T>& Stack<T>::operator=(const Stack<T2>& src)
{
  //auto assignment
  if((void*)this == (void*)&src)
    return (*this);
  // if(static_cast<void*>(this) == static_cast<void*>(&src))
  //   return (*this);


  elems.clear();
  
  for (typename Stack<T2>::const_iterator citr = src.cbegin();
       citr!=src.cend();
       ++citr)
  {
    elems.push_back(static_cast<T>(*citr));
  }
  
  return (*this);
}




#endif
