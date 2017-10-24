
#include <iostream>
#include <cstdlib> // __func__


void const_cast_test();


int main()
{
  const_cast_test();
 
  
  return 0;
}

//------------------------------------------------------------------------------

void const_cast_test()
{
  std::cout << "\nFunction: " << __func__ << std::endl;
}
