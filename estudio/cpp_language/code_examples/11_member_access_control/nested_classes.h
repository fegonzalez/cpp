#ifndef _NESTED_CLASSES_H
#define _NESTED_CLASSES_H


/*==============================================================================
//!\test 11.7 Nested classes

The members of an enclosing class have no special access to the INNER
members of a nested class; the usual access rules (11) shall be obeyed.
 
Thus, B & I has complete access to E members, but E's members access
to the interior of B & I follows the general rules (public, protected, private)

//============================================================================*/

void nested_classes_test(); // for test purpose only

class E {

  friend void nested_classes_test(); // for test purpose only
  
  int x;

  class B { };

  class I {
    friend void nested_classes_test(); // for test purpose only
    B b; // OK: E::I can access E::B
    int y;
    void f(E* p, int i) {
      p->x = i; // OK: E::I can access E::x
    }
  };
  
  /*
  int g(I* p)
  {
    return p->y; // error: I::y is private
  }
  */
};


#endif
