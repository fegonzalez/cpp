/*!\file virtual_inher_4_7_8.h

  Testing construction order with virtual inheritance & undefined operations.

  This code has been extracted from the C++ standard document [4_7_8]:

  "Member functions (including virtual member functions, 10.3) can be
  called for an object under construction.  Similarly, an object under
  construction can be the operand of the typeid operator (5.2.8) or of
  a dynamic_- cast (5.2.7). However, if these operations are performed
  in a ctor-initializer (or in a function called directly or
  indirectly from a ctor-initializer) before all the mem-initializers
  for base classes have completed, the result of the operation is
  undefined."

*/

#ifndef _UNDEF_H
#define _UNDEF_H


#include <iostream>
#include <cassert>

//==============================================================================

class Class_A {
 public:

  virtual int undef_f(){return 4;};
  
  Class_A(int)
    {
      std::cout << "\n Class_A()" << std::endl;
    }
};

//------------------------------------------------------------------------------

class Class_B : public Class_A {
  int j;
  
 public:
  virtual int undef_f();

 Class_B():
  Class_A(undef_f()), // undefined: calls member function
                      // but base Class_A not yet initialized
  j(undef_f())   // well-defined: bases are all initialized
  {
    std::cout << "\n Class_B()" << std::endl;
  } 
};

//------------------------------------------------------------------------------

class Class_C {
 public:
  Class_C(int)
    {
      std::cout << "\n Class_C()" << std::endl;
    }
};

//------------------------------------------------------------------------------

class Class_D : public Class_B, Class_C {
  int i;
 public:

  int undef_f();

 Class_D():
  //here: implicit call to Class_B default constructor
  Class_C(undef_f()), // undefined: calls member function
                      // but base Class_C not yet initialized
  i(undef_f()) // well-defined: bases are all initialized
  {
    std::cout << "\n Class_D()" << std::endl;
  } 
};
				 
//==============================================================================

#endif
