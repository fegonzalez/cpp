/*!\test [c10] - FAQ Why am I getting an error after declaring a Foo
  object via Foo x(Bar())?

  https://isocpp.org/wiki/faq/ctors
*/



#include <iostream>


/*******************************************************************************
 PROBLEM code
*******************************************************************************/

class Bar {
public:
  Bar()
  {	std::cout << "\nBar() ctor. " << std::flush;}
  // ...
};


class Foo {
public:
  Foo(const Bar& b)  // or perhaps Foo(Bar b)
  {
    std::cout << "\nFoo(const Bar& b) ctor." << std::flush;
    (const void)b;
  }

  Foo(const Foo& src)
  {
    std::cout << "\nFoo copy ctor." << std::flush;
    if(this != &src)
    {
      ;
    }
  }

  
  void blah()
  {	std::cout << "\nFoo::blah() method." << std::flush;}
};


void yourCodeFail()
{
  std::cout << "\nyourCodeFail()" << std::flush;
 
  Foo x(Bar());  // You think this creates a Foo object called x...
  
  //x.blah();      // compilation error: ...But it doesn't, so this line
		 // gives you a bizarre error message:
                 //
                 // error: request for member ‘blah’ in ‘x’, which is
                 // of non-class type ‘Foo(Bar (*)())

  std::cout << "\ncompilation error" << std::flush;

  std::cout << std::endl;
}


/*******************************************************************************
 SOLUTION code: (upon equivalents  x_sol & y_sol)
*******************************************************************************/


void yourCodeBestSolution()   // ***** BEST_PRACTICE [C++11] required
{
  std::cout << "\nyourCodeBestSolution()" << std::flush;
  
  Foo x{Bar()};  // ***** BEST_PRACTICE: uniform initialization
                    // C++11 required
  
  x.blah();      // Ahhhh, this now works: no more error messages

  std::cout << std::endl;
}


void yourCodeTrickySolution()
{
  std::cout << "\nyourCodeTrickySolution()" << std::flush;
 
  Foo x((Bar()));
     // ↑     ↑ // These parens save the day
  x.blah();
  // ↑↑↑↑↑↑↑↑ // Ahhhh, this now works: no more error messages
  std::cout << std::endl;
}

void yourCodeCopyCtor()
{
  std::cout << "\nyourCodeCopyCtor()" << std::flush;
 
  Foo x = Foo(Bar());  // Foo copy-constructor
  x.blah();            // Ahhhh, this now works: no more error messages
  // ...
  std::cout << std::endl;
}

void yourCodeImplicitCtor()
{
  std::cout << "\nyourCodeImplicitCtor()" << std::flush;
 
  Foo x = Bar(); // Implicit conversion operator from Bar to Foo (Usually works
  x.blah();      // 
  // ...
  std::cout << std::endl;
}


/******************************************************************************/


int main()
{
  yourCodeFail();

  yourCodeTrickySolution();
  yourCodeCopyCtor();
  yourCodeImplicitCtor();

  yourCodeBestSolution(); // C++11 required

  std::cout << std::endl;
  
  return 0;
}


