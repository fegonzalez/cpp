/*!\file sales_input_test.cpp

  \brief Test for the Sales_item class

  Options:
  input_from_file: test input from file
  hard_coded_input: input codified in this source. 
*/


#include "Sales_item.h"
#include <iostream>
#include <sstream>
#include <cassert>

//------------------------------------------------------------------------------

void input_from_file(Sales_item &item1, Sales_item &item2);
void hard_coded_input(Sales_item &item1, Sales_item &item2);

//------------------------------------------------------------------------------

//make "EXEC_OPTIONS = <./data/add_item" runtest
void input_from_file(Sales_item &item1, Sales_item &item2)
{
  bool invariant = (item1.isbn() == item2.isbn());
  assert(invariant);
  std::cin >> item1 >> item2;
  assert(invariant);
}

// hard-coded input: make runtest
void hard_coded_input(Sales_item &item1, Sales_item &item2) 
{
  bool invariant = (item1.isbn() == item2.isbn());
  assert(invariant);
  std::istringstream iss("0-201-78345-X 3 20.00");
  iss >> item1;
  std::istringstream iss2("0-201-78345-X 2 25.00");
  iss2 >> item2;
  assert(invariant);
}

//------------------------------------------------------------------------------


int main()
{
  std::cout <<">>sales_item_test.cpp" << std::endl;

  Sales_item item1, item2;
  //hard_coded_input(item1, item2);
  input_from_file(item1, item2);
    
  std::cout <<"write: ISBN, copies sold, total revenue, sales price."
	    << std::endl;
  std::cout << item1 + item2 << std::endl; //print their sum

  std::cout << std::endl;
  return 0;
}

/*!\warning Input selection via execution command:

  ./sales_item_test  vs  ./sales_item_test <./data/add_item

  \error: "<./data/add_item" is not taken as an input argument

 */
/*
int main(int argc, char *argv[])
{
  std::cout << argc << std::endl;
  std::cout << argv[0] << std::endl;
  
  Sales_item item1, item2;

  // no funciona porque "<./data/add_item"  no cuenta como argv
  if (argc==1)
    hard_coded_input(item1, item2);
  else
    input_from_file(item1, item2);
    
  std::cout <<"\nwrite: ISBN, copies sold, total revenue, sales price."
	    << std::endl;
  std::cout << item1 + item2 << std::endl; //print their sum
  
  return 0;
}
*/
