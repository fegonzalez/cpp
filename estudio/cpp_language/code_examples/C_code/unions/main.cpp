
/*!\test Empty unions ara valid?


  The standard sya YES "at most one" 
*/



#include <iostream>



/*******************************************************************************
 PROBLEM code
*******************************************************************************/

union VoidUnion
{
  int get_dummy(){return 1;}
};

union NonVoid
{
  int i;
  char c;
};

/******************************************************************************/



int main()
{
  std::cout << "\n Test: Empty UNIONS ara valid? (expected = YES)" 
	    << std::flush;

  std::cout << std::endl;
  NonVoid nv1;
  nv1.i=7;
  std::cout << nv1.i << std::endl;
  std::cout << nv1.c << std::endl;
  nv1.c='a';
  std::cout << nv1.i << std::endl;
  std::cout << nv1.c << std::endl;

  VoidUnion vvuu;
  std::cout << vvuu.get_dummy() << std::endl;
  
  return 0;
}


