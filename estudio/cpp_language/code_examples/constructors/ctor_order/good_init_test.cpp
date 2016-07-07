/*!\test [k12] - construction (initialization) order
 */

#include <iostream>
#include <cassert>

//------------------------------------------------------------------------------

class A;
class B;
class C;

//------------------------------------------------------------------------------

class D
{
public:
  
  D(int value = -1): the_value(value)
  {
    std::cout << "create D::D()" << std::endl;
  }

  ~D()
  {
    std::cout << "destroy D::~D()" << std::endl;
  }

  int the_value;
};

//------------------------------------------------------------------------------

class A
{
public:
  
  A()
  {
    std::cout << "create A::A()" << std::endl;
  }

  ~A()
  {
    std::cout << "destroy A::~A()" << std::endl;
  }

  virtual void print() const
  {
    std::cout << " A::print()" << std::endl;    
  }
};

//------------------------------------------------------------------------------

class B: public A
{
public:
  
  B() 
      // implicit call to direct base constructors
      // implicit initialization of the v-pointer
      // implicit initialization of the embeded data members: int, D
  {
    std::cout << "create B::B()" << std::endl;
  }

  ~B()
  {
    std::cout << "destroy B::~B()" << std::endl;
  }

  virtual void print() const
  {
    std::cout << " B::print()" << std::endl;
    std::cout << "(undefined) int_within_b =  " << std::flush;
    std::clog << int_within_b << std::flush;
    
    std::cout << "\n(default -1) d_within_b =  " << d_within_b.the_value
	      << std::endl;
  }

protected:
  int int_within_b;
  D d_within_b;
};

//------------------------------------------------------------------------------

class C: public B
{
public:
  
  C():
  //!\todo (1) implicit call to virtual base constructors (C is the
  //       most derived class)

  // (2) implicit call to direct bases (B) constructor.
    
  // (3) implicit initialization of the v-pointer: __vptr(&C::__vtable[0])

  // (4) init. of the embeded data members: emdeb_inc, num, ptr2d
    embed_in_c(22),
    num(33),
    ptr2d(new D(44))
    
  // (5) body constructor -> object created (this)
  {
    assert(ptr2d);
    std::cout << "create C::C()" << std::endl;
  }

  
  ~C()
  {
    std::cout << "destroy C::~C()" << std::endl;
    delete(ptr2d);

    // (1) body destructor -> object deleted (this)
    
    // (2) implicit call destructor of the embedded data members
    // (inverse order of declaration): (ptr2d must be explicitly
    // deleted in the body), num, emdeb_in_c

    // (3) implicit deletion of the v-pointer (only in the most base class)

    // (4) implicit call to direct bases (B) destructor.    

    //!\todo (5) implicit call to virtual base destructors (C is the
    //       most derived class)
    
  }

  
  virtual void print() const
  {
    std::cout << "C::print()" << std::endl;
    std::cout << "embed_in_c =  " << embed_in_c.the_value << std::endl;
    std::cout << "num =  " << num << std::endl;
    assert(ptr2d);
    std::cout << "*ptr2d =  " << ptr2d->the_value << std::endl;

    this->B::print();
  }

protected:
  D embed_in_c;
  int num;
  D *ptr2d;
};


//==============================================================================

int main()
{
  std::cout << "\n ctor_order test (c++ standard 12.6.2)" << std::endl;
  C c_obj;
  c_obj.print();
  

  /* output:
  create A::A()
  create D::D()
  create B::B()
  create D::D()
  create D::D()
  create C::C()
  C::print()
  embed_in_c = 22
  num = 33
  *ptr = 44
  destroy C::~C()  // C destructor ongoing:
  destroy D::~D()  // C's data member (ptr2d)
  destroy D::~D()  // C's data member (embed_in_c)
  destroy B::~B()  // B destructor ongoing:
  destroy D::~D()  // B's data member (d_within_b)
  destroy A::~A()  // A destructor ongoing:
                   // HERE v-pointer implicitly released (most base class)
                   

  */
  
  std::cout << std::endl;
  return 0;
}
