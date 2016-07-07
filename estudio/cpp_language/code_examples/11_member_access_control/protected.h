#ifndef _PROTECTED_H
#define _PROTECTED_H


/*==============================================================================
//!\test 11.4 Protected member access

A derived class member or friend may access the protected members of the
base class only through a derived object. ([3_1] 15.5, p. 756)

//============================================================================*/

class Sneaky;
class BaseProtectedTest;

void protected_test(); // for test purpose only
void clobber(Sneaky&); 
void clobber(BaseProtectedTest&);



class BaseProtectedTest {
 protected:
  
  int prot_mem = 0; // protected member

 public:
  
  void dummy(){};
};
  
class Sneaky : public BaseProtectedTest
{
  friend void clobber(Sneaky&); // ok: can access Sneaky::prot_mem

  // error: can't access BaseProtectedTest::prot_mem
  friend void clobber(BaseProtectedTest&);
   

  int j; // j is private by default

  void dummy(){};
};



#endif
