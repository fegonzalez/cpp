#include <iostream>

int main() {

  int result=0, newval=0;

  const std::string ASK_MSG = "\nEnter integer value; end-of-file to finish (Unix: control-d / Win: control-z) ?";

  std::cout << ASK_MSG << std::endl;
  while(std::cin >> newval){
    result+=newval;
    std::cout << "newval = " << newval
	      << " ; result = " << result << std::endl;
    std::cout << ASK_MSG << std::endl;
  }
  
  return 0;
}
