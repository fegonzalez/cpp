/*!\test [c9] - the "static initialization order" fiasco.

  FAQ What’s the “static initialization order fiasco”?  

  https://isocpp.org/wiki/faq/ctors

  >>> A subtle way to crash your program.

  This the well known problem of initializing two GLOBAL (static)
  variables, which exist in separate source files, when one of them
  depends on the other to be initialized: 50%-50% chance of dying.

  \test Problem & solution for built-in types.

*/



#include <iostream>

const int INITIAL_Y_VALUE = 5;

/*******************************************************************************
 PROBLEM code
*******************************************************************************/

int f();  // forward declaration
int g();  // forward declaration

int x = f();  //!\warning More than one GLOBAL variables initialization.
int y = g();


int f()
{
  std::cout << "\n - initializing 'x'" << std::flush;

  //!\warning HERE 'x' depends on non-constructed 'y' => fiasco solved
  std::cout << "\nconstruction of x uses y (which is " << std::flush;
  std::cout << y << std::flush;
  std::cout << ") " << "; (" << INITIAL_Y_VALUE << " expected)." << std::endl;

  std::cout << "\nwarning fiasco DOES NOT IMPLIES compilation or linking error";
  std::cout << "\nwarning fiasco IMPLIES an uncontrolled unexpected bad "
	    << "initialization"
	    << "\n => run-time  mistakes / errors / CRASH" << std::endl;
  return 3*y + 7;
}

int g()
{
  std::cout << "initializing 'y' (" << INITIAL_Y_VALUE << ")\n";
  return INITIAL_Y_VALUE;
}



/*******************************************************************************
 SOLUTION code: (upon equivalents  x_sol & y_sol)
*******************************************************************************/


int & x_sol();
int & y_sol();

int & x_sol()
{
  std::cout << "\n\n - initializing 'x_sol'" << std::flush;
  //!\warning HERE 'x_sol' depends on non-constructed 'y_sol' => fiasco solved
  std::cout << "\n   cronstruction of x_solve uses y_sol (which is "
	    << std::flush;
  std::cout << y_sol() << std::flush;
  std::cout << ") " << "; (" << INITIAL_Y_VALUE << " expected)." << std::endl;

  static int* ans = new int(3 * y_sol() + 7);
  return *ans;
}

int & y_sol()
{
  std::cout << "\n - initializing 'y_sol' ("; 
  static int* ans = new int(INITIAL_Y_VALUE);
  std::cout << *ans << ")" << std::endl;
  return *ans;
}



/******************************************************************************/


int main()
{
  std::cout << "\nmain() " << std::flush;
  std::cout << "\nUsing the \"Construct On First Use Idiom\"" << std::flush;
  std::cout << "\nmain: First use of 'x_sol' %%%_(" << std::flush;
  std::cout << x_sol() << std::flush;
  std::cout << ")_%%%" << std::flush;
  std::cout << "\nmain: 'y_sol' already created ---_(" << std::flush;
  std::cout << y_sol() << std::flush;
  std::cout << ")_---" << std::flush;
  std::cout << std::endl;
  return 0;
}


