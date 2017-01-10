/*!\file max6test.cpp

  \test # 14.4.6 Using string literals as Arguments for Function Templates

        14) Consequences in templates: Example: value parameters (T)
*/

#include "max6.hpp"
#include <string>

int main()
{
  std::string s;

  ::max("apple", "peach");  // OK: same type (const char[6])
  ::max("apple", "tomato"); // OK: decays to same type

  //::max("apple", s);        // ERROR: different types
}
