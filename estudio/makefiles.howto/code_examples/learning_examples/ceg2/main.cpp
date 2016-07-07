/*!\file main.cpp

  \brief Just a makefile test.
 */


#include "common_header.h"
#include "non_common_header.h"
#include <iostream>


int main()
{
  T  tvar = nonlocal_var;

  std::cout << "\nJUST_A_DUMMY_CONST = " << JUST_A_DUMMY_CONST << std::endl;

  std::cout << "\ntvar= " << tvar << std::endl;

        
  return 0;
}
 
