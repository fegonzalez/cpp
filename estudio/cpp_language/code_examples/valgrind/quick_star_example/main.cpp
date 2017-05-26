#include <stdlib.h>

void fnonfree()
{
  int * kk = new int[10];
  kk[0]=5;

  delete [] kk;
  //   kk=0;      // warning: not reset to 0 not detected by memcheck
  delete [] kk;   // ok: (invalid free) detected
 
}


// bad code
void f(void)
{
  int * x= (int*)malloc(10 * sizeof(int)); // C++ code // int* x = malloc(10 * sizeof(int));    // C code
  x[10] = 0;        // problem 1: heap block overrun
                    // problem 2: memory leak -- x not freed
  int undef_value;
  x[0] = undef_value;
  
}                    




// good code
/*
void f(void)
{
  int * x= (int*)malloc(10 * sizeof(int)); // C++ code // int* x = malloc(10 * sizeof(int));    // C code
  x[9] = 0;        // problem 1: heap block overrun
  free(x);
}                    // problem 2: memory leak -- x not freed
*/


int main(void)
{
  f();
  
  fnonfree();
 
  return 0;
}

//==============================================================================

/* EOFILE */
