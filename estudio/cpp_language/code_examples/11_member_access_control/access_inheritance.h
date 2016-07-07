#ifndef ACCESS_INHERITANCE_H
#define ACCESS_INHERITANCE_H


/*==============================================================================
//!\test 11.2 Accessibility of base classes and base class members

- The derivation access specifier has no effect on whether members
(and friends) of a derived class may access the members of its own
direct base class...

- ... The purpose of the derivation access specifier is to control the
access that users of the derived class—including other classes
derived from the derived class—have to the members inherited from the base:

//============================================================================*/

void access_inheritance_test(); // for test purpose only

class Base
{
 public:
  void pub_mem(){}; // public member
 protected:
  int prot_mem; // protected member
 private:
  char priv_mem; // private member
};


//============================================================================*/
// Access to the derived classes & their friends
//============================================================================*/


struct Pub_Derv : public Base
{
  /******************************************************************/
  /*!\note The IMPLICIT derived code would be something like this:  */
  /******************************************************************/
  /* 
 public:
  void pub_mem();
 protected:
  int prot_mem;
  */
  /******************************************************************/

  // Pub_Derv code     
 public:
  int f() {return prot_mem;}        // ok: prot_mem is accesible 
  //  char g() { return priv_mem; } // error: private members are inaccessible
                                    // to derived classes
};


//----------------------------------------------------------------------------*/

struct Priv_Derv : private Base
{
  /******************************************************************/
  /*!\note The IMPLICIT derived code would be something like this:  */
  /******************************************************************/
  /*
 private:
  void pub_mem();
  int prot_mem;
  */
  /******************************************************************/

  // Priv_Derv code

  int f() {return prot_mem;} // ok: private derivation doesn't affect access
     
  //  char g() { return priv_mem; } // error: private members are inaccessible
                                    // to derived classes
};


//----------------------------------------------------------------------------*/

struct Prot_Derv : protected Base
{
  /******************************************************************/
  /*!\note The IMPLICIT derived code would be something like this:  */
  /******************************************************************/
  /*
 protected:
    void pub_mem();  
    int prot_mem;
  */
  /******************************************************************/

  // Priv_Derv code

  int f() {return prot_mem;} // ok: protected derivation doesn't affect access
     
  //char g() { return priv_mem; } // error: private members are inaccessible
                                    // to derived classes
};

//----------------------------------------------------------------------------*/

void exempting_individual_members_test(); // for test purpose only

struct Exempting_Priv_Derv : private Base
{
  /******************************************************************/
  /*!\note The IMPLICIT derived code would be something like this:  */
  /******************************************************************/
  /*
 private:
  void pub_mem();
  int prot_mem;
  */
  /******************************************************************/

  // Priv_Derv code

  int f() {return prot_mem;} // ok: private derivation doesn't affect access
    
  //  char g() { return priv_mem; } // error: private members are inaccessible
                                    // to derived classes
  
 public:

  // using Base::priv_mem; // error: A derived class may provide a using
			// declaration only for names it is permitted
			// to access, thus not to the private members
			// of the base.
 
  using Base::pub_mem; // accessible to users & derived classes.

    
};
#endif
