/******************************************************************************/
/*!\test [c8] Default constructor                                             */
/******************************************************************************/


/*!\test 1.- Synthesized default constructor - embedded data members

  What happens if the object have some embedded data members which
don't have a default constructor, but another constructor defined
instead?
*/

/*!\test 2.- Synthesized default constructor - base class

\todo what happens if the object have a base class which don't have a
default constructor, but another constructor defined instead?

*/



/* Default constructor                                                 


# a.1) Synthesized constructor for a class (or struct) 

    The one automatically & implicitly created by C++ iff ...

      	- If there is no user-declared constructor for a class (or struct)

      	- And if the class doesn't contain const or reference data members.

    ... the implementation needs (MUST have) that definition.


- [C++11] "default" declaration/definition [4_7_4]

    Sales() // declaration body
    {
     Sales_data() = default; // here: synthetised & inlined
    }


    // At class definition: synthetised, but not inlined by default
    //
    Sales_data::Sales_data() = default { ...  }


- [C++11] "default" initialization process [4_7_4]

    • If there is an in-class initializer (2.6.1), use it to init the member.

    • Otherwise, default-initialize (2.2.1) - ([3_1] 2.2.1, p. 72) the member.

    WARNING
    Classes that have members of built-in or compound type usually
    should rely on the synthesized default constructor only if all
    such members have in-class initializers.

*******************************************************************************/



#include <iostream>

// forward declarations
class B;
class C;
// class Embedded;

//==============================================================================
// test .- Synthesized default constructor - base class
//==============================================================================

class A
{
public:

  A(int v1): the_v1(v1), the_v2(v1*1.1)
  {
    std::cout << "\n A(int v1) " << std::endl;
  }

protected:
    
  int the_v1;
  float the_v2;
};

//------------------------------------------------------------------------------

class B : public A
{
public:

#ifdef default // [C++11]
  B() = default; // here: synthetised & inlined
#endif
  
  // base class has a non-default constructor: will be the synthesized default
  // constructor created?
  //
  // expected: no (compilation error)
  // obtained; the expected

private:
  char the_char;
};



//==============================================================================
// test .- Synthesized default constructor - base class
//==============================================================================

class Embedded
{
public:
  
  Embedded(int v1): the_v1(v1), the_v2(v1*1.1)
  {
    std::cout << "\n Embedded(int v1) " << std::endl;
  }

protected:
    
  int the_v1;
  float the_v2;
};

//------------------------------------------------------------------------------

class Compound
{
public:

#ifdef default // [C++11]
  Compound() = default; // here: synthetised & inlined
#endif
  
  // embedded data member has a non-default constructor: will be the synthesized
  // default constructor created?
  //
  // expected: no (compilation error)
  // obtained; the expected

private:
  char the_char;
  Embedded the_data;
};

//==============================================================================

int main()
{
  std::cout << "\n test.- Synthesized default constructor & base class "
	    << std::endl;
  /*  B b;
   */
  std::cout << "\n[C++98]: error: no matching function for call to Base::Base()"
	    << std::flush;
  std::cout << "\n[C++11] [C++14]: error: use of deleted function ‘B::B()’"
	    << std::flush;
  std::cout << "\n[C++11] [C++14]: error: ‘B::B()’ is implicitly deleted because the default definition would be ill-formed."
	    << std::flush;
  std::cout << std::endl;   

  std::cout << "\n test.- Synthesized def. constructor - embedded data members"
	    << std::endl;
  /*  Compound();
   */
  std::cout << "\n[C++98]: error: no matching function for call to ‘Embedded::Embedded()’" << std::flush;
  std::cout << "\n[C++11] [C++14]: error: use of deleted function ‘Compound::Compound()’"
	    << std::flush;
  std::cout << "\n[C++11] [C++14]: error: ‘Compound::Compound()’ is implicitly deleted because the default definition would be ill-formed."
	    << std::flush;
  
  std::cout << std::endl;

  
  return 0;
}
