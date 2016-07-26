#include <iostream>
#include <cassert>

/*!\file namespace_scope.cpp 
\test [k3306] 3.3.6 Namespace scope

Its potential scope begins at its point of declaration and ends at the
end of the namespace.
*/
namespace N
{
  int i = 30;
  int g(int a) { return 2*a; }
  int j();
  void q();

  int get_j = j(); // ok: j() already declared (and defined later)

  //  int get_h = h(); // error: h() not declared yet, the point of
		   // declaration of h() is after this statement
}

namespace { int l=1; }

namespace N
{
  int g(char a)	// overloads N::g(int)
  { 
    return l+a;	// l is from unnamed namespace
  }

  //  int i;	// error: duplicate definition
  int j(); 	// OK: duplicate function declaration

  int j()  	// OK: definition of N::j()
  { 
    return g(i);	// calls N::g(int)
  }
    
  //  int q();	        // error: different return type


  int h() {return 77;}  // declaration of h()
  int get_h = h();      // Here: ok: h() declared and defined
	
} //eof namespace N


//------------------------------------------------------------------------------


int main()
{
  std::cout << "\nBEGIN namespace_scope_test" << std::endl;

  std::cout << "N::get_j: " << N::get_j << std::endl;
  std::cout << "N::get_h: " << N::get_h << std::endl;
  
  std::cout << std::endl;
  return 0;
}
