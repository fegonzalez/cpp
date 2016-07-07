#include "nested_classes.h"
#include <iostream>

void nested_classes_test()
{
  std::cout << "\n>>> test 11.7 Nested classes" << std::endl;
    
  E eobj;
  eobj.x = 1;
  std::cout << "eobj.x = 1; ? : " << eobj.x
	    << std::endl;

  E::I iobj;
  iobj.f(&eobj, 22);
  std::cout << "eobj.x = 22; ? : " << eobj.x
	    << std::endl;
}


