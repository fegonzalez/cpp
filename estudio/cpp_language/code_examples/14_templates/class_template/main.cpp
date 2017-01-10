#include "myvector.h"
#include <iostream>
#include <cstdlib> // __func__


void primary_template_test();
void parcial_specialization_test();

int main()
{
  primary_template_test();
  parcial_specialization_test();
  
  return 0;
}

//------------------------------------------------------------------------------

void primary_template_test()
{
  std::cout << "\nFunction: " << __func__ << std::endl;
 
  Vector<int> v6(6);
  std::cout << "\nReading operator[]" << std::endl;
  std::cout << v6 << std::endl;
  std::cout << "\nWriting operator[]";
  v6[0] = 3;
  std::cout << v6 << std::endl;

  //copy ctor
  std::cout << "\nCopy constructor";
  Vector<int> v6_bis = v6;

  //operator=
  std::cout << "\nassignment operator";
  v6_bis = v6;

  // A template never used doesn't need to be defined

  v6.template_used_needs_definition();
}

//------------------------------------------------------------------------------

void parcial_specialization_test()
{
  std::cout << "\nFunction: " << __func__ << std::endl;

  Vector<int> normalv(6);
  Vector<int*> v3(3);
  std::cout << "\nWriting operator[]";
  for (size_t loopi = 0;
       loopi<v3.size();
       ++loopi)
  {
    v3[loopi] = normalv[loopi];
  }
  std::cout << v3 << std::endl;
 
  std::cout << "\nReading operator[]" << std::endl;
  std::cout << v3 << std::endl;
}

//------------------------------------------------------------------------------
