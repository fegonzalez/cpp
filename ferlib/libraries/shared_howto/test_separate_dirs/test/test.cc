/* test example: using the library */

#include <iostream>
#include "../include/foo.h"
 
int main(void)
{
    std::cout << "This is a shared library test..." << std::endl;
    foo();
    return 0;
}
