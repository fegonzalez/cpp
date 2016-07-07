#ifndef REFS_LIB_H
#define REFS_LIB_H

#include <iostream>
#include <string>


const int nonlocal_var = 99; 

extern const int &ref71; // can be declared as extern in different files

class BaseClass;
class DerivedClass;
class Passbyref;



//------------------------------------------------------------------------------
// Testing references as functions parameters
//------------------------------------------------------------------------------

/*!\warning const vs non-const functions: in a real program we would
  use functions with the same name, letting the compiler to properly
  select the destination function according to the type of the
  parameter used in the call:

  void finput(const int &);
  void finput(int &);

  
  For test purpose only we will use a different name, this way we may:

  - repeat a call with the same parameter to both functions:
  - to force passing a non-const as a const parameter.

  void const_finput(const int&);
  void nonconst_finput(int&);

*/

int get_int_var();
int ref2func(int input);
double gravity();

void finput(int &);
void finput(const int &);

void finput(BaseClass &);
void finput(const BaseClass &);


void usef( void (&f)(int) );
void f_as_param( int x );



/*!\fn void finput(const int&);

  \brief CONSTANT Memory reference as parameter to a function.
*/
void const_finput(const int&);


/*!\fn void finput(int&);

  \brief NON-CONSTANT Memory reference as parameter to a function.
*/
void nonconst_finput(int&);

  
//------------------------------------------------------------------------------
// Testing functions returning a reference 
//------------------------------------------------------------------------------


/*!\fn int& f_return_local_var();

  \brief Function returning a local variable.
*/
int& f_return_local_var();


/*!\fn int& f_return_local_ref();

  \brief Function returning a LOCAL-VAR memory reference.
*/
int& f_return_local_ref();


/*!\fn int& f_return_local_var();

  \brief Function returning a local-static variable.
*/
int& fstatic();

  

/*!\fn ftest2_return_nonlocal_ref();

  \brief Function returning a NON-LOCAL VAR memory reference.
*/
/* int& ftest2_return_nonlocal_ref(); */



//------------------------------------------------------------------------------
// Testing references in classes
//------------------------------------------------------------------------------


class BaseClass{};

class DerivedClass: public BaseClass
{
};




//------------------------------------------------------------------------------
// Pass by reference: implicit copy?
//------------------------------------------------------------------------------

/* b+=a */
void incr_by_ref (int a, Passbyref &b);

void incr_by_value (int a, Passbyref b);


void ptr_incr(int* &i);


class Passbyref{

  class DummyData{};

  
 public:
  
 Passbyref(int newval = 0): the_value(newval), dummy_data(new DummyData())
      {
	std::cout << "\n\n>> Create Passbyref(): " << std::flush;
	std::clog << "\n   ... address = " << this << std::flush;
      }


  ~Passbyref()
    {
      release();
      std::cout << "\n\n>> Destroy ~Passbyref(): " << std::flush;
      std::clog << "\n   ... address = " << this << std::flush;
    }
 
 
  Passbyref(const Passbyref & src)
    : the_value(0), dummy_data(0) // not required if release() is not executed
    {
      std::cout << "\n\n>> Create Passbyref(const Passbyref&) " << std::flush;
      std::clog << "\n   ... address = " << this << std::flush;

      if(this != &src)
	{
	  /*!\warning A copy constructor is invoked iff the object
             does not yet exists => there's no memory to release.
	    // release(); 
	   */
	  the_value = src.the_value;
	  dummy_data = new DummyData();
	}
    }
  
 
  Passbyref& operator=(const Passbyref & src)
    {
      std::cout << "\n\n>> Passbyref& operator= :" << std::flush;
      std::clog << "\n   ... address = " << this << std::flush;

      if(this != &src)
	{
	  release();
	  the_value = src.the_value;
	  dummy_data = new DummyData();
	}

      return *this; // a copy of myself
    }
 
 
  void incr(int val = 1)
  {
    the_value+=val;
  }

  int get_value()const {return the_value;} 

 
 private:

  int the_value;
  DummyData *dummy_data;

  void release()
  {
    delete dummy_data;
    dummy_data=0;
  }
};


//------------------------------------------------------------------------------
// refs. as data members
//------------------------------------------------------------------------------

/*!\error Reference data member not initialized

   // Option 1: no initialization at all

   Rclass(int a) // Compilation error: uninitialized reference member in ‘int&’


   // Option 2: no initialization, but assignation instead

   Rclass(int a)
   {the_ref = a;} // Compilation error: uninitialized reference member in ‘int&’


   private:
   int & the_ref;//Options 1 & 2: Compiler note: ‘the_ref’ should be initialized
*/
class Rclass
{

 public:

 Rclass(int &a):the_ref(a) {}  // OK
  // Rclass(int a) {}              // Compilation error
  // Rclass(int a) {the_ref = a;}  // Compilation error
  
  int & ref() {return the_ref;}

  
  Rclass& operator=(const Rclass& src)
    {
      if(this != &src)
	{ 
	  /*!\warning copy data members: references aren't re-assignable.
	   */

	  // option 1: ILLEGAL, references can't be re-initialized.
	  // &the_ref = &src.the_ref; // error: lvalue required as left
	                              //         operand of assignment

	  // option 2: WARNING the referent is implicitly modified
	  the_ref = src.the_ref;  // value copy, not deep copy

	  
	  /* valid BUT trick -> destroying and creating => not really copy
	     this->~Rclass();
	     new (this) Rclass(src);
	  */
	}
      return *this;
    }

  
  bool operator==(const Rclass& src)
  {
    if(this != &src)
      return (&the_ref == &src.the_ref);
    else
      return true;
  }

  
 private:
  int & the_ref;
};


/*
c) References and copyability issue

 + Inicializar referencia como data member de una clase => NOT copyable types ?

(e.g.)
*/

#endif
