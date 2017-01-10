#ifndef _STACK4_HPP_
#define _STACK4_HPP_

/*!\file trickybasics.hpp 14.4 Tricky Basics examples

  \test [k14106]  14.4.2 Using this->

*/

//#include <stdexcept>
#include <iostream>

//------------------------------------------------------------------------------

template <typename T>
class Base
{
public:
  void exit()
  {
    std::cout << "\n"
	      << __FILE__
	      << " : Base<T>::" << __func__
	      << std::endl;
  }

  void exit2()
  {
    std::cout << "\n"
	      << __FILE__
	      << " : Base<T>::" << __func__
	      << std::endl;
  }

};

//------------------------------------------------------------------------------

template <typename T>
class Derived: public Base<T>
{
public:

  void exit2()
  {
    std::cout << "\n"
	      << __FILE__
	      << " : Derived<T>::" << __func__
	      << std::endl;
  }
  
  void foo()
  {
    //exit(); //ERROR: trickybasics.hpp:29:10: error: there are no
	    //arguments to ‘exit’ that depend on a template parameter,
	    //so a declaration of ‘exit’ must be available
	    //[-fpermissive]

    Base<T>::exit(); // ok: calls Base::exit()
    this->exit();    // ok: calls Base::exit()
    exit2();         // ok: calls Derived::exit2()
    this->exit2();   // ok: calls Derived::exit2()
  }  
};

//------------------------------------------------------------------------------


#endif
