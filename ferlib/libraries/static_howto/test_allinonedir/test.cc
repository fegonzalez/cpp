/* test example: using the library */


#include "foo.h"     // lib. header
#include "foo2.h"    // lib. header

#include <iostream>  // any other headers

 
int main(void)
{
    std::cout << "This is a shared library test..." << std::endl;
    foo();
    foo2();
    return 0;
}
