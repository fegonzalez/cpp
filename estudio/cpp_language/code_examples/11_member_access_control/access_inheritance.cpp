#include "access_inheritance.h"
#include <iostream>

void access_inheritance_test()
{
  std::cout << "\n>>> test 11.2 Accessibility of base classes and base class members" << std::endl;

  Pub_Derv d1; // members inherited from Base are public
  Priv_Derv d2; // members inherited from Base are private
  Prot_Derv d3; // members inherited from Base are protected
    
  d1.pub_mem(); // ok: pub_mem is public in the derived class
  //  d2.pub_mem(); // error: pub_mem is private in the derived class
  d2.f(); // ok: public in the derived class
  // d3.pub_mem(); // error: pub_mem is protected in the derived class
  d3.f();

  exempting_individual_members_test();
}

//----------------------------------------------------------------------------*/

void exempting_individual_members_test()
{
  Exempting_Priv_Derv d4;// members inherited from Base are private   ...
  d4.pub_mem(); // ... but using Base::pub_mem provide the access
}

//----------------------------------------------------------------------------*/

