#include "refs_lib.h"
#include "base.h"

#include <iostream>
#include <cassert>



//-----------------------------------------------------------------------------


/* extern-reference definition example */

const int &ref71 = 22;

//-----------------------------------------------------------------------------

double gravity() {return 9.81;}

//-----------------------------------------------------------------------------

void ptr_incr(int*& i)
{ i++; }

//-----------------------------------------------------------------------------

int get_int_var()
{
  int a = 6;
  return a;
}

//-----------------------------------------------------------------------------

int ref2func(int input)
{
  return input + 2;
}

//-----------------------------------------------------------------------------

void finput(int &param)
{
  const std::string mynameis = "void finput(int &param);";

  std::cout << mynameis;
  std::clog << "received    address = " << &param << std::endl;
  std::cout << "\nparam value = " << param << std::endl;
}

//-----------------------------------------------------------------------------

void finput(const int &param)
{
  const std::string mynameis = "void finput(const int &param)";
  
  std::cout << mynameis;
  std::clog << "received    address = " << &param << std::endl;
  std::cout << "\nparam value = " << param << std::endl;
}

//-----------------------------------------------------------------------------

void finput(BaseClass &param)
{
  const std::string mynameis = "void finput(BaseClass &)";

  std::cout << mynameis << std::endl;
  std::clog << "received    address = " << &param << std::endl;
} 

//-----------------------------------------------------------------------------

void finput(const BaseClass &param)
{
  const std::string mynameis = "void finput(const BaseClass &param)";
  
  std::cout << mynameis << std::endl;
  std::clog << "received    address = " << &param << std::endl;
}

//-----------------------------------------------------------------------------

void const_finput(const int& param)
{
  const std::string mynameis = "void const_finput(const int& param)";
  
  std::cout << mynameis;
  std::clog << "received    address = " << &param << std::endl;
  std::cout << "\nparam value = " << param << std::endl;
}

//-----------------------------------------------------------------------------

void nonconst_finput(int& param)
{
  const std::string mynameis = "void nonconst_finput(int& param)";

  std::cout << mynameis;
  std::clog << "received    address = " << &param << std::endl;
  std::cout << "\nparam value = " << param << std::endl;
}

//-----------------------------------------------------------------------------

/*!\fn int& f_return_local_var();

  \brief Function returning a lcoal variable.
*/
int& f_return_local_var()
{
  int  local_obj = 4;
  local_obj++;
  
  const std::string mynameis = "int& f_return_local_var()";
  const std::string inside = "INSIDE: ";
  std::cout << std::endl << inside << mynameis << std::flush;
  std::clog << std::endl << inside << "local variable address = " << &local_obj
	    << std::flush;
  std::cout << std::endl << inside << "local variable value = " << local_obj
	    << std::flush;
  return local_obj;
}
 
//-----------------------------------------------------------------------------

/*!\fn int& f_return_local_ref();

  \brief Function returning a LOCAL-VAR memory reference.
*/
int& f_return_local_ref()
{
  int local_obj=4;
  int &local_ref = local_obj;
  local_obj++;
  
  const std::string mynameis = "int& f_return_local_ref()";
  const std::string inside = "INSIDE: ";
  std::cout << std::endl << inside << mynameis << std::flush;
  std::clog << std::endl << inside << "local variable address = " << &local_obj
	    << std::flush;
  std::cout << std::endl << inside << "local variable value = " << local_obj
	    << std::flush;
  std::clog << std::endl << inside << "local ref address = " << &local_ref
	    << std::flush;
  std::cout << std::endl << inside << "local ref value = " << local_ref
	    << std::flush;

  return local_ref;
}


//-----------------------------------------------------------------------------

int& fstatic()
{
  static int local_static_obj = 144;
  
  const std::string mynameis = "int& fstatic()";
  const std::string inside = "INSIDE: ";
  std::cout << std::endl << inside << mynameis << std::flush;
  std::clog << std::endl << inside << "local variable address = "
	    << &local_static_obj
	    << std::flush;
  std::cout << std::endl << inside << "local variable value = "
	    << local_static_obj
	    << std::flush;

  return local_static_obj;
}

//-----------------------------------------------------------------------------

/* b+=a */
void incr_by_ref (int a, Passbyref &b) 
{
  std::cout << "\n\nvoid incr_passbyref (int a, Passbyref &b) " << std::flush;
  std::clog << "\n   ... address = " << &b << std::flush;

  b.incr(a);
}

void incr_by_value (int a, Passbyref b) //HERE: calling the copy constructor
{
  std::cout << "\n\nvoid incr_by_value (int a, Passbyref b)" << std::flush;
  std::clog << "\n   ... address = " << &b << std::flush;
  b.incr(a); 
} //HERE: calling the destructor

//-----------------------------------------------------------------------------

void usef( void (&f)(int) )  { f(42); }

void f_as_param( int x ) { std::cout << "result = " << x << std::endl; }

