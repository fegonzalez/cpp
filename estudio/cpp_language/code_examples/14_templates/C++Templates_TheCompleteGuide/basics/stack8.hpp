#ifndef _STACK_HPP_
#define _STACK_HPP_


/*!\file stack8.hpp Template Template Parameters example [k14108]

  \test [k14108] Template Template Parameters

*/


#include <deque>
#include <stdexcept>
//#include <allocator>

/******************************************************************************/
/* Template DECLARATION section                                               */
/******************************************************************************/


//------------------------------------------------------------------------------

/*!\error:  expected a template of type ‘template<class ELEM> class CONT’, got ‘template<class _Tp, class _Alloc> class std::deque’

template <typename T,
	  template<typename ELEM>
	  class CONT = std::deque>
class Stack
*/


/*!\error: expected ‘class’ before ‘CONT’
template <typename T,
	  template<typename ELEM,
		   typename = std::allocator<ELEM> >
	  typename CONT = std::deque>
class Stack
*/


template <typename T,
	  template<typename ELEM,
		   typename = std::allocator<ELEM> >
	  class CONT = std::deque>
class Stack
{
  
public:

  void push(const T&);
  T pop();
  T top()const; //return top element

  bool empty()const
  { return elems.empty(); }

  size_t length()const
  {return elems.length();}
  
  // member template
  template <typename T2,
	  template<typename ELEM2,
		   typename = std::allocator<ELEM2> >
	  class CONT2>
  Stack<T,CONT>& operator=(const Stack<T2,CONT2>&);
  
  // class iterators

  typedef typename CONT<T>::const_iterator const_iterator;
  typedef typename CONT<T>::iterator iterator;
  iterator begin() { return elems.begin();}
  iterator end() { return elems.end();}
  const_iterator cbegin() const { return elems.begin();}
  const_iterator cend() const { return elems.end();}
  
private:

  //  std::deque<T> elems;
  CONT<T> elems;  //stack elements
  
}; //end_clas_Stack



/******************************************************************************/
/* Template DEFITION section                                                  */
/******************************************************************************/


template <typename T, template<typename,typename> class CONT>
inline
void Stack<T,CONT>::push(const T& elem)
{
  elems.push_back(elem);
}

//------------------------------------------------------------------------------

template <typename T, template<typename,typename> class CONT>
inline
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

template <typename T, template<typename,typename> class CONT>
inline
T Stack<T,CONT>::top() const
{
  if(empty())
  {
     throw std::out_of_range("Stack<>::top(): empty stack");
  }
  return elems.back(); //return copy of last element
}

//------------------------------------------------------------------------------

template <typename T, template<typename,typename> class CONT>
template <typename T2, template<typename,typename> class CONT2>
inline
Stack<T,CONT>& Stack<T,CONT>::operator=(const Stack<T2,CONT2>& src)
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
