/*!\file lookup_test

 */
#include <iostream>
#include <cassert>

//====================================================================================

// global namespace

//extern int i; // test_point_7_4: 5) global scope, before the definition of N

//====================================================================================

namespace Unqualified_name_lookup
{
  /*!\namespace test_point_3
    \test [k3401]
  */
  namespace test_point_3
  {
    typedef int f;
    namespace N {
      struct A
      {
	friend void f(A &);
	operator int();
	void g(A a)
	{
	  int i = f(a); // f is the typedef, not the friend function:
			// equivalent to int(a)
	  
	  std::cout << "Unqualified_name_lookup::test_point_3::N::A::g::i = " << i
		    << std::endl;
	  
	}
      };//A

      A::operator int(){return 33;}
      
      void f(A & object)
      {
	std::cout << "Unqualified_name_lookup::test_point_3::N::f = "
		  << 2 * int(object) << std::endl;
      }
      
    }//N
  }//test_point_3
  
  //----------------------------------------------------------------------------------

  /*!\namespace test_point_7_4
    \test [k3402]
  */
  namespace test_point_7_4
  {
    namespace M
    {
      class B
      {
      public:
	//int i = 9; //test_point_7_4: 3) scope of N::Y’s base class M::B
	           //
	           // error:invalid use of non-static data member
		   // ‘Unqualified_name_lookup::test_point_7_4::M::B::i’
      };
    }

    namespace N
    {
      // extern int i; // test_point_7_4: 4) scope of namespace N, before
		    // the definition of N::Y
      
      class Y : public M::B
      {
	//int i = 3; // test_point_7_4: 2) scope of class N::Y, 
		   // before the definition of N::Y::X
	           //
	           // error: invalid use of non-static data member
	           // ‘Unqualified_name_lookup::test_point_7_4::N::Y::i’	

	class X
	{
	  int i = 3; // ok: 1) scope of class N::Y::X, BEFORE the use of i

	  int a = i; // just simple than int a[i]

	  // int i = 3; // declaration (Definition) AFTER the use of i:
	             // compilation & linkage ok ...
	             //
	             // ... BUT, bad the init value (3 here) is ignored,
	             // and the default (0) value is assigned to 'a'.

	public:
	  int geta() const {return a;}

	};


	X the_x;

      public:

      	void geta() const
	{
	  std::cout << "Unqualified_name_lookup::test_point_7_4::N::Y::X::a = "
		    << the_x.geta() << std::endl;
	}
	
      };
    }//N
    
    // The following scopes are searched for a declaration of i:
    //
    // 1) scope of class N::Y::X, before the use of i
    // 2) scope of class N::Y, before the definition of N::Y::X
    // 3) scope of N::Y’s base class M::B
    // 4) scope of namespace N, before the definition of N::Y
    // 5) global scope, before the definition of N
    
  }//test_point_7_4
  
}//Unqualified_name_lookup


//====================================================================================

int main()
{
  std::cout << "\nBEGIN 3.4 Name lookup test" << std::endl;

  Unqualified_name_lookup::test_point_3::N::A a1;
  a1.g(a1); // f is the typedef, not the friend function: equivalent to int(a)
  Unqualified_name_lookup::test_point_3::N::f(a1); //calling the friend function


  Unqualified_name_lookup::test_point_7_4::N::Y y1;
  y1.geta();
    
  std::cout << std::endl;
  return 0;
}

