/*!\file case2.cpp 

Test [k3310]:

C++ standard, chapter 3.3.10 Name hiding,

2) A class name (9.1) or enumeration name (7.2) can be hidden by the
   name of a variable, data member, function, or enumerator declared
   in the same scope. The declaration order doesn't matters.

*/

#include <iostream>
#include <cassert>

double color = 33.33; //declared before the hidden name

enum color //color is an enumeration name   
  { red = 1, blue = 2 };

class clase // clase is a class name
{
};


void clase() //declared after the hidden name
{
  std::cout << "\n(class clase hidden): void clase()" << std::endl;
}



int main()
{  
  std::cout << "\n(enum color hidden): color = " << color << std::endl;
  clase();

  std::cout << std::endl;  
}

