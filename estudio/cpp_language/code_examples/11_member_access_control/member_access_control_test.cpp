/******************************************************************************/
/*!\test [k11_01] Default constructor                                         */
/******************************************************************************/

//!\test 11.7 Nested classes


/******************************************************************************/

#include "nested_classes.h"
#include "access_inheritance.h"
#include "protected.h"


#include <iostream>

// forward declarations


//------------------------------------------------------------------------------


//==============================================================================

int main()
{
  access_inheritance_test();
  nested_classes_test();
  protected_test();  
  std::cout << std::endl;

  return 0;
}
