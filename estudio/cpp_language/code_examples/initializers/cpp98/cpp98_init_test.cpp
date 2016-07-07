/*!\test 8.5.0 Initialiation before C++11 vs Initialiation after C++11

  c++98 initialization

*/

#include <iostream>
#include <vector>


int main()
{


  // not_1) Initialization of fundamental types: // 

 int n = 0, total(0);         /* (1)  obj = value  OR  obj(value)  */ 

 total+=n;

 // not_2) Initialization of data members in a class and objects

 struct S
 {
   explicit S(int n, int m) : a(n), b(m){}   /* (2)  mem-init */ 
   int suma()const{return a+b;}
 private:
   int a, b;
 };
 S s(0,1);   /* (3)  object initializers enclosed in parentheses */
 // S s={0,1};  /* (4)  compilation error */
 total+=s.suma();


 // not_3) Initialization of aggregates (arrays / structs / string literals)
 // Agregate init. requires braces '{}' ...

  int c1[2]={0,2};       /* (5) arrays */    
 struct SS { int a,b; };
 SS ss={0,1};             /* (6) structs  */

 total+=c1[1];
 total+=ss.a;
 total+=ss.b;
 
 // ... with the exception of string literals:
 char c2[]="message";                           /* (7) string literals */
 char c3[]={'m','e','s','s','a','g','e','\0'};  /* (8) string literals*/

 std::cout << "\n Suma total = " << total << std::endl;
 std::cout << "\n"<< c2[2] << std::endl;
 std::cout << "\n" << c3[5] << std::endl;

 // warning: extended initializer lists only available with
 // -std=c++11 or -std=gnu++11
 // error: in C++98 ‘vs’ must be initialized by constructor, not by ‘{...}’
 // std::vector <std::string> vs{"alpha", "beta", "gamma"}; // stl containers

  
 std::cout << std::endl;
 return 0;
}
