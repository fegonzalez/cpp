/**@test [k2501] remove_if algorithm VS hand-written loop on an std::vector

  @warning std::remove-if Example copied from wikipedia: 
           https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom#Example

*/

// Use g++ -std=c++11 or clang++ -std=c++11 to compile.

#include <algorithm> // remove and remove_if
#include <iostream>
#include <vector> // the general-purpose vector container



//=============================================================================

///@test std::remove_if ::  remove if value in [2-7]

bool  condition(int i)
{
  return ( (2 <= i) and (i <= 7) );
}

void print(const std::vector<int> &vec)
{
  std::cout << "(size = " << vec.size() << "); ";
  for (const auto& i: vec) 
    std::cout << i << ' '; 
  std::cout << std::endl;
}

//=============================================================================
 
int algorithm_test()
{
  // initialises a vector that holds the numbers from 0-9.
  std::vector<int> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  print(v);
 
  // // removes all elements with the value 5
  // v.erase( std::remove( v.begin(), v.end(), 5 ), v.end() ); 
  // print(v); 
  
  // removes all odd numbers
  v.erase( std::remove_if(v.begin(), v.end(), condition), v.end() );
  print(v);

  
/*
Output:
0 1 2 3 4 5 6 7 8 9 
0 2 4 6 8 
*/

  return 0;  
}

//=============================================================================

///@bug ERROR! ++index && remove => skipping several vector positions
int erroneous_hand_written_loop_test()
{
  // initialises a vector that holds the numbers from 0-9.
  std::vector<int> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  print(v);
 
  for (unsigned int index = 0; index < v.size(); ++index)
  {
    std::cout << "\nindex = " << index << std::endl;
    std::cout << "v[index] = " << v[index] << std::endl;

    
    if (condition(v[index]))
    {
      std::cout << "remove: " << v[index] << std::endl;

      //      if (index < v.size())
	v.erase(v.begin() + index);
    }
    else
    {
      std::cout << "DO NOT remove: " << v[index] << std::endl;
    }

    print(v); 
  }

    
/*
Output:
(size = 10) 0 1 2 3 4 5 6 7 8 9   (init)
(size = 7); 0 2 3 5 6 8 9         (final)   ERROR! ++index && remove => skipping several vector positions
*/

  return 0;  
}

//=============================================================================


int fixed_hand_written_loop_test()
{
  // initialises a vector that holds the numbers from 0-9.
  std::vector<int> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  print(v);

  typedef std::vector<int>::iterator vec_iter;
  
  unsigned int index = 0; //log purpose only

  for( vec_iter it = v.begin();
       it != v.end();
       /* blank */ )
  {
    
    std::cout << "\nindex = " << index << std::endl;
    std::cout << "v[index] = " << v[index] << std::endl;

    
    if(condition(*it))
    {
      std::cout << "remove: " << v[index] << std::endl;
      
      //v.erase( it++ );       // Error
      v.erase( it );       // OK
    }
    else
    {
      std::cout << "DO NOT remove: " << v[index] << std::endl;
	    
      ++it;

      ++index;
    }

     print(v); 
  }
 
/*
Output:
(size = 10) 0 1 2 3 4 5 6 7 8 9   (init)
(size = 7); 0 2 3 5 6 8 9         (final)   OK
*/

  return 0;  
}

//   // another version, without vector iterator

// int fixed_hand_written_loop_test()
// {
//   // initialises a vector that holds the numbers from 0-9.
//   std::vector<int> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//   print(v);

  
//   for (unsigned int index = 0; index < v.size();)
//   {
//     std::cout << "\nindex = " << index << std::endl;
//     std::cout << "v[index] = " << v[index] << std::endl;

    
//     if (condition(v[index]))
//     {
//       std::cout << "remove: " << v[index] << std::endl;

//       if (index < v.size())
//       {
// 	v.erase(v.begin() + index);
//       }

//       ///@warning DO NOT increment loop control var when callingvector.erase()
//     }
//     else
//     {
//       std::cout << "DO NOT remove: " << v[index] << std::endl;
//       ++index; ///@warning increment iff std::Vector.erase() not called
//     }

//     print(v); 
//   }

    
// /*
// Output:
// (size = 10) 0 1 2 3 4 5 6 7 8 9   (init)
// (size = 7); 0 2 3 5 6 8 9         (final)   OK
// */

//   return 0;  
// }

//=============================================================================


int main()
{

  std::cout << "\n-------------------" << std::endl; 

  std::cout << "\nalgorithm_test()..." << std::endl; 
  algorithm_test();

  std::cout << "\n-------------------" << std::endl; 

  std::cout << "\nerroneous_hand_written_loop_test()..." << std::endl;
  erroneous_hand_written_loop_test();
  std::cout << "\nERROR! ++index && remove => skipping several vector positions"
	    << std::endl;
  
  std::cout << "\n-------------------" << std::endl; 


  std::cout << "\nfixed_hand_written_loop_test()..." << std::endl;
  fixed_hand_written_loop_test();
  
  std::cout << "\n-------------------" << std::endl; 
  

    
}
  
/*
Output:
0 1 2 3 4 5 6 7 8 9 
0 1 2 3 4 6 7 8 9 
0 2 4 6 8 
*/
