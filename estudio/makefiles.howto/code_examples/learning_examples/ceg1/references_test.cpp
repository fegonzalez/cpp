/*!\file references_test.cpp

  \brie Testing " Memory references (&)" # B.1. Memory references (&)

  \info README file for tests details.

  \warning 'cout' MUST be used instead of 'cerror' to have the
  Makefile properly working ("./$(MAIN) > $(MAIN).last_diff" command)
 */


#include "refs_lib.h"
#include <iostream>


int main()
{
  //aux vars. init
  T  T_var = nonlocal_var;
  // T& ref_to_var = T_var;

    
  std::cout << "\n#----------------------------------------------------------";
  std::cout << "\n1) Test type 1. Testing references as functions parameters ";
  std::cout << "\n#----------------------------------------------------------"
	    << std::endl;

  
  /*!\test TEST_1_1 passing a constant: ftest1_ref_as_fnparam(7)

    Expected: compilation error 

    Result: the expected: "invalid initialization of non-const
    reference of type ‘int&’ from an rvalue of type ‘int' "
  */
  // ftest1_ref_as_fnparam(7);
  std::cout << "\nTEST_1_1 passing a constant: ftest1_ref_as_fnparam(7): "
	    << "compilation error."
	    << std::endl;

  
  /*!\test TEST_1_2 passing a & to a constant: ftest1_ref_as_fnparam(&7)

    Expected: compilation error
    Result:   the expected: "lvalue required as unary ‘&’ operand"
  */

  // ftest1_ref_as_fnparam(&7);
  std::cout << "\nTEST_1_2 passing a & to a const.: ftest1_ref_as_fnparam(&7): "
	    << "compilation error."
	    << std::endl;

  
  /*!\test TEST_1_3 passing a variable: ftest1_ref_as_fnparam(T_var)

    Expected: 
    Result:   
  */
  std::cout << "\nTEST_1_3 passing a variable: ftest1_ref_as_fnparam(T_var): "
	    << "OK. Inside the function, used as a reference to the var, "
	    << "and can be persistently modified inside."
	    << std::endl;

  
  // aki lo dejo:
  //   http://www.tutorialspoint.com/makefile/makefile_quick_guide.htm
  //   Makefile Implicit Rules


    
  ftest1_ref_as_fnparam(T_var);
  // ftest1_ref_as_fnparam(&T_var);
  // ftest1_ref_as_fnparam(ref_to_var);
  std::cout << "Returned obj value = " << T_var << std::endl;



  
  return 0;
  

  std::cout << "\n#----------------------------------------------------------";
  std::cout << "\n2) Test type 2. Testing functions returning a reference ";
  std::cout << "\n#----------------------------------------------------------"
	    << std::endl;

  
  /*!\test TEST_2_1 return a reference to a local variable. 

    Expected: compilation warning
    Result: the expected; "reference to local variable returned""
  */
  //ftest2_return_local_ref();
  std::cout << "\nTEST_2_1 return a reference to a local variable."
	    << " compilation warning."
	    << std::endl;

    
  return 0;
}
 
