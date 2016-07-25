#include <iostream>
#include <cassert>

int b;
int a=1;		// (a_1)

void f()
{
  int a=2;		// (a_2) the other 'a' is hidden inside the function f()
  b = a;   	  	// Here: b = (a_2) == 2
  assert(b==2);
}			// (a_1) is visible again


int main()
{  
  b = a; 		// Here: b = (a_1) == 1
  assert(b==1);
  std::cout << b << std::endl;
  f();
  assert(b==2);
  std::cout << b << std::endl;
  b = a; 		// Here: b = (a_1) == 1
  assert(b==1);
  std::cout << b << std::endl;
}

