
/*!\test [k8503] Pods

  -  POD (Plain Old Data), or PDS (Passive data structure) class

  a) definition

  The idea of a POD is to capture basically two distinct properties:
  1. It supports static initialization, and
  2. Compiling a POD in C++ gives the same memory layout as struct compiled in C

  Specifies that the type is POD (Plain Old Data) type. This means
  the type is compatible with the types used in the C programming
  language, can be manipulated using C library functions: it can be
  created with std::malloc, it can be copied with std::memmove, etc,
  and can be exchanged with C libraries directly, in its binary form.


  \warning The conditions to be a PODType differs in the different
  versions of C++: 98, 2011, 2014, 2017.

  \warning default compilation:  -std=c++14. Other options:
  make "CPP_STD_FLAGS = " 
  make "CPP_STD_FLAGS = -std=c++11" 
  make "CPP_STD_FLAGS = -std=c++17" 
*/


#include <iostream>
#include <string>
#include <cassert>

#include <type_traits>

void pod_test();
void is_test();

// =============================================================================

void pod_test()
{
  std::cout << "\nTest [k8503] Pods."<< std::endl;


  struct A {
    int m;
  };
 
  struct B {
    int m1;
  private:
    int m2;
  };
 
  struct C {
    virtual void foo();
  };
 
  std::cout << std::boolalpha;
  std::cout << std::is_pod<A>::value << '\n';
  std::cout << std::is_pod<B>::value << '\n';
  std::cout << std::is_pod<C>::value << '\n';
  //  std::cout << std::is_aggregate<C>::value << '\n';
}

// -----------------------------------------------------------------------------

void is_test()
{
    std::cout << "\nvoid is_test()" << std::endl;
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


  /*!\struct derived_from_trivial

    is_standard_layout: false // non-s data members in diff. classes (C++14)
		       	      // base classes with non-s data members (C++11)
  */
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

  std::cout << std::boolalpha;

  std::cout << "\nis_trivial ?" << std::endl;
  std::cout << std::is_trivial<base0>::value << '\n';  
  std::cout << std::is_trivial<base1>::value << '\n';
  std::cout << std::is_trivial<base2>::value << '\n';
  std::cout << std::is_trivial<derived_from_trivial>::value << '\n';
  std::cout << std::is_trivial<derived>::value << '\n';
  // std::cout << "\nis_trivially_copyable ?" << std::endl;  // C++17
  // std::cout << std::is_trivially_copyable<A>::value << '\n';
  // std::cout << std::is_trivially_copyable<base0>::value << '\n';  
  // std::cout << std::is_trivially_copyable<base1>::value << '\n';
  // std::cout << std::is_trivially_copyable<base2>::value << '\n';';
  //std::cout<<std::is_trivially_copyable<derived_from_trivial>::value << '\n';
  // std::cout << std::is_trivially_copyable<derived>::value << '\n';

  std::cout << "\nis_standard_layout ?" << std::endl;
  std::cout << std::is_standard_layout<base0>::value << '\n';  
  std::cout << std::is_standard_layout<base1>::value << '\n';
  std::cout << std::is_standard_layout<base2>::value << '\n';
  std::cout << std::is_standard_layout<derived_from_trivial>::value << '\n';
  std::cout << std::is_standard_layout<derived>::value << '\n';

  std::cout << "\nis_pod ?" << std::endl;
  std::cout << std::is_pod<base0>::value << '\n';  
  std::cout << std::is_pod<base1>::value << '\n';
  std::cout << std::is_pod<base2>::value << '\n';
  std::cout << std::is_pod<derived_from_trivial>::value << '\n';
  std::cout << std::is_pod<derived>::value << '\n';
  std::cout << std::endl;

  //--------------------------------------

  //!\warning valid aggregate in C++14  
  derived d0{}; //ok: default init is valid in C++14
  std::cout
    << d0.b1
    << " " << d0.b2
    // << " " << d0.b3
    << " " << d0.d
    << std::endl;

}

// =============================================================================
      
int main()
{
  /*!\test Aggregates definition in C++14:  */

  pod_test();
  is_test();
  
  std::cout << std::endl;
  return 0;
}
