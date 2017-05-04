/*!\file
  
  \doc [doc1] boost.howto

  \brief Testing boost smart pointers.

  \test boost::shared_ptr to objects : shared_ptr_example()
  \test boost::shared_ptr to arrays : shared_ptr_as_shared_array_example();
  \test boost::shared_array : shared_array_example()
  \test boost::make_shared : make_shared_example()
  \test boost::ptr_vector : void ptr_vector_example()
  \test boost::ptr_set : void ptr_set_example()
 */

#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/make_shared.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_set.hpp>
#include <boost/ptr_container/ptr_inserter.hpp>

#include <iostream>
#include <cassert>
#include <typeinfo> // make_shared_example()
#include <ctime>    // macros example
//#include <array>    // listener example [C++11]
#include <algorithm>// listener example

/*!\test boost::shared_ptr

  \doc [doc_1].2.2.1 test [k2_1]

  \output:

   1
   2
   false
   true

 */
void shared_ptr_example()
{
  std::cout << "\nboost::shared_ptr example"  << '\n';

  boost::shared_ptr<int> p1(new int(1));
  std::cout << typeid(p1).name() << '\n';
  std::cout << *p1 << std::endl;  
  boost::shared_ptr<int> p2(p1);
  assert(*p1==*p2);
  p1.reset(new int(2));
  std::cout << *p1.get() << std::endl;  
  assert(*p1 not_eq *p2);
  p1.reset();
  std::cout << std::boolalpha << static_cast<bool>(p1) << '\n';
  std::cout << std::boolalpha << static_cast<bool>(p2) << '\n';
}

//------------------------------------------------------------------------------

/*!\test boost::shared_array

  \doc [doc_1].2.2.2 test [k2_2]

  \output:

   0
   1
   true
   1
   1
   true
   false
 */
void shared_array_example()
{
  std::cout << "\nboost::shared_array example" << '\n';
  boost::shared_array<int> p1(new int[2]);
  p1[0]=0; //used as an array
  p1[1]=1;
  std::cout << p1[0] << '\n';
  std::cout << p1.get()[1] << '\n';
  //  std::cout << *p1 << '\n'; //error: operator*() not defined
  {
    boost::shared_array<int> p2(p1);
    p2[0] = 1;
    std::cout << std::boolalpha << static_cast<bool>(p2) << '\n';
    assert(p1[0]==p2[0]);
  }
  std::cout << p1[0] << '\n';
  std::cout << p1.get()[1] << '\n';
  std::cout << std::boolalpha << static_cast<bool>(p1) << '\n';


  //!\warning no length operator available

  //!\bug shared_array allows out_of_bounds indexing
  std::cout << "\nBUG boost::shared_array allows out_of_bounds indexing" 
	    << '\n';
  p1[100]=100;
  std::cout << p1[100] << '\n';
  std::cout << p1[2] << '\n';


  p1.reset();
  std::cout << std::boolalpha << static_cast<bool>(p1) << '\n';  
}

//------------------------------------------------------------------------------


/*!\test shared_ptr_as_shared_array_example()

  \doc [doc_1].2.2.2 test [k2_3]

  \bug [k2_3] compilation error upon trying operator[] with Boost
	1.53.0 and C++98. \todo Try with more modern versions.

  \output:

 */

void shared_ptr_as_shared_array_example()
{
/* output:

   //error: operator[] not defined for shared_ptr 
 */
  std::cout << "\nboost::shared_ptr as shared_array example" << '\n';

  boost::shared_ptr<int> p1(new int[2]);

  //  p1[0]=0; //error: operator[] not defined for shared_ptr 
  std::cout << "!\nno match for 'operator[]' in 'p1[0]' " << std::endl;

  // p1[1]=1;
  // std::cout << p1[0] << '\n';
  // std::cout << p1.get()[0] << '\n';
  // std::cout << p1.get()[1] << '\n';
  // {
  //   boost::shared_ptr<int> p2(p1);
  //   p2[0] = 1;
  //   std::cout << std::boolalpha << static_cast<bool>(p2) << '\n';
  //   assert(p1[0]==p2[0]);
  // }
  // std::cout << p1[0] << '\n';
  // std::cout << p1.get()[1] << '\n';
  // std::cout << std::boolalpha << static_cast<bool>(p1) << '\n';

  // p1.reset();
  std::cout << std::boolalpha << static_cast<bool>(p1) << '\n';
}

//------------------------------------------------------------------------------

/*!\test boost::make_shared

  Only one call to new (shared_ptr requires two, one at the pointer definition)

  \doc [doc_1].2.2.3 test [k2_4]
 */
void  make_shared_example()
{
  std::cout << "\nboost::make_shared example" << '\n';

  //auto p1  = // C++ code
  boost::shared_ptr<int> p1 = 
    boost::make_shared<int>(1); //!\hint "(new int(1))" not required
  std::cout << typeid(p1).name() << '\n';

  //  auto p2
  // boost::shared_ptr<int> p2 = // compilation error
  // boost::shared_array<int> p2 = // compilation error
  //   boost::make_shared<int[]>(10);
  // std::cout << typeid(p2).name() << '\n';
}

//------------------------------------------------------------------------------

/*!\test boost::shared_ptr optimization with macros. 

  Using the macro BOOST_SP_USE_QUICK_ALLOCATOR the smart pointer allocation time
  should e reduced.

  \doc [doc_1].2.2.4 test [k2_5]

  \warning Using clog instead of cout to exclude the highly unstable
           value of the ctime result from difftest checking.

  \output

  N5boost10shared_ptrIiEE


  \warning In my test (see [k2_5]), SOMETIMES the results are not the expected:
  better without the optimization macro:

  Loop time with BOOST_SP_USE_QUICK_ALLOCATOR = 43

  Loop time without BOOST_SP_USE_QUICK_ALLOCATOR = 42

*/

void  make_shared_macros()
{
  std::cout << "\nOptimization of boost::shared_ptr with macros" << '\n';
 
#ifndef nullptr  //Pre-C++11 code
#define nullptr 0
#endif

  int num_cycles = 1000000 * 10 * 5;
  boost::shared_ptr<int> p;

#define BOOST_SP_USE_QUICK_ALLOCATOR
  std::cout << "\nUsing BOOST_SP_USE_QUICK_ALLOCATOR" << '\n';
  std::time_t then = std::time(nullptr);
  for (int i = 0; i < num_cycles; ++i)
    p.reset(new int(i));
  std::time_t now = std::time(nullptr);
  std::clog << "\nLoop time with BOOST_SP_USE_QUICK_ALLOCATOR = " 
	    << now - then << '\n';
   
  
#undef BOOST_SP_USE_QUICK_ALLOCATOR
  p.reset();
  std::cout << "\nNOT using BOOST_SP_USE_QUICK_ALLOCATOR" << '\n';

  std::time_t then2 = std::time(nullptr);
  for (int i = 0; i < num_cycles; ++i)
    p.reset(new int(i));
  std::time_t now2 = std::time(nullptr);
  std::clog << "\nLoop time without BOOST_SP_USE_QUICK_ALLOCATOR = " 
	    << now2 - then2 << '\n';

}

//------------------------------------------------------------------------------

/*!\test boost::ptr_vector container

  \doc [doc_1].2.4.1; test [k2_6]
 */

void ptr_vector_example()
{
  std::cout << "\nboost::ptr_vector example" << '\n';
  boost::ptr_vector<int> v;
  v.push_back(new int(1));
  v.push_back(new int(2));
  std::cout << v.back() << '\n';  // prints 2
}

//------------------------------------------------------------------------------


/*!\test boost::ptr_set container

  \doc [doc_1].2.4.2; test [k2_7]
*/

void ptr_set_example()
{
  std::cout << "\nboost::ptr_set example" << '\n';
  boost::ptr_set<int> s;
  s.insert(new int(2));
  s.insert(new int(1));
  std::cout << *s.begin() << '\n';
}

//------------------------------------------------------------------------------

/*!\test container inserter

  \doc [doc_1].2.4.3; test [k2_8]
 */

void container_inserter_example()
{
   std::cout << "\nInserters for boost containers example" << '\n';
   boost::ptr_vector<int> v;
   const size_t ARRAY_SIZE = 3;

   /* [C++11]
   std::array<int, ARRAY_SIZE> a{{0, 1, 2}};  
   std::copy(a.begin(), 
             a.end(), 
	     boost::ptr_container::ptr_back_inserter(v));
   */
   /* [C++03] */
   int a[ARRAY_SIZE] = {0, 1, 2};
   std::copy(a, 
	     a+ARRAY_SIZE, // end() == ptr. to theposition AFTER the last
	     boost::ptr_container::ptr_back_inserter(v));


   std::cout << v.size() << '\n';
   for (size_t loop=0;
     	loop<v.size();
     	++loop)
     std::cout << "v[" << loop << "]= "<< v[loop] << '\n';
   std::cout << '\n';
}

//------------------------------------------------------------------------------


int main()
{
  shared_ptr_example();  
  shared_array_example();
  //  shared_ptr_as_shared_array_example(); // compilation errors
  make_shared_example();
  //make_shared_macros();  // too much time to makediff


  // # 2.4 Boost.PointerContainer
  ptr_vector_example();
  ptr_set_example();
  container_inserter_example();
}
