#ifndef MY_FUNCTION_H_
#define MY_FUNCTION_H_

/*\file my_fuynction.h

  \brief C++ Template study. c++.howto, chaper 14.1
*/

#include <cstring>

  template <typename T> 
  inline const T& max (const T &t1, const T &t2) // DEFINITION in a header file
  {
    return (t1>t2) ? t1 : t2;
  }


// overloading max()
  inline const char* & max(const char* & t1, const char* & t2)
  {
    int val = std::strcmp(t1,t2);
    if (val>0) return t1; else return t2;  
  }

#endif
