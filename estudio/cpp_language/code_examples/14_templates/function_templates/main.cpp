#include "myfunction.h"
#include <iostream>

int main()
{
  double d1 = max (2.3, 4.5);  // implicit deduction: double(double, double)
  std::cout << "\n max (2.3, 4.5) = " << d1 << std::endl;
  char cmx = max('0', '8');    // implicit deduction:  char max(char, char)
  std::cout << "\n max('0', '8') = " << cmx << std::endl;

  //cmx=max(6,'8'); // error: no matching function for call to ‘max(int, char)’

  int nmx = max<int>(false, 5.6); //Explicit deduction
  std::cout << "\n max<int>(false, 5.6) = " << nmx << std::endl;

  // max<double>(false, &d1); //error: no matching function for call to
			   //‘max(bool, double*)’
  

  //!\test # 14.2.2 Overloading and Partial Specialization

  const char *p1 = "string1";
  const char *p0 = "string0";
  // const char *maxstr = max(p1, p0); //error: pointer comparison;
  // 				    //lexicographical comparison required

  //After const char * max(const char * t1, const char * t2) definition:
  const char *maxstr = max(p1, p0);
  std::cout << "\nconst char *maxstr = max(p1,p0) = " << maxstr << std::endl;
  
  
  return 0;
}

