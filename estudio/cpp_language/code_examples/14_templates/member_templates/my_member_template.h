#ifndef MYFUNCTION_H_
#define MYFUNCTION_H_

/*\file my_member_template.h

  \brief C++ Template study. c++.howto, chaper 14.

  \test [k1403] # 14.3.1 Templates and Implicit Conversions
*/

#include <cassert>
#include <cstring>
#include <iostream>

template <class T> 
const T& max (const T &t1, const T &t2) // DEFINITION in a header filex  
{
  return (t1>t2) ? t1 : t2;
}

// 14.2.2 Overloading

const char * max(const char * t1, const char * t2)
{
  std::cout << "\nUSING: const char * max" << std::endl;
  assert(t1 and t2);
  int val = std::strcmp(t1,t2);
  if (val>0)
    return t1;
  else
    return t2;  
}

#endif
