/*\file basic io_example.cpp
 */

#include <iostream>
#include <sstream>

int main()
{
  std::cout << "Enter two (integer) numbers:" << std::endl;
  int v1 = 0, v2 = 0;
  std::cin >> v1 >> v2; // first v1, then v2
  std::cout << "The sum of " << v1 << " and " << v2
	    << " is " << v1 + v2 << std::endl;

  std::cout << "Input from stream:" << std::endl;
  std::istringstream iss("9 24");
  iss >> v1 >> v2;
  std::cout << "The sum of " << v1 << " and " << v2
	    << " is " << v1 + v2 << std::endl;

  return 0;
}
