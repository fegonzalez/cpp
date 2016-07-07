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


/*!\test The "Implicit conversion" situation */
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


/*!\test WARNING Only One Class-Type Conversion Is Allowed by the compiler */

class Counter
{
 public:

  Counter():the_count(0)
  {}


  /* implicit conversion - access: Counter - string */
  Counter(std::string s):the_count(s.size())  // implicit conversion
  {
    std::cout << "\n(implicit) Counter(std::string s)" << std::endl;
  }

  operator std::string()
  {
    std::cout << "operator string()\n";
    return "Counter2string";
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


  void set(const Counter& src) { the_count = src.the_count;}


  /*!\test implicit conversion of a non-const reference.

    Expected: to receive and modify a Counter object.

    error: "no known conversion"

  */
  void copyme(Counter& src) { src.the_count = the_count;}

  
  
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


  
  /*!\test WARNING Only One Class-Type Conversion Is Allowed by the compiler */
  std::string s1 = "I am s1";
  Counter c1(s1);  // ok: implicit conversion
  std::cout << c1.count() << std::endl;
  Counter c2 = s1; // ok: implicit conversion
  std::cout << c2.count() << std::endl;

  c1.set(c2); // ok: explicit call
  std::cout << c1.count() << std::endl;

  c1.set(s1); // ok: implicit conversion
  std::cout << c1.count() << std::endl;

  // error: no constructor exists to convert a "const char*" to a Counter.
  //
  // It would require two user-defined conversions:
  // (1) convert "a literal" to a string
  // (2) convert that (temporary) string to Counter
  // c1.set("a literal");

  std::cout << "\ntest explicit use of a non-const reference."
	    << std::endl;
  c2.reset();
  std::cout << c2.count() << std::endl;
  c1.copyme(c2);
  std::cout << c2.count() << std::endl;


  std::cout << "\ntest implicit conversion of a non-const reference:"
	    << "\nc1.copyme(string); // error: no known conversion from "
	    << "'string' to Counter&"
	    << std::endl;
  /* c1.copyme(s1); */

  s1 = c1;
  std::cout << "s1; " << s1 << std::endl;

  
  return 0;
}
