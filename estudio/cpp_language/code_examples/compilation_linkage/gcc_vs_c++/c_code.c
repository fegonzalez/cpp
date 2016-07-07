/*\file c_code.c
  \test Checking the difference between gcc & g++ over a C file.
  

  // compile & link in one step

  gcc c_code.c               // OK

  g++ -x c c_code.c          // OK (compiled as C code)

  g++ c_code.c               // full of errors (compiled as C++ code)


  // compile & link in two separate steps

  gcc -c c_code.c            // 
  gcc c_code.o               // OK

  g++ -x c -c c_code.c       // OK (compiled as C code)
  g++ c_code.o               // OK (linked as C++ code)

  g++ -x c -c c_code.c       // OK (compiled as C code)
  gcc c_code.o               // OK (linked as C code)


  // WARNING '-x c' option is only valid for source code

  g++ -x c -c c_code.c       // OK (compiled as C code); 'c_code.o' created
  g++ -x c c_code.o          // full of errors (-x c only valid for source code)
 
  gcc -c c_code.c            // OK as C
  gcc -x c c_code.o          // full of errors (-x c only valid for source code)

 */

#include <stdlib.h>
#include <stdio.h>
#include "c_code.h"

int main() 
{
  int* new; //warning 'new' used to force C++ errors (as 'new' does
	    //not exists in C)
    int* p = malloc(sizeof(int));

    *p = 42;
    new = p; // 'new' is a reserved word only in C++
    printf("The answer: %d\n", *new);
    free(p);
    p=0;

    printf("const a_c_constant: %d\n", a_c_constant);

    return 0;
}



