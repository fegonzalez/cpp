/*\file dummy_c_code.c
  \brief Dummy, not main(), c code to check multiple  compilation:
         g++ -c -x c dummy_c_code.c -x c++ dummy_c++_code.cpp
*/


int dummy_c()
{
  int new = 5;
  return new;
}
