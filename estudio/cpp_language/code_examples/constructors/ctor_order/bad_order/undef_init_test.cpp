/*!\test [k13] - Test different call-points to check where is the v-pointer
  initialized in practice:

  \test 1: mem-init-list before direct base classes: expected error.

  \test 2: mem-init-list after direct base classes: expected ok.

  \test 3: constructor body: expected ok.


   Theory:
   # c++.howto 10.3.2 virtual table & virtual pointer: resolving dynamic binding
   # [4_11_2] https://isocpp.org/wiki/faq/virtual-functions#dyn-binding 

   WARNING	   
   The C++ standard commands the initialization of the v-pointer after
   all the base classes has been defined, but it doesn't specifies
   exactly where from this point, thus it is compiler-implementation
   dependant. [4_7_8] [k13]


  \test bad construction_order: calling member functions before the
  definition of the v-pointer.


 */

//==============================================================================

#include "undef.h"


int main()
{
  std::cout << "\n ctor_order test (c++ standard 12.6.2)" << std::endl;

  /*
  \test 1: mem-init-list before direct base classes: expected error.

  \test 2: mem-init-list after direct base classes: expected ok.

  \test 3: constructor body: expected ok.

    */

  Class_D vd_obj;

    
  std::cout << std::endl;
  return 0;
}
