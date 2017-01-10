#ifndef _ADDVAL_HPP_
#define _ADDVAL_HPP_


/*!\file addval.cpp nontype function template parameters example.

  \test [k14105] nontype function template args.

*/

//------------------------------------------------------------------------------

template<typename T, int VAL> //VAL is a value rather than a type
T addValue(const T& x)
{
  return (x + VAL);
}

//------------------------------------------------------------------------------

#endif
