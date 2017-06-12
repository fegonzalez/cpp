#include <iostream>
#include <cmath>

// >>which valgrind
// /usr/bin/valgrind
//#include <valgrind/callgrind.h> //main.cpp:6:32: fatal error: valgrind/callgrind.h: No such file or directory

//==============================================================================

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


int doble_primo(int x)
{
  int retval =  0;
  for(int j=x+1; j<10000; ++j)
    if (isPrime(x))              // another caller to isPrime
      {
	retval = j;
	break;
      }

  return retval;
}


//==============================================================================

int main()
{
  int primeCount = 0;
  int doble_count =0;
  for (int i = 0; i < 1000000; ++i)
    {
      if (isPrime(i))
	{
	  // CALLGRIND_START_INSTRUMENTATION;
          ++primeCount;
	  doble_count+=doble_primo(i);
	  // CALLGRIND_STOP_INSTRUMENTATION;
	}
    }
  std::cout << primeCount << " ; " << doble_count << std::endl;
}
 
//==============================================================================

/*  EOFILE  */
