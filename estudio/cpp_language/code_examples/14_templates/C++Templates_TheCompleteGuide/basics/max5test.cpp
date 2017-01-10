/*!\file max5test.cpp

  \test # 14.4.6 Using string literals as Arguments for Function Templates

        14) Consequences in templates: Example: reference parameters (T&)
*/


#include "max5.hpp"
#include <string>
#include <iostream>
#include <typeinfo>


int main()
{
  std::string s, s2;

  ::max("apple", "peach");  // OK: same type (const char[6])
					 
  //::max("apple", "tomato"); // ERROR: different types
  //
  //error: no matching function for call to ‘max(const char [6], const char [7])
  
  //::max("apple", s);        // ERROR: different types
  //
  //error: no matching function for call to ‘max(const char [6], std::string&)’

  ::max(s,s2); // OK: same type (std::string)

  ::max<std::string>("apple", "tomato"); // OK: same type (std::string)

}
