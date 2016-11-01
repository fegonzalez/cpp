/*!\error The "Implicit conversion" situation:

  class Date
  {
   public:
	Date(); // default ctor; no arguments required 
  	Date(time_t t); // extracts date from a time_t value  (*P)
  };

  main()
  {
    Date p = NULL; // Compilation OK because it fits (*P)
  }


  Problem:
  The compiler executes an implicit conversion from long (NULL's type) to time_t
  The problem here is that the implicit conversion (taking place behind the
  programmer's back) switches off the compiler's static type checking.


- Solution: The explicit Keyword: constructors declared explicit will
  refuse to perform such implicit conversions.

*/

#include <ctime>
#include <iostream>
#include <cassert>


/***************************************************************************/
/*!\test The "Implicit conversion" situation */
/***************************************************************************/
class Date
{
 public:
  
 Date():the_time(0){}
  
  //non-default ctors:

  
  // implicit conversion operator: extracts date from a time_t value
  //
  //Date(time_t t): the_time(t) {} //!\warning Accepts an implicit
  // 				    // conversion from long to time_t

  explicit Date(time_t t): the_time(t) {} //solution: explicit conversion oper.

  time_t time()const {return the_time;}
  
private:

  time_t the_time;
};


/***************************************************************************/
/*!\test WARNING Only One Class-Type Conversion Is Allowed by the compiler */
/***************************************************************************/

class Counter
{
 public:

  Counter():the_count(0)
  {}


  /* implicit conversion - access: Counter - string */
  Counter(std::string s):the_count(s.size())  // implicit conversion
  {
    std::cout << "\nINSIDE: (implicit) Counter(std::string s)" << std::flush;
  }

  operator std::string()
  {
    std::cout << "\nINSIDE: operator string()" << std::flush;
    return "Counter2string";
  }

  Counter(const Counter &src)
  {
    std::cout << "\nINSIDE: Counter copy ctor" << std::flush;
    the_count = src.the_count;
  }

  Counter & operator=(const Counter &src)
  {
    std::cout << "\nINSIDE: Counter operator=" << std::flush;
    the_count = src.the_count;
    return *this;
  }

  
  /* explicit construction - access : Counter - int */
  // explicit Counter(int count):the_count(count)
  // {
  //   std::cout << "\nexplicit Counter(int count):the_count(count)" << std::endl;
  // }


  // explicit operator int() // warning: explicit conversion operators: c++11 required
  // {
  //   std::cout << "explicit operator int()\n";
  //   return the_count;
  // }


  
  
  int count()const {return the_count;}
  void reset() { the_count = 0;}


  void set(const Counter& src)
  {
    std::cout << "\nINSIDE: void set(const Counter& src)" << std::flush;
    the_count = src.the_count;
  }


  /*!\test implicit conversion of a non-const reference.

    Expected: to receive and modify a Counter object.

    error: "no known conversion"

  */
  void set_nonconst(Counter& src)
  {
    std::cout << "\nINSIDE: void set_nonconst(Counter& src)"<< std::flush;
    src.the_count = the_count;
  }

  
  
private:

  int the_count;
};

//------------------------------------------------------------------------------

int main()
{
  /*!\test The "Implicit conversion" situation */

  // explicit Date(time_t t): compilation error: conversion from
  // ‘long int’ to non-scalar type ‘Date’ requested
  // Date p = NULL;
  // std::cout << p.time() << std::endl;

  Date d(std::time(0)); // ok: Direct Initialization
  std::clog << d.time() << std::endl;
  Date d2= Date(std::time(0)); //same meaning as above
  std::clog << d2.time() << std::endl;

  // error: explicit Constructors Can Be Used Only for Direct Initialization
  // Date d3 = std::time(0);
  Date d3 = Date(std::time(0)); //ok: Direct Initialization
  std::clog << d3.time() << std::endl;


  /*!\test Implicit conversion operators */
  
  std::string s1 = "I am a literal";

  std::cout << std::endl;
  std::cout << "\nCounter c1(s1);";
  Counter c1(s1);  // ok: implicit conversion (conversor operator)

  std::cout << std::endl;
  std::cout << "\nCounter c3 = s1;";
  Counter c3 = s1;  // ok: (implicit constructor)

  std::cout << std::endl;
  std::cout << "\nCounter c4 = c3";
  Counter c4 = c3;  // ok: (copy constructor)

  std::cout << std::endl;
  std::cout << "\nc4 = c3";
  c4 = c3;     	    // ok: (operator=)

	
  /*!\test WARNING Only One Class-Type Conversion Is Allowed by the compiler */
	       
  /*  a) Functions that require a string can accept a literal => one
      conversion (literal to string)

      i) Conversion from literal to a (temporary) string
      ii) Calling Counter(std::string s)
  */

  std::cout << std::endl;
  std::cout << "\nCounter c2(\"I am a literal\")";
  Counter c2("I am a literal");  // ok: implicit conversion (implicit constructor)


  /* b) Functions that require a Counter can accept a string => 
     => one conversion: string to Counter

     i) Calling Counter(std::string s) to create a temporary Counter
     ii) Calling the function with the temporary Counter
  */

  std::cout << std::endl;
  std::cout << "\nc1.set(s1);";
  c1.set(s1);            // ok: implicit conversion



  std::cout << std::endl;

  
  /*
    c) Functions that require a Counter cannot accept a literal =>
    => two conversion: literal to (temporary) string to Counter
  */

  //  c4 = "I am a literal"; // error: no match for ‘operator=’ (operand types
                             // are ‘Counter’ and ‘const char [15]’)
                             // (calling operator=(Counter &) )
  
  //  Counter c5 = "I am a";     // error: conversion from ‘const char [8]’
                             // to non-scalar type ‘Counter’ requested
                             // (calling the copy constructor)

  	
  /*!\test WARNING The compiler can not perform an implicit conversion
    for a non-const reference because it can't be temporary, (it has
    no sense):
  */
  

  // error: no constructor exists to convert a "const char*" to a Counter.
  //
  // It would require two user-defined conversions:
  // (1) convert "a literal" to a string
  // (2) convert that (temporary) string to Counter
  // c1.set("a literal");

  std::cout << "\ntest explicit use of a non-const reference."
	    << std::endl;
  c3.reset();
  std::cout << c3.count();
  c1.set_nonconst(c3);
  std::cout << std::endl << c3.count();
  std::cout << std::endl;

  std::cout << std::endl;
  std::cout << "\ntest implicit conversion of a non-const reference:"
  	    << "\nc1.set_nonconst(string); // error: no known conversion from "
  	    << "'string' to Counter&"
  	    << std::endl;
  //  c1.set_nonconst(s1);

  //!\test operator string
  std::cout << std::endl;
  s1 = c1;
  std::cout << "s1; " << s1 << std::endl;
  std::cout << std::endl;
    
  return 0;
}
