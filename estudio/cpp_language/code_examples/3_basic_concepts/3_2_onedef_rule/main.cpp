
#include "other_source.h"

#include <iostream>



/******************************************************************************/
/*!\test 3.2 One-definition rule

RULE1	No program shall contain more than one DEFINITION of any...

\test a) non-static global variables
\test c) Static data members


RULE1_EXCEPTION This rule does not apply to entities with internal
		linkage (3.5.2)

\test d-b1) (explicitly declared) static names

\test d-b2) a variable of non-volatile const-qualified type that is
       neither explicitly declared extern nor previously declared to
       have external linkage:

       (non-extern) (non-volatile) const ...

*/
/******************************************************************************/

/*!\test a-ii) non-static global variables

   global variable "int one_per_program_non_static_global_var" defined
   twice in the program: main.cpp, other_source.cpp

   expected: compilation error: multiple definitions of
   `one_per_program_non_static_global_var'

   obtained: the expected
*/
int one_per_program_non_static_global_var = 1;



/*!\test c) Static data members

   data_member `classone::one_per_program_static_data_member "int
   one_per_program_non_static_global_var' defined twice in the
   program: main.cpp, other_source.cpp

   expected: compilation error multiple definitions of
   `classone::one_per_program_static_data_member'

   obtained: the expected 
*/
int classone::one_per_program_static_data_member = 1;



/*!\test d-b1) (explicitly declared) static names

       (including the global namespace)
 */
static int counter = 2; // unrelated to other translation units
namespace n1
{
  static int counter = 2222; // unrelated to other translation units
}

/*!\test d-b2) a variable of non-volatile const-qualified type that is
       neither explicitly declared extern nor previously declared to
       have external linkage:

       (non-extern) (non-volatile) const ...
*/
const int const_counter = 0; // ok: unrelated to other translation units


void test_rule1()
{
  std::cout << "\none_per_program_non_static_global_var = "
	    << one_per_program_non_static_global_var;

  std::cout << "\nclassone::one_per_program_static_data_member = "
	    << classone::one_per_program_static_data_member;

  std::cout << "\nstatic counter = "
	    << counter;
  std::cout << "\nstatic n1::counter = "
	    << n1::counter;


  std::cout << "\nconst const_counter = "
	    << const_counter;

  std::cout << std::endl;
}


/******************************************************************************/
/*!\test 3.2 One-definition rule

RULE2 Every program SHALL contain exactly one definition of every
      previous item ( RULE_1's a) to d) ) that is odr-used in that
      program. [1_1]


RULE2_EXCEPTION There are two kinds of references that do not
		constitute an odr-use in the previous sense:

e2-a) A reference to an entity appears as part of a sizeof operator

e2-b) A reference that appears as part of a typeid operator it is not
      odr-used unless the argument of the typeid operator ends
      designating a polymorphic object (because in general it is not
      always possible to determine the result of a polymorphic typeid
      operation until run time).
*/
/******************************************************************************/



void test_rule2()
{
  std::cout << std::endl;
}


int main()
{
  test_rule1();
  test_rule2();
  return 0;
}
