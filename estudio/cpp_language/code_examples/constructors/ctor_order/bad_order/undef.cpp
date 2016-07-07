/*!\file undef.cpp

  \warning tehs expected "undefined " result is not get.

  \exception If we explicitly do not define, thus do not write the
  code bellow, of an undef_f() function:


Building target: undef_init_test
g++  -g -o undef_init_test undef.o undef_init_test.o 

undef_init_test.o: En la función `Class_D::Class_D()':
/home/fer/workspace/C_C++/estudio/cpp_language/code_examples/constructors/ctor_order/bad_order/undef.h:74: referencia a `Class_D::undef_f()' sin definir

/home/fer/workspace/C_C++/estudio/cpp_language/code_examples/constructors/ctor_order/bad_order/undef.h:74: referencia a `vtable for Class_D' sin definir

/home/fer/workspace/C_C++/estudio/cpp_language/code_examples/constructors/ctor_order/bad_order/undef.h:74: referencia a `Class_D::undef_f()' sin definir

collect2: error: ld returned 1 exit status
Makefile:211: recipe for target 'undef_init_test' failed
make: *** [undef_init_test] Error 1


  Q: With a separate impl. of the virtual member functions: any change?
  
  A: NO. 


\warning C++ standard, what undefined means ?

1.3.25 undefined behavior
behavior for which this International Standard imposes no requirements

[ Note: Undefined behavior may be expected when this International
Standard omits any explicit definition of behavior or when a program
uses an erroneous construct or erroneous data. Permissible undefined
behavior ranges from ignoring the situation completely with
unpredictable results, to behaving during translation or program
execution in a documented manner characteristic of the environment
(with or without the issuance of a diagnostic message), to terminating
a translation or execution (with the issuance of a diagnostic
message).  Many erroneous program constructs do not engender undefined
behavior; they are required to be diagnosed.  —end note ]


*/

#include "undef.h"

#include <iostream>
#include <cassert>


//==============================================================================

int Class_B::undef_f()
{
  std::cout << "\nB::undef_f" << std::endl;
  return 100;
}

//------------------------------------------------------------------------------

int Class_D::undef_f()
{
  std::cout << "\nD::undef_f" << std::endl;
  return 33;
}

//==============================================================================
