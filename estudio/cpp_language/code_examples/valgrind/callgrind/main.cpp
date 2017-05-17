#include <stdlib.h>

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
  
  return 0;
}

//==============================================================================

/* EOFILE */
