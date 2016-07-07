/*!\test virtual functions FAQ: What’s the difference between how
  virtual and non-virtual member functions are called?
*/

//==============================================================================

#include <iostream>
#include <cassert>

//==============================================================================

class Shape
{
public:
  virtual void draw() const;
  void move() const;
  void resize() const;
  virtual void check_member_access_rules() const;
};

void Shape::draw()const
{
  std::cout << "\nvirtual Shape::draw()" << std::endl;
}

void Shape::move()const
{
  std::cout << "\nShape::move()" << std::endl;
}

void Shape::resize()const
{
  std::cout << "\nShape::resize()" << std::endl;
}

void Shape::check_member_access_rules()const
{
  std::cout << "\nvirtual Shape::check_member_access_rules()" << std::endl;
}
  
//------------------------------------------------------------------------------

class Circle : public Shape
{
  //--- inherited virtual functions
public:
  void draw() const; // here: "virtual" is not necessary, already
		     // specified at Shape
private:
  void check_member_access_rules() const; 
  

public:  
  //---  non-inherited functions
  void only_for_circle()const;

  
  /*!\fn void Circle::move() 
    \warning: does not override Shape::move(), it defines a new method
    called move() instead.
  */
  void move() const
  { std::cout << "\nnew-method Circle::move()" << std::endl; }

  
  /*!\fn virtual void Circle::resize() 
    \warning: does not override Shape::resize(), it defines a new method
    called resize() instead.
    \warning 'virtual' here is not related to the base class.
  */
  virtual void resize() const
  { std::cout << "\nnew-method  virtual Circle::resize()" << std::endl; }

};


void Circle::draw()const
{
  std::cout << "\nvirtual Circle::draw()" << std::endl;
}
 
void Circle::check_member_access_rules()const
{
  std::cout << "\nvirtual Circle::check_member_access_rules()" << std::endl;
}
  
void Circle::only_for_circle()const
{
  std::cout << "\nv Circle::only_for_circle()" << std::endl;
}

  
//------------------------------------------------------------------------------

class SolidCircle : public Circle 
{
public:

  //--- inherited virtual functions: inherited fromm Shape
  
  void draw() const; // "virtual" already specified at Shape
  void check_member_access_rules() const;
  void resize() const;
};

void SolidCircle::draw()const
{
  std::cout << "\nvirtual SolidCircle::draw()" << std::endl;
}
 
void SolidCircle::check_member_access_rules()const
{
  std::cout << "\nvirtual SolidCircle::check_member_access_rules()"
	    << std::endl;
}

void SolidCircle::resize()const
{
  std::cout << "\nvirtual SolidCircle::resize()"
	    << std::endl;
}


//==============================================================================


int main()
{
  std::cout << "\n\n>> test virtual functions vs non-virtual functions"
	    << std::endl;

  
  /* Q: What’s the difference between how virtual and non-virtual
     member functions are called?

     A: 
     Non-virtual member functions are resolved statically (at compile-time)
     BASED ON the TYPE of the POINTER (or reference) TO THE OBJECT.

     Virtual member functions are resolved dynamically (at run-time),
     BASED ON the TYPE of the OBJECT, not the type of the ptr/ref to that obj.
  */
  
  Circle my_circle;
  Shape * shape1 = &my_circle; // static binding: type Shape.
                               // dynamic binding: type Circle
			       // member access: type Shape.

 
  
  /*!\test shape1->only_for_cycle()

    expected: compile error 
    (non-virtual member -> compile-time -> based on the type of the
    pointer to the object, thus "Shape", but Shape::only_for_cycle()
    doesn't exists).
    
    obtained: the expected
  */
  /* shape1->only_for_cycle(); // error: ‘class Shape’ has no member
  // named ‘only_for_cycle’
  */
  std::cout << "\ntest shape1->only_for_cycle(): compile error: ‘class Shape’ "
	    << "has no member named ‘only_for_cycle’"
	    << std::endl;

  
  /*!\test shape1->draw()

    expected: OK
    virtual member -> run-time -> based on the type of the object, thus "Circle"
  
    obtained: the expected
  */
  std::cout << "\ntest shape1->draw(): ok "
  	    << std::flush;
  shape1->draw(); // ok

  
  /*!\test shape1->move()

    expected: OK
    (non-virtual member -> compile-time -> based on the type of the
    pointer to the object, thus "Shape", and Shape::move() exists.)
    
    warning: Circle::move() does not interferes here (because remember:
    based on the type of the pointer)

    obtained: the expected
  */
  std::cout << "\ntest shape1->move(): ok "
	    << std::flush;
  shape1->move(); // ok


  /*!\test circle1->move()

    expected: OK. No pointer or reference => the type is static =>
    compile-time resolution based on the type (Circle).
  
    obtained: the expected
  */
  //  Circle circle1;
  Circle * circle1 = &my_circle; // all bindings & access rules: Circle
  std::cout << "\ntest circle1->move(): ok " << std::flush;
  circle1->move();


  /*!\test shape1->resize()  (idem shape1->move())

    expected: OK
  */
  std::cout << "\ntest shape1->resize(): ok "
	    << std::flush;
  shape1->resize(); // ok


  /*!\test circle1->resize()

    expected: OK. No pointer or reference => the type is static =>
    compile-time resolution based on the type (Circle).
  
    obtained: the expected
  */
  std::cout << "\ntest circle1->resize(): ok " << std::flush;
  circle1->resize();
  
  
  /*!\test circle1->Shape::resize

    expected: OK. Indirect call to Shape::resize()
  
    obtained: the expected
  */
  std::cout << "\ntest circle1->Shape::resize(): ok " << std::flush;
  circle1->Shape::resize();


    
  /* Applying member access rules: */
  std::cout << "\ntest Applying member access rules" << std::endl;
  
  /*!\test dynamic binding & public access: 
    expected: ok
    dynamic binding =>  Circle::check_member_access_rules() is selected ...
    & accesses via Shape pointer => ... accessed as Shape => public 
  
    obtained: the expected
  */
  std::cout << "\ntest shape1->check_member_access_rules(): ok "
  	    << std::flush;
  shape1->check_member_access_rules();
    
  
  /*!\test dynamic binding & private access: 

    expected: error
    dynamic binding =>  Circle::check_member_access_rules() is selected ...
    access as Circle pointer => ... Circle::check_member_access_rules is private
  
    obtained: the expected
  */
  std::cout << "\ntest error: ‘virtual void Circle::check_member_access_rules()"
	    << " const’ is private "
  	    << std::flush;
  // circle1->check_member_access_rules();
  

  std::cout << std::endl;


    
  /*!\test deep method inheritance: 

    Shape::virtual draw()
      ^
      |

    Circle::draw() 
      ^
      |

    SolidCircle::draw() is virtual by inheritance, not matter how it
    is qualified in Circle.

    expected: ok

    obtained: the expected
  */
  std::cout << "\ntest deep method inheritance" << std::endl;
  std::cout << "\n a) virtual functions:" << std::endl;
  SolidCircle solidcircle1;
  Shape * shape2 = &solidcircle1;
  std::cout << "\ntest shape2->draw(): ok " << std::flush;
  shape2->draw(); // ok
  Circle * circle2 = &solidcircle1;
  std::cout << "\ntest circle2->draw(): ok " << std::flush;
  circle2->draw(); // ok
  std::cout << "\ntest solidcircle1.draw(): ok " << std::flush;
  solidcircle1.draw(); // ok
  
  std::cout << "\ntest shape2->check_member_access_rules(): ok " << std::flush;
  shape2->check_member_access_rules();
  std::cout << "\ntest circle2->check_member_access_rules(): error"
	    << std::flush;
  std::cout << "\ntest error: ‘virtual void Circle::check_member_access_rules()"
	    << " const’ is private "
  	    << std::flush;
  //circle2->check_member_access_rules();
    std::cout << std::endl;  
  std::cout << "\ntest solidcircle1.check_member_access_rules(): ok "
	    << std::flush;
  solidcircle1.check_member_access_rules();


  /*!\test deep method inheritance of non-virtual (non-overwrote) functions */
  std::cout << "\n b) non-virtual functions:" << std::endl;
  std::cout << "\ntest shape2->move(): expected Shape::move() ok"
	    << std::flush;
  shape2->move();
  std::cout << "\ntest circle2->move(): expected Circle::move() ok"
	    << std::flush;
  circle2->move();

  std::cout << "\ntest shape2->resize(): expected Shape::resize() ok"
	    << std::flush;
  shape2->resize();
  std::cout << "\ntest circle2->resize():  SolidCircle::resize() ok"
  	    << std::flush;
  circle2->resize();
  
  std::cout << std::endl;  
  return 0;
}



/* EOFILE */
