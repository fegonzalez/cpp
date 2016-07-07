/*!\file references_test.cpp

  \brief Testing " Memory references (&)" # B.1. Memory references (&)

  \info README file for tests details.

  \warning 'cout' MUST be used instead of 'cerror' to have the
  Makefile properly working ("./$(MAIN) > $(MAIN).last_diff" command)

  \warning 'clog' MUST be used in the lines that print memory
  addresses to not print them in the .OK & .last_diff files (because
  the mem. addrs. will change in every execution.

*/


#include "refs_lib.h"
#include "base.h"

#include <iostream>
#include <cassert>


int main()
{
  /*!\test Test: 2.3.1.3 Defining (binding) references to objects. */
    
  std::cout << "\n#----------------------------------------------------------";
  std::cout << "\n1) Test: 2.3.1.3 Defining (binding) references to objects.";
  std::cout << "\n#----------------------------------------------------------"
	    << std::endl;

  std::cout << "\na) Ordinary binding" << std::endl;

  std::cout
    << "\na1) Reference to an object of the same type=> OK"
    << "\nint int_var = 100;"
    << "\nint &ref1 = int_var;"
    << std::endl;
  int int_var = 100, &ref1 = int_var;
  assert(ref1 == int_var);
  assert(&ref1 == &int_var);


  std::cout
    << "\na1) A reference to function: "
    << "\nint (&ref_funcx)(int) = ref2func;"
    << std::endl;

  int (&ref_funcx)(int) = ref2func;	// reference to function
  assert(ref2func(4) == ref_funcx(4));


  std::cout << "\na1) A reference to function as a function parameter: "
	    << std::flush;
  std::cout << "\nvoid usef( void (&f)(int) )  { f(42); }" << std::flush;
  std::cout << "\nvoid f_as_param( int x ) {cout << \"result = \" << x}"
	    << std::flush;
  std::cout << std::endl;
  usef(f_as_param);

	  
  /* **********************************

2.3.1.3 Defining (binding) references to objects [c5]

a1) Reference to an object of the same type

    (e.g) int funcX() { return 42 ; };  
    	  int (&ref_funcx)() = funcX;	// reference to function


2.3.1.3 Defining (binding) references to objects [c5]

 b2.2) const conversion to a different but 'acceptable' type: const R &ref = T;


  ************************************** */
  
  
  std::cout
    << "\na2) Using a reference as an initializer to another reference => OK"
    << "\nint &ref3 = ref1;"
    << std::endl;
  int &ref3 = ref1;
  assert(ref3 == int_var);
  assert(&ref3 == &int_var);

  std::cout << "\na3) const reference to an lvalue-constant => OK"
	    << "\nconst int int_const=55;"
  	    << "\nconst int &ref4 = int_const;"
  	    << std::endl;
  const int int_const=55;
  const int &ref4 = int_const;
  assert(ref4==int_const);


  std::cout << "\na4) Initialization of references as data members.";
  std::cout << "\nCompilation error: uninitialized reference member"
	    << "\nRclass(int &a) {}             // no init."
    	    << "\nRclass(int &a) {the_ref = a;} // no init, but assignation";
  std::cout << "\nCorrect initialization: Rclass(int &a):the_ref(a) {}"
  	    << std::endl;
  Rclass r1(int_var);
  assert(r1.ref() == int_var);
  assert(&r1.ref() == &int_var);
  int_var++;
  assert(r1.ref() == int_var);
  assert(&r1.ref() == &int_var);
  r1.ref()--;
  assert(r1.ref() == int_var);
  assert(&r1.ref() == &int_var);

  
  std::cout << "\na5) Pointer references: the pointer is incremented, "
	    << "not what it points to." 
  	    << std::endl;
  int* ptr_referent = 0;
  std::cout << "before increment: ptr_referent (addr)= " << ptr_referent
    << std::endl;
  ptr_incr(ptr_referent);
  std::cout << "after  increment: ptr_referent (addr)= " << ptr_referent
	    << std::endl;
  

  std::cout << "\na6) Array references"
  	    << std::endl;
  int array[3] = {1, 2, 3};
  int (&rarray)[3] = array; // 'rarray' refers to the array 'array'
  for (int auxi=0; auxi<3;++auxi)
    {
      std::cout << array[auxi] << " ";
      std::cout << rarray[auxi] << std::endl;
    }
  rarray[1] = 22;            // modifies array[1]
  assert(rarray==array);
  assert(&rarray==&array);
  for (int auxi=0; auxi<3;++auxi)
    {
      std::cout << array[auxi] << " ";
      std::cout << rarray[auxi] << std::endl;
    }
  
  
  std::cout << "\nb) Binding exceptions" << std::endl;

  std::cout << "\nb1) Classes related by inheritance => OK"
	    << "\nDerivedClass do1;"
  	    << "\nBaseClass & ref5 = do1"
	    << std::endl;
  DerivedClass do1;
  const DerivedClass do2;
  BaseClass &ref5 = do1;
  assert(&ref5 == &do1);


  std::cout << "\nb2) Const reference to a non-const object of the same type, "
	    << "\n    or to a type that involves an ACCEPTABLE const conversion"
	    << std::endl;

  std::cout << "\n(e.g.) same type => OK" << std::endl;
  const int &ref6 = int_var;
  assert(&ref6 == &int_var); // bind directly to the initializer
  assert(ref6 == int_var);
  int_var+=2;
  assert(&ref6 == &int_var);
  assert(ref6 == int_var);
  int_var-=2;

    
  std::cout << "\n(e.g.) const conversion from literal => OK"
	    << "\nconst int &ref7 = 7; // ref7 refers to TEMPORARY with value 7"
  	    << std::endl;
  const int &ref7 = 7;
  assert(ref7==7);


  std::cout << "\n(e.g) const conversion from a different type"
	    << " (const R &ref = T;)"
  	    << "\ndouble dval = 3.14;"
  	    << "\nconst int &ref62 = dval; "
	    << "// ref62 refers to TEMPORARY with value 3"
  	    << std::endl;
  double dval = 3.14;
  const int &ref62 = dval; // ref62 refers to TEMPORARY with value 3 ...
                           // ... not to the original variable:
  std::clog << &dval << std::endl;
  std::clog << &ref62 << std::endl;
  std::cout << dval << std::endl;
  std::cout << ref62 << std::endl;
  assert(ref62==3);
  dval*=7.0;
  assert(ref62==3);
  std::cout << dval << std::endl;
  std::cout << ref62 << std::endl;

  

  std::cout << "\n(e.g) const conversion from a different type"
	    << "\ndouble gravity() {return 9.81;}"
  	    << "\nconst int &ref621 = g(); "
	    << "// ref621 refers to TEMPORARY with value 9"
  	    << std::endl;
  const int &ref621 = gravity();
  assert(ref621 == 9);


  std::cout << "\nb4) A reference declared as extern does not require "
	    << "initialization: "
	    << "\nextern const int &ref71; // Declaration at base.h"
  	    << "\nconst int &ref71 = 22"
	    << ";   // Definition at refs_lib.cpp"
	    << "\nstd::cout << ref71; " << "     // Use: at main.cpp"
	    << std::endl;

  
  
  std::cout << "\nc) Invalid bindings" << std::endl;

  std::cout << "\nc1) (Non const) Reference to a literal"
	    << "\nint &ref8 = 7;   OR   int &ref8 = get_int_var();  "
	    << std::endl;
  // int &ref8 = 7; assert(ref8==ref8);
  // int &ref8 = get_int_var(); assert(ref8==ref8);
  std::cout << "compilation error: "
  	    << "\"invalid initialization of non-const reference of type ‘int&’ from an rvalue of type ‘int’\""
  	    << std::endl;

  std::cout << "\nc2) Reference to a different type:"
  	    << "\ndouble dval = 3.14;"
  	    << "\nint &ref9 = dval;\n";
  //double dval = 3.14;
  // int &ref9 = dval;
  std::cout << "compilation error: "
  	    << "\"invalid initialization of reference of type ‘int&’ from expression of type ‘double’\""
  	    << std::endl;
  
  std::cout << "\nc2.2) conversion from const to nonconst reference (a particular case of c2)"
	    << "\nWARNING Neither 'a1' nor 'b2' cases"
  	    << "\nconst int int_const = 55;"
  	    << "\nint &ref10 = int_const;\n";
  // int &ref10 = int_const;
  std::cout << "compilation error: "
  	    << "\"invalid initialization of reference of type ‘int&’ from expression of type ‘const int’\""
  	    << std::endl;
  
  std::cout << "\nc2.3) reference to a ptr./ mem.address of the same type "
	    << "(a particular case of c2)"
  	    << "\nint int_var=0;"
  	    << "\nint &ref11 = int_var;\n";
  // int &ref11 = &int_var; assert(&ref11 == &int_var);
  std::cout << "compilation error: "
  	    << "\"invalid initialization of non-const reference of type ‘int&’ from an rvalue of type ‘int*’\""
  	    << std::endl;


/* WARNING A reference must refer to an object, not a dereferenced null
	pointer [3_2_1]

	It means this is illegal (C++ standard, says it’s illegal, it
	doesn't matter what a particular compiler do):
*/
  std::cout << "\nc3) A reference must refer to an object, not a dereferenced "
	    << "null pointer. It is (C++) illegal:"
	    << "\n int* pnull=NULL; int &ref101 = *pnull; // => Compilation OK"
	    << "\ncout << ref101;  => but runtime error: (segmentation fault)"
  	    << std::endl;
  // int* pnull = NULL;
  // int &ref101 = *pnull;  // illegal: it may compile ...
  // std::cout << ref101;   // ... but then rise a segmentation fault

  
  
  /*!\test Test: 2.3.1.4 Memory references as functions parameters.

    NOTICE Passing an object to a function's reference parameter is
           equivalent to define a reference to an object:
  */
  std::cout << "\n#----------------------------------------------------------";
  std::cout << "\n2) Test: 2.3.1.4 Memory references as functions parameters";
  std::cout << std::endl;
  std::cout << "\n NOTICE Passing an object to a function's reference ";
  std::cout << "\n parameter is equivalent to define a reference to an object.";
  std::cout << std::endl;
  std::cout << "\n#----------------------------------------------------------"
	    << std::endl;

  
  std::cout << "\na) Ordinary binding" << std::endl;

  std::cout
    << "\na1) Reference to an object of the same type=> OK"
    << std::endl;
  finput(int_var);
  finput(int_const);
  
  std::cout
    << "\na2) Using a reference as an initializer to another reference => OK"
    << std::endl;
  finput(ref1);
  finput(ref4);

  std::cout << "\na3) const reference to an lvalue-constant => OK"
  	    << std::endl;
  finput(int_const);


  std::cout << "\nb) Binding exceptions" << std::endl;

  std::cout << "\nb1) Classes related by inheritance => OK" << std::endl;
  std::clog << "calling var address = " << &do1 << std::endl;
  finput(do1);
  std::cout << std::endl;
  std::clog << "calling var address = " << &do2 << std::endl;
  finput(do2);

  
  std::cout << "\nb2) CONST reference to a non-const id=> OK" << std::endl;
  std::cout << "\nb2.1) const conversion to the same data type: const T & = T"
  	    << std::endl;
  const_finput(int_var);
  std::cout << "\nb2.2) const conversion to a different but 'acceptable' type: "
	    << "\nconst_finput(const int &) <- double dval = 3.14"
  	    << std::endl;
  dval = 3.14;
  const_finput(dval);

  
  std::cout << "\nb3) CONST reference to a literal => OK" << std::endl;
  finput(7);

  
  std::cout << "\nc) Invalid bindings" << std::endl;

  std::cout << "\nc1) (Non const) Reference to a literal"
	    << "\nnonconst_finput(7);"
	    << std::endl;
  // nonconst_finput(7);
  std::cout << "compilation error: "
  	    << "\"invalid initialization of non-const reference of type ‘int&’ from an rvalue of type ‘int’\""
  	    << std::endl;

  std::cout << "\nc2) Reference to a different type:"
  	    << "\n//double dval = 3.14; void nonconst_finput(int &param)"
  	    << "\nnonconst_finput(dval)\n";
  // double dval = 3.14;
  // nonconst_finput(dval);
  std::cout << "compilation error: "
  	    << "\"invalid initialization of reference of type ‘int&’ from expression of type ‘double’\""
  	    << std::endl;
  
  std::cout << "\nc3) conversion from const to nonconst reference (a particular case of c2)"
	    << "\nWARNING Neither 'a1' nor 'b2' cases"
  	    << "\nconst int int_const = 55; void nonconst_finput(int &param)"
  	    << "\nnonconst_finput(int_const);;\n";
  // nonconst_finput(int_const);
  std::cout << "compilation error: "
  	    << "\"invalid initialization of reference of type ‘int&’ from expression of type ‘const int’\""
  	    << std::endl;
  
  std::cout << "\nc4) reference to a ptr./ mem.address of the same type "
  	    << "(a particular case of c2)"
  	    << "\nnonconst_finput(&int_var);\n";
  // nonconst_finput(&int_var);
  std::cout << "compilation error: "
  	    << "\"invalid initialization of non-const reference of type ‘int&’ from an rvalue of type ‘int*’\""
  	    << std::endl;
  


  /*!\test Testing functions returning a reference.
  */

  std::cout << "\n#----------------------------------------------------------";
  std::cout << "\n3) Test: 2.3.1.5 functions returning memory references";
  std::cout << "\n#----------------------------------------------------------"
	    << std::endl;

  std::cout << "\na) Returning references to local variables." << std::endl;

  std::cout << "\na1) Returning a local variable."
  	    << std::endl;
  std::cout << "compilation warning: "
  	    << "reference to local variable ‘local_obj’ returned"
  	    << std::flush;
  int &ref12 = f_return_local_var(); 
  std::clog << "\ncalling var address = " << &ref12 << std::flush;
  std::cout << "\nreturned value = undefined value (i.e. -1013474526) = "
  	    << std::flush;    
  std::clog << ref12 << std::flush;
  std::cout << std::endl;

  
  std::cout << "\na2) Return a reference to a local variable."
	    << std::endl;
  std::cout << "WARNING compilation OK."
  	    << "\nWARNING undefined result"
  	    << std::flush;
  int &ref13 = f_return_local_ref(); 
  std::clog << "\ncalling var address = " << &ref13 << std::flush;
  std::cout << "\nreturned value = undefined value (i.e. -1013474526) = "
	    << std::flush;    
  std::clog << ref13 << std::flush;
  std::cout << std::endl;

  
  std::cout << "\na3) Returning a static local variable" << std::flush;
  int &ref14 = fstatic();
  std::clog << "\ncalling var address = " << &ref14 << std::flush;
  std::cout << "\nreturned value = " << ref14 << std::flush;
  std::cout << std::endl;

  
  
  std::cout << "\n#----------------------------------------------------------";
  std::cout << "\n4) Test: Pass by reference vs pass by copy: ";
  std::cout << "\n#----------------------------------------------------------"
  	    << std::endl;

  Passbyref passbyref(89);

  std::cout << "\n\n4.2) By reference: no copy at all. " << std::flush;

  incr_by_ref (2, passbyref);
  incr_by_ref (-22, passbyref);
  assert(passbyref.get_value() == 89+2-22);
  std::cout << std::endl;

  std::cout << "\n\n4.2) By copy: the copy constructor is (implicitly) invoked"
    << std::endl;
  std::cout << "\n--------- Before calling 'incr_by_value': " << std::flush;
  incr_by_value (3, passbyref);
  std::cout << "\n\n--------- After calling 'incr_by_value': " << std::flush;
  std::cout << std::endl;
  
   
  std::cout << "\n#----------------------------------------------------------";
  std::cout << "\n4) Test: issues of references as data members.";
  std::cout << "\n#----------------------------------------------------------"
	    << std::endl;

  std::cout << "\nWARNING If the objects must be reassignable (copyable), "
	    << "\n        references cannot be used as data members."
	    << std::endl;

  struct Foo
  {
    std::string& text;
    Foo(std::string& s):text(s){}

    Foo & operator=(const Foo& src) {
      if(this != &src) {text = src.text;}
      return *this;
    }
  };

  std::string s1("I am s1");
  std::string s2("I am s2");
  Foo foo_s1(s1);
  Foo foo_s2(s2);

  std::cout  << "\nfoo_s1 (" << foo_s1.text << ") ; s1 (" << s1 << ")"
	     << "\nfoo_s2 (" << foo_s2.text << ") ; s2 (" << s2 << ")"
	     << std::endl;

  foo_s2 = foo_s1; // WARNING s2 implicitly modified

  std::cout  << "\nExecuting: foo_s2 = foo_s1;";
  std::cout  << "\nfoo_s1 (" << foo_s1.text << ") ; s1 (" << s1 << ")"
	     << "\nfoo_s2 (" << foo_s2.text << ") ; s2 (" << s2 << ")"
	     << " => s2 implicitly modified!"
	     << std::endl;

  s2 = "Still  I'am s2"; // WARNING foo_s2 implicitly modified!
  

  std::cout  << "\nExecuting: s2 = \"Still  I'am s2\";";
  std::cout  << "\nfoo_s2 (" << foo_s2.text << ") ; s2 (" << s2 << ")"
	     << " => foo_s2 implicitly modified!"
	     << std::endl;


  std::cout  << "\nDanger: Lifetime issues: referent ceased to exist."
	     << std::flush;
  std::string * s3 = new std::string("I am temporary.");
  
  Foo foo_s3(*s3);
  std::clog  << "\n& foo_s3 : " << & foo_s3.text << std::flush;
  std::cout  << "\nfoo_s3 : " << foo_s3.text << std::flush;
 
  std::cout  << "\nExecuting: delete(s3); s3=0;" << std::flush;
  delete(s3);
  s3=0;
  std::clog  << "\n& foo_s3 : " << & foo_s3.text << std::flush;
  std::cout  << "\nHERE: using the reference will cause Segmentation Fault"
	     << std::flush;
  //std::cout  << "\nfoo_s3 : " << foo_s3.text << std::flush;
  std::cout  << std::endl;



  std::cout << "\n#----------------------------------------------------------";
  std::cout  << "\nd) Definitions using the volatile Qualifier: " << std::endl;
  std::cout << "\n#----------------------------------------------------------";
  std::cout << std::endl;

  std::cout << "\nValid case: volatile T & = volatile T" << std::endl;
  volatile int vi = 1;
  volatile int & vref = vi;     // ok: vref refers to vi
  std::cout << vi << std::endl;
  std::cout << vref << std::endl;
  assert(&vref==&vi);

  std::cout << "\nValid case: const volatile T & = volatile T" << std::endl;
  const volatile int & cvref = vi;     // ok: vref refers to vi
  std::cout << cvref << std::endl;
  assert(&cvref==&vi);

  std::cout << "\nInvalid case: anything else." << std::endl;

   
  return 0;
}
