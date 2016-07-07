#include "refs_lib.h"

#include <iostream>


//-----------------------------------------------------------------------------

void ftest1_ref_as_fnparam(T& obj)
{
  std::cout << "\nftest1_ref_as_fnparam(T& obj)"
	    << "\ninitial obj value = << obj" << std::endl;

  obj++;
  
  std::cout << "final obj value = " << obj << std::endl;
}

//-----------------------------------------------------------------------------

/*!\fn T& return_ref();

  \brief Function returning a NON-LOCAL memory reference.
*/
// T& ftest2_return_nonlocal_ref()
// {

//   return &nonlocal_var;
// }
 
//-----------------------------------------------------------------------------

/*!\fn T& ftest2_return_local_ref();

  \brief Function returning a LOCAL-VAR memory reference.

  \error: COMPILATION WARNING: warning: reference to local variable
  ‘local_obj’ returned
  
*/
/*
T& ftest2_return_local_ref()
{
  T local_obj = 4;
  
  return local_obj;
}
*/

//-----------------------------------------------------------------------------
 
 
 
 
 
