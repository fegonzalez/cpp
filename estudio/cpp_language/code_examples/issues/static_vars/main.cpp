
/*!\test [KI001] LOCAL static var in a member function: is the
   variable shared between all the objects of that type?

   Result:  YES

   FACT: They are just like "class variables", but with local scope
         (scope = the function they are defined)

*/



#include <iostream>



/*******************************************************************************
 PROBLEM code
*******************************************************************************/

class Dummy_Static
{
public:
  
  void f_with_local_static()
  {
    static int local_static_var= 0;

    std::cout << "\n" << my_name << " :" << local_static_var++ << std::endl;
  }
  

  Dummy_Static(std::string name): my_name(name)
  {}

  
      
private:

  std::string my_name;
};

/******************************************************************************/


int main()
{
  std::cout << "\n\test LOCAL static var in a member function: is the variable"
	    << "shared between all the objects of that type? " << std::flush;

  Dummy_Static uno("uno");
  Dummy_Static dos("dos");
  Dummy_Static tres("tres");

  for (unsigned int loop = 0; loop < 3; ++loop)
    {
      uno.f_with_local_static();
      dos.f_with_local_static();
      tres.f_with_local_static();
    }

  
  std::cout << std::endl;
  return 0;
}


