#include "my_member_template.h"
#include <iostream>
#include <vector>


/*\test [k1403] # 14.3.1 Templates and Implicit Conversions
*/

int main()
{
  //# 14.3.1 Templates and Implicit Conversions
  
  std::vector<int> vi {10};
  std::vector<double> vd;
  //vd = vi;             // compilation error
  
  //std::cout << "\nconst char *maxstr = max(p1,p0) = " << maxstr << std::endl;
  
  
  return 0;
}

