/*!\test extern_test.cpp

A variable with the same name "shared_var" can be defined and used
in independent files without problems: 

*/


#include "a.h"
#include "b.h"

#include <iostream>

int main() 
{
  std::cout << "\nextern_test.cpp"
	    << std::endl;

  std::cout << shared_var;
    
  std::cout << std::endl;

  return 0;
}

