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
  std::cout << v6_bis << std::endl;
  
  //operator=
  std::cout << "\nassignment operator";
  v6_bis = v6;
  std::cout << v6_bis << std::endl;
  
  // A template never used doesn't need to be defined
  v6.template_used_needs_definition();
  //v6.template_never_used_doesneed_definition(); //error: not defined
}

//------------------------------------------------------------------------------

void parcial_specialization_test()
{
  std::cout << std::endl;
  std::cout << "\nFunction: " << __func__ << std::endl;

  Vector<int> aux_normalv(4);

  aux_normalv[0]= 11;
  aux_normalv[1]= 3;
  aux_normalv[3]= 1000;
  std::cout << aux_normalv << std::endl;
  
  Vector<int*> v3(3);
  std::cout << v3 << std::endl;

  std::cout << "\nWriting operator[]";
  
  for (size_t loopi = 0;
       (loopi<v3.size() and loopi<aux_normalv.size());
       ++loopi)
  {
    v3[loopi] = aux_normalv[loopi];
  }
  std::cout << "\nReading operator[]" << std::endl;
  std::cout << aux_normalv << std::endl;
  std::cout << v3 << std::endl;
 
  // copy ctor
  std::cout << "\n<T*> Copy constructor";
  Vector<int*> v3_bis = v3;
  std::cout << v3_bis << std::endl;
 
  //operator=
  std::cout << "\n<T*> assignment operator";
  v3_bis = v3;
  std::cout << v3_bis << std::endl;

  Vector<int*> v5(5);
  std::cout << v5 << std::endl;
  assert(v5.size()==5);
  v5 = v3;
  std::cout << v5 << std::endl;
  assert(v5.size()==3);
  

  // A template never used doesn't need to be defined
  v3_bis.template_used_needs_definition();
  //v3_bis.template_never_used_doesneed_definition(); //error: not defined

  std::cout << std::endl;
}

//------------------------------------------------------------------------------
