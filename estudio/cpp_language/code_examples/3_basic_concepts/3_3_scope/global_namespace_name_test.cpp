/*!\file global_namespace_name_test.cpp

  Test [k33062a]. Check that the name of the global namespace is "::"
 */

#include <iostream>
#include <cassert>

int c = 0; // global variable ::c  

int main()
{
  int c = 1;

  assert(c==1);
  assert(::c==0);
  std::cout << c << std::endl;
  std::cout << ::c << std::endl;

  {
    int c=2;
    assert(c==2);
    assert(::c==0);
    std::cout << c << std::endl;
    std::cout << ::c << std::endl;
    
  }

  std::cout << std::endl;
  return 0;
}
