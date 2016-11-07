/*!\test [k6] Converting vs explicit constructors - "./explicit_constructor"

  \test Converting Constructors

  \test Explicit Constructors

*/

#include <iostream>
//#include <cassert>
#include <string>

/***************************************************************************/

/*!\test Converting Constructors 


WARNING
The program is well-formed (compiles) only if there exists (zero or) ONE 
unambiguous implicit conversion sequence from T1 to T2.


 */

/*!\test Explicit Constructors */

/***************************************************************************/

struct A
{
  A()             // converting constructor (since C++11)  
  {
    std::cout << "A::A() " << std::endl;
  } 

  A(std::string) // converting constructor
  {
    std::cout << "A::A(std::string): " << std::endl;
  }

  A(int)          // converting constructor
  {
    std::cout << "A::A(int) " << std::endl;
  }
  
  A(int, int)     // converting constructor (since C++11)
  {
    std::cout << "A::A(int, int) " << std::endl;
  }
  
  A(const A&)
  {
    std::cout << "A::A(const A&): " << std::endl;
  }

  A& operator=(const A&)
  {
    std::cout << "A& A::operator=(const A&) " << std::endl;
    return *this;
  }  
  
  
private:

  int value;
};


void seta(const A&)
{
  std::cout << "void seta(const A&) " << std::endl;
}


/*  WARNING The compiler can not perform an implicit conversion for
    a non-const reference because it can't be temporary, (it has no
    sense):
*/
void seta_noconst(A&)
{
  std::cout << "void seta(A&) " << std::endl;
}


/******************************************************************************/
/* struct B */
/******************************************************************************/

struct B
{
  explicit B()            // converting constructor (since C++11)  
  {
    std::cout << "B::B() " << std::endl;
  } 

  explicit B(int)          // converting constructor
  {
    std::cout << "B::B(int) " << std::endl;
  }
  
  explicit B(int, int)     // converting constructor (since C++11)
  {
    std::cout << "B::B(int, int) " << std::endl;
  }

  explicit B(std::string) // converting constructor
  {
    std::cout << "B::B(std::string): " << std::endl;
  }
  
  //explicit
  B(const B&)
  {
    std::cout << "B::B(const B&): " << std::endl;
  }

  B& operator=(const B&)
  {
    std::cout << "B& B::operator=(const B&) " << std::endl;
    return *this;
  }  
  
  
private:

  int value;
};


void setb(const B&)
{
  std::cout << "void setb(const B&) " << std::endl;
}

void setb_noconst(B&)
{
  std::cout << "void setb(B&) " << std::endl;
}



  

void implicit_test()
{
  std::string sa {"literal"};
  A a1 = 1;      // OK: copy-initialization selects A::A(int)
  A a2(2);       // OK: direct-initialization selects A::A(int)
  A a3{4, 5};    // OK: direct-list-initialization selects A::A(int, int)
  A a4 = {4, 5}; // OK: copy-list-initialization selects A::A(int, int)
  A a5 = (A)1;   // OK: explicit cast performs static_cast, direct-init A::A(in 
  A a8(sa);// OK: direct-initialization selects A::A(string)
  A a9("literal");  // OK: direct-initialization selects A::A(string)
  A a10 = sa;//OK: copy-initialization  selects A::A(string)
  //A a11 = "literal"; // error: invalid conversion <= ONLY one implicit
		       // conversion allowed, two required char[] => string => A
  A a12(a1);     // OK: copy constructor
  a12 = a1;      // OK: operator=(): A => A : none implicit conversion required


  std::cout << "\na12 = std::string" << std::endl;
  //OK: operator=() accepts one implicit conversion:  string => A
  // 1st call: operator=()
  //
  // 2nd call: inside operator=(), before execute the function body,
  //           the compiler executes an implicit conversion to create
  //           a temporary A by calling A::A(std::string): 
  a12 = sa; // OK: operator=() accepts one implicit conversion:  string => A

  
  //a12 = "literal"; // error: invalid user-defined conversion
		     //        ONLY one implicit conversion allowed

  
  std::cout << "\nseta(string)" << std::endl;
  seta(sa); //OK: one implicit conversion (string => A) to make the temporary A

  std::cout << "\nseta({1,2})" << std::endl;  
  seta({1,2}); // OK: one implicit conversion: A::A(int, int) 

  std::cout << "\nseta(\"literal\")" << std::endl;
  //seta("literal"); //error: ONLY one implicit conversion allowed, two required
  std::cout << "error: ONLY one implicit conversion allowed, two required."
	    << std::endl;
  std::cout << std::endl;

  
  std::cout << "error: The compiler can not perform an implicit conversion"
	    << " for a non-const reference because it can't be temporary, "
	    << "(it has no sense)."
	    << std::endl;
  seta_noconst(a1); // ok: zero implicit conversions
  //seta_noconst(sa); // error: one implicit conversion required.
  std::cout << std::endl;

    
  // note.- just to avoid warnings
  std::cout << "\nnote.- just to avoid warnings" << std::endl;
  
  a4 = a3; // OK: operator=
  a5 = a4; // OK: operator=
  a10 = a1; // OK: operator=
  std::cout << std::endl;
}
 
void explicit_test()
{
  std::cout << "\n\n EXPLICIT \n" << std::endl;
    
  std::string sb {"literal"};
  //  B b1 = 1;      // error: copy-initialization does not consider B::B(int)
  B b2(2);           // OK: direct-initialization selects B::B(int)
  B b3{4, 5};        // OK: direct-list-initialization selects B::B(int, int)
  // B b4 = { 4, 5}; // error: copy-list-initialization selected an
                     // explicit constructor B::B(int, int)

  std::cout << "\nB b5 = (B)1" << std::endl;
  B b5 = (B)1;       // OK: explicit cast, direct-init: B::B(int) 
  
                     // default construction cases
  B b6;              // OK, default-initialization selects B::B()
  B b7{};            // OK, direct-list-initialization selects B::B()
  // B b8 = {};      // error: copy-list-initialization selected
                     // an explicit constructor B::B()
  
  B b8(sb);          // OK: direct-initialization selects B::B(string)
  B b9("literal");   // OK: direct-initialization selects B::B(string)

  //B b10 = sb;   // error: copy-initialization does not consider B::B(string)
  //B b11 = "literal"; // error: invalid conversion
  B b12(b2);     // OK: copy constructor
  b12 = b2;      // OK: operator=(): B => B : none implicit conversion required
  //b12 = sb;      // error: no match for ‘operator=’
  //b12 = "literal"; // error: no match for ‘operator=’

  
  std::cout << "\nsetb(B)" << std::endl;
  setb(b2); // ok: direct init
  std::cout << "\nsetb(string)" << std::endl;
  //setb(sb); // error: explicit constructor doesn't allow implicit conversions
  std::cout << "\nsetb({1,2})" << std::endl;  
  //setb({1,2}); // error: explicit constructor doesn't allow implicit convers.

  std::cout << "error: The compiler can not perform an implicit conversion"
	    << " for a non-const reference because it can't be temporary, "
	    << "(it has no sense)."
	    << std::endl;
  setb_noconst(b2); // ok: zero implicit conversions
  //setb_noconst(sb); // error: one implicit conversion required.
  std::cout << std::endl;

  
  // note.- just to avoid warnings
  std::cout << "\nnote.- just to avoid warnings" << std::endl;
  b3 = b2;
  b3 = b5;
  // b6 = b2;
  // b7 = b2;
  
}

//------------------------------------------------------------------------------

int main()
{
  implicit_test();
  explicit_test();
}
