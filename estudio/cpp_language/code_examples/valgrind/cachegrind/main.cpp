#include <iostream>
#include <cmath>



/*!\todo  Test One object 

>< lscpu
L1d cache:             32K
L1i cache:             32K
L2 cache:              256K
L3 cache:              3072K


sizeof(Tipo1) ??
sizeof(TestAllLocal) ??
sizeof(TestAllPointers) ??
  

  class TestAllLocal
  {

     private:

     int the_int;
     double the_double;
     char the_char;
     Tipo1 the_tipo1;
  }

  Vs


  class TestAllPointers
  {
  
     private:

     int *the_int;
     double *the_double;
     char *the_char;
     Tipo1 *the_tipo1;
  }


  \todo to be def:  Struct Tipo1: una struct grande

  i.e struct Tipo1 {

  int the_int_array[1024]; // 16K ?? 
  double the_double_array2014[256]; // 8K ?  (32bits/double * 256 double)
  
  };

 */









//==============================================================================
/*
bool isPrime(int x)
{
  int limit = std::sqrt(x);
  for (int i = 2; i <= limit; ++i)
  {
    if (x % i == 0)
    {
      return false;
    }
  }
  return true;
}
 
//==============================================================================

int main()
{
  int primeCount = 0;
  for (int i = 0; i < 1000000; ++i)
  {
    if (isPrime(i))
    {
      ++primeCount;
    }
  }
}
*/
//==============================================================================

/*  EOFILE  */
