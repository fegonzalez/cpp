#include "protected.h"
#include <iostream>


void clobber(Sneaky& obj) // ok: can access Sneaky::prot_mem
{
  obj.dummy();
  std::cout << "ok: can access Sneaky::prot_mem = " << obj.prot_mem
	    << std::endl;
}

void clobber(BaseProtectedTest& obj)   // error: can't access Base::prot_mem
{
  obj.dummy();

  std::cout << "error: can't access BaseProtectedTest::prot_mem = "
    //	    << obj.prot_mem
	    << std::endl;

}



void protected_test()
{
  std::cout << "\n>>> test 11.4 Protected member access" << std::endl;

  Sneaky sneak;
  BaseProtectedTest base; 
  
  clobber(sneak); // ok: can access Sneaky::prot_mem
  clobber(base); // error: can't access BaseProtectedTest::prot_mem
}
