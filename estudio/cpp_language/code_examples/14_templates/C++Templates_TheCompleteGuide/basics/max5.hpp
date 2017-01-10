/*!\file max5.hpp

  \test # 14.4.6 Using string literals as Arguments for Function Templates

        14) Consequences in templates: Example: reference parameters (T&)
*/


#include <string>
#include <iostream>
#include <typeinfo>

template <typename T>
inline const T& max(const T& a, const T& b)
{
  std::cout << "\ntypedid(a): " << typeid(a).name()
	    << "\ttypedid(b): " << typeid(b).name()
	    << std::endl;
  return a < b ? b : a; 
};
