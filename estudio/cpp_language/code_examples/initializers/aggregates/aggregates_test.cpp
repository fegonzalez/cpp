
/*!\test [c6] Aggregate Classes in C++14

  \warning The conditions to be an "aggregate type" differs in the
  different versions of C++: 98, 2011, 2014, 2017.

  \warning default compilation:  -std=c++14. Other options:
  make "CPP_STD_FLAGS = " 
  make "CPP_STD_FLAGS = -std=c++11" 
  make "CPP_STD_FLAGS = -std=c++17" 

  Note.- Tests were default made for c++14 only. Aggregates already
  exists since c++98, but with different definition.

  \doc [4_6_5] Aggregate initialization -
  http://en.cppreference.com/w/cpp/language/aggregate_initialization
*/


#include <iostream>
#include <string>
#include <array>
#include <cassert>
#include <type_traits>

// -----------------------------------------------------------------------------

void inheritance_example();
void aggregate_init_example();
void aggregates_including_non_aggregates();
void example_from_4_6_5();

// -----------------------------------------------------------------------------

/*!\test Aggregate class definition in C++14: 

  -std=c++14 or -std=gnu++14

*/



// -----------------------------------------------------------------------------
  
// -----------------------------------------------------------------------------

struct AggregateBase{
public:
  // AggregateBase() {} //error: inherited user-defined constructor disables
  // 		//aggregate type at Data14

  AggregateBase() = default;   // ok: not defined by the user
  int k;
};
  

// class Data14 //error: 'class' disables aggregate type
struct Data14 // C++14 aggregate class

//  : protected AggregateBase //error: disables aggregate type

/*!\warning not accepted by my compiler: g++ (Debian 4.9.2-10) 4.9.2
  for initialization other than default init: Data14{} is the only valid.
*/
// : public AggregateBase
{
  friend std::ostream &operator<<(std::ostream & out, const Data14 & src);//ok

  // Data14() {} //error: user-defined constructor disables aggregate type  
  Data14() = default;   // ok: not defined by the user
  int i;
  static int si;       // ok: static not considered a member to init
  int :17;             // ok: anonymous bit-field not considered a member
  int j;

  // virtual void f() {} //error: disables aggregate type, and then
  // 		         //produces an error upon braced list (Data14 v1 = {0})

  // private:
  // int private_non_static_member; //error: private or protected
  //non-static data members disables
  //aggregate type
};

std::ostream &operator<<(std::ostream & out, const Data14 & src)
{
  out << "(" << src.i << ", "
      << src.j << ")";
  return out;
}

//------------------------------------------------------------------------------

void inheritance_example()
{
  std::cout << "\nvoid inheritance_example()" << std::endl;
  //--------------------------------------

  // aggregate
  struct base0 { int b01, b02; };
  
  struct base1 { int b1, b2 = 42; }; // b=42 => copy constructor => not trivial

  // non-aggregate
  struct base2
  {
    base2() : b3(42) {} // user-defined constructor
    int b3;
  };

  struct derived_from_trivial
  : base0
  { int dft; };


  //!\warning valid aggregate in C++14 / C++17  
  struct derived
    //!\warning derivation, causes is_standard_layout == false
    :
    base1 // public derivation from an aggregate
  //  , base2 // public derivation from a non-aggregate: error (until C++17?)
  { int d; };

  //--------------------------------------

  //!\warning valid aggregate in C++14  
  derived d0{}; //ok: default init is valid in C++14
  std::cout
    << d0.b1
    << " " << d0.b2
    // << " " << d0.b3
    << " " << d0.d
    << std::endl;

  /*!\error not accepted by my compiler: g++ (Debian 4.9.2-10) 4.9.2

  //  derived d1{ {1, 2}, { }, 4}; // d1.b1 = 1, d1.b2 = 2,  d1.b3 = 42, d1.d=4

    error: no matching function for call to ‘derived::derived(<brace-enclosed initializer list>)’
    derived d1 {{1, 2}, {}, 4};
    ^

  //derived d2{ {    }, { }, 4}; // d2.b1 = 0, d2.b2 = 42, d2.b3 = 42, d2.d=4 
    */

  
}

// -----------------------------------------------------------------------------

void aggregate_init_example()
{
  /*
  Data14 v1 = {0, 1};     // ok: complete initialization of aggr. class
                          // i = 0; j = 1
  std::cout << v1 << std::endl;

  Data14 v2 = {0};        // ok: j = int{}, that is, j = 0
  std::cout << v2 << std::endl;

  // Data14 v3 = {0, 1, 3};  // error: too many elements

  Data14 v4 = {};        // ok: i, j = int{}, that is, i = 0, j = 0
  std::cout << v4 << std::endl;
  */
}

// -----------------------------------------------------------------------------

/*!\warning [4_6_5] An aggregate class or array may include
  non-aggregate members, elements, and public bases (since C++17).
*/
void aggregates_including_non_aggregates()
{
  class Inner1 
  {
  public:
    Inner1(int i=0):i(i){} // user-defined constructor
    int operator()()const {return i;}
  private:
    int i; // private non-stataic member
  };
    
  class Data14_2
  {
  public:
    int i;
    Inner1 in;  // ok 
  };

  Data14_2 v1 {10, 12};     // ok: complete initialization of aggr. class
  std::cout << v1.i << " " << v1.in()
	    << std::endl;
}

// =============================================================================

void example_from_4_6_5()
{
  struct S {
    int x;
    struct Foo {
      int i;
      int j;
      int a[3];
    } b;
  };
 
  union U {
    int a;
    const char* b;
  };


  /*!\test brace elision
     Expected: error until C++14.
     Obtained: ok in C++11.
  */
  S s1 = { 1, { 2, 3, {4, 5, 6} } };
  S s2 = { 1, 2, 3, 4, 5, 6};   // same, but with brace elision
  assert((s1.x==s2.x) and
	 (s1.b.i==s2.b.i) and (s1.b.j==s2.b.j)
	 and (s1.b.a[0]==s2.b.a[0])
	 and (s1.b.a[1]==s2.b.a[1])
	 and (s1.b.a[2]==s2.b.a[2]) );

  S s3{1, {2, 3, {4, 5, 6} } }; // same, using direct-list-initialization syntax
  S s4{1, 2, 3, 4, 5, 6};       // error in C++11: brace-elision only
				// allowed with equals sign
  assert((s3.x==s4.x) and
	 (s3.b.i==s4.b.i) and (s3.b.j==s4.b.j)
	 and (s3.b.a[0]==s4.b.a[0])
	 and (s3.b.a[1]==s4.b.a[1])
	 and (s3.b.a[2]==s4.b.a[2]) );
  
  // okay in C++14
  int ar[] = {1,2,3}; // ar is int[3]
  std::cout << "\nsizeof(ar) = " << sizeof(ar) << std::endl;
  //  char cr[3] = {'a', 'b', 'c', 'd'}; // too many initializer clauses
  char cr[3] = {'a'}; // array initialized as {'a', '\0', '\0'}
  std::cout << cr << std::endl; 
  int ar2d1[2][2] = {{1, 2}, {3, 4}}; // fully-braced 2D array: {1, 2} {3, 4}
  int ar2d2[2][2] = {1, 2, 3, 4}; // brace elision: {1, 2} {3, 4}
  int ar2d3[2][2] = {{1}, {2}};   // only first column: {1, 0} {2, 0}
  std::cout << ar2d1[0][0] << std::endl;
  std::cout << ar2d2[0][0] << std::endl;
  std::cout << ar2d3[0][0] << std::endl;
  std::cout << ar2d3[0][1] << std::endl;
  std::cout << ar2d3[1][0] << std::endl;
  std::cout << ar2d3[1][1] << std::endl;

  std::cout << "\nstd::array is an aggregate" << std::endl;
  std::array<int, 3> std_ar2{ {1,2,3} };    // std::array is an aggregate
  std::array<int, 3> std_ar1 = {1, 2, 3}; // brace-elision okay
  std::cout << std_ar1[0] << std::endl;
  std::cout << std_ar2[0] << std::endl;

  std::cout << "\nnarrowing conversion: error since C++11" << std::endl;
  //int ai[] = { 1, 2.0 }; // narrowing conversion from double to int:
                            // error SINCE C++11, okay in C++03

  
  std::string ars[] = {std::string("one"), // copy-initialization
		       "two",          // conversion, then copy-initialization
		       {'t', 'h', 'r', 'e', 'e'} }; // list-initialization

  std::cout << *ars << std::endl;
  std::cout << *(ars+1) << std::endl;
  std::cout << *(ars+2) << std::endl;
  U u1 = {1}; // OK, first member of the union
  std::cout << u1.a << std::endl;
  //    U u2 = { 0, "asdf" }; // error: too many initializers for union
  //    U u3 = { "asdf" }; // error: invalid conversion to int

}

// =============================================================================
      
int main()
{
  /*!\test Aggregates definition in C++14:  */
  std::cout << "\n[k] Aggregates in C++14"<< std::endl;

  inheritance_example();
  aggregate_init_example();
  aggregates_including_non_aggregates();
  example_from_4_6_5();
  
  std::cout << std::endl;
  return 0;
}
