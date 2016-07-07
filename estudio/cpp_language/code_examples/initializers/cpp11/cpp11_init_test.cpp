/*!\test 8.5.0 Initialiation before C++11 vs Initialiation after C++11

  c++98 initialization

*/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>
#include <sstream>      // std::ostringstream
#include <initializer_list>


//==========================================================================

//!\test initializer-list (sequence) constructor (8.5.4)

template <class T>
struct S {
  std::vector<T> v;

  // (1) std containers or user defined classes, have a constructor
  S(std::initializer_list<T> l) : v(l) {
    std::cout << "constructed with a " << l.size() << "-element list\n";
  }
  void append(std::initializer_list<T> l) {
    v.insert(v.end(), l.begin(), l.end());
  }
  std::pair<const T*, std::size_t> c_arr() const {
    return {&v[0], v.size()};  // copy list-initialization in return statement
    // this is NOT a use of std::initializer_list
  }
};


template <typename T>
void templated_fn(T) {}

//==============================================================================

void cpp98_init();
void cpp11_brace_init();
void cpp11_class_member_init();

void cpp11_initializer_list_test();
void cpp11_stl_initializer_list();
void cpp11_user_defined_initializer_list();
  

//------------------------------------------------------------------------------

void cpp98_init()
{
  std::cout << "\n>> cpp98_init()" << std::endl;

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
  //  std::vector <std::string> vs{"alpha", "beta", "gamma"}; // stl containers
}

//------------------------------------------------------------------------------

void cpp11_brace_init()
{
  std::cout << "\n>> cpp11_brace_init()" << std::endl;


  // # 8.5.0.3 C++11 brace-init [4_5]
  //
  // a) Introducing a UNIVERSAL initialization notation that applies to
  //    every type, whether a POD variable, a class object with a
  //    user-defined constructor, a POD array, a dynamically allocated
  //    array, or even a Standard Library container:

  int a={1}, total{};
  std::string s={"hello"}, s2{s};
  double totald{},
    *pd = new double[3]{0.5, 1.2, 12.99}; // dynamic POD array

 std::vector <std::string> vs{"alpha", "beta", "gamma"}; // stl containers
 std::map<std::string, std::string> stars			
 { {"Superman", "+1 (212) 545-7890"},
     {"Batman", "+1 (212) 545-0987"}};

 class C
 {
   public:
   int x[4]{141,552,553}; //warning, overridden by mem-init at constructors
   public:
   C(): x{0,1,2,3}  // member arrays: mem-init overrides brace-init above
   {std::cout << "C(): x[3]=" << x[3] << std:: endl;}
 };

 C ac; //warning: calling default-constructor
   
 total+=a;
 totald+=*pd;


 // b) Default initialization "{}"
 //   POD types usually means initialization to binary zeros.
 //   non-POD types default initialization means default construction.

 //C++11: default initialization using {}
 int n{}; //zero initialization: n is initialized to 0
 int *p{}; //initialized to nullptr
 double d{}; //initialized to 0.0
 char voidchar[12]{}; //all 12 chars are initialized to '\0'
 std::string s3{}; //same as: string s;
 char *p5=new char [5]{}; // all five chars are initialized to '\0'

 p = &n;
 assert(p);
 total+=(n+*p);
 totald+=d;

 std::cout << "\n Suma total = " << total << std::endl;
 std::cout << "\n s2 = " << s2 << std::endl;
 std::cout << "\n Suma double total = " << totald << std::endl;

 for(std::size_t li= {0}; li<12;++li)
   if( not (voidchar[li]=='\0'))
     std::cout << voidchar[li] << std::endl;

 p5[4] = '4';
 for(std::size_t li=0; li<5;++li)
   if (not (*(p5+li)=='\0'))
     std::cout << *(p5+li) << std::endl;


}

//------------------------------------------------------------------------------

void cpp11_class_member_init()
{
  std::cout << "\n>> cpp11_class_member_init()" << std::endl;

// WARNING
// Regardless of the initialization form used, the compiler conceptually
// transforms every class member initializer into a corresponding mem-init.

  class C
  {
  public:
    C()
    {
      //      p = new char('a');
    }

    std::string print()const
    {
      std::ostringstream out{};
      out << this->s << ";"
	  << this->d << ";"
	  << ( (this->p!= nullptr) ? this->p : "" )<< ";"
	  << this->y[1] << ";"
	  << this->x;
      return out.str();
    }
   
  private:
    std::string s="abc";     //class member initializers ...
    double d=0;
    char * p {nullptr};
    int y[5] {1,2,3,4};
    int x=7;
    
  };//class CC

  C c;
  std::cout << c.print() << std::endl;
}

//==============================================================================

void cpp11_initializer_list_test()
{
  cpp11_stl_initializer_list();
  cpp11_user_defined_initializer_list();
}

//------------------------------------------------------------------------------

/*!\fn cpp11_initializer_list()
  Used to INITIALIZE STL CONTAINERS through a sequence of values. For example:
*/
void cpp11_stl_initializer_list()
{
  std::cout << "\n>> cpp11_stl_initializer_list()" << std::endl;

  std::vector<int> vi {1,2,3,4,5,6};
  std::map<std::string, std::string> stars { {"Superman", "+1 (212) 545-7890"},
      {"Batman", "+1 (212) 545-0987"} };

  std::for_each(vi.begin(), vi.end(),
		[](int &n) {std::cout << n << " " << std::flush;} );
  std::cout << std::endl;

  std::for_each(stars.begin(), stars.end(),
  		[](std::pair<const std::basic_string<char>,
		   std::basic_string<char> > &the_pair)
		{std::cout << the_pair.first << ": "
			   << the_pair.second << "\n" << std::flush;} );
  std::cout << std::endl;
}
 
//------------------------------------------------------------------------------

void cpp11_user_defined_initializer_list()
{
  std::cout << "\n>> cpp11_user_defined_initializer_list()" << std::endl;

  std::cout << "\nTest a2) a braced-init-list is used in list-initialization"
	    << std::endl;  
  S<int> s = {1, 2, 3, 4, 5}; // (2) copy list-initialization
  std::cout << "The vector size is now " << s.c_arr().second << " ints:\n";
  s.append({6, 7, 8});      // list-initialization in function call
  std::cout << "The vector size is now " << s.c_arr().second << " ints:\n";


  std::cout << "\nTest a1) a braced-init-list is bound to auto, "
	    << " including in a ranged for loop:"
	    << std::endl;  
  for (auto n : s.v)
    std::cout << n << ' ';
  std::cout << '\n';
  
  std::cout << "Range-for over brace-init-list: \n";
  for (int x : {-1, -2, -3}) // the rule for auto makes this ranged-for work
    std::cout << x << ' ';
  std::cout << '\n';

  auto al = {10, 11, 12};   // special rule for auto 
  std::cout << "The list bound to auto has size() = " << al.size() << '\n';
  
  //templated_fn({1, 2, 3}); // error: "{1, 2, 3}" is not an expression,
                             // it has no type, and so T cannot be deduced

  templated_fn<std::initializer_list<int>>({1, 2, 3}); // OK
  templated_fn<std::vector<int>>({1, 2, 3});           // also OK  
  
}

//==============================================================================

int main()
{
  cpp98_init();
  cpp11_brace_init();
  cpp11_class_member_init();
  cpp11_initializer_list_test();
  std::cout << std::endl;
  return 0;
}
