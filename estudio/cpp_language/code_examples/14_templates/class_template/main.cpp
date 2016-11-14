#include "myvector.h"
#include <iostream>

int main()
{
  Vector<int> v6(6);
  std::cout << "\nReading operator[]" << std::endl;
  std::cout << v6 << std::endl;
  std::cout << "\nWriting operator[]";
  v6[0] = 3;
  std::cout << v6 << std::endl;

  //copy ctor
  Vector<int> v6_bis = v6;

  //operator=
  v6_bis = v6;

  // A template never used doesn't need to be defined

  v6.template_used_needs_definition();
  
  return 0;
}

