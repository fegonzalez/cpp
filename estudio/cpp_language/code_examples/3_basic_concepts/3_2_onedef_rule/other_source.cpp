
#include "other_source.h"

#include <iostream>



/* \test a-ii) non-static global variables

   global variable "int one_per_program_non_static_global_var" defined
   twice in the program: main.cpp, other_source.cpp

   expected: compilation error: multiple definitions of
   `one_per_program_non_static_global_var'

   obtained: the expected
*/
//int one_per_program_non_static_global_var = 1;



/* \test c) Static data members

   data_member `classone::one_per_program_static_data_member "int
   one_per_program_non_static_global_var' defined twice in the
   program: main.cpp, other_source.cpp

   expected: compilation error multiple definitions of
   `classone::one_per_program_static_data_member'

   obtained: the expected 
*/
//int classone::one_per_program_static_data_member = 1;


/*!\test d-b1) (explicitly declared) static names

   b1) (explicitly declared) static names

       (including the global namespace, see 3.2.1 RULE1_EXCEPTION's example)
 */
static int counter = 0; // unrelated to other translation units
namespace n1
{
  static int counter = 1; // unrelated to other translation units
}

/*!\test d-b2) a variable of non-volatile const-qualified type that is
       neither explicitly declared extern nor previously declared to
       have external linkage:

       (non-extern) (non-volatile) const ...
*/
const int const_counter = 2; // ok: unrelated to other translation units


// extern DefinedPolymorphicDecider a_poly_decider;


void print()
{

  std::cout << "\n(other_source) static counter = "
	    << counter;

  std::cout << "\n(other_source) static n1::counter = "
	    << n1::counter;

  std::cout << "\nconst const_counter = "
	    << const_counter;  
}




