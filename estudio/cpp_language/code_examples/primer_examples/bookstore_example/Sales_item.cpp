#include "Sales_item.h"

#include <iostream>

// #include <assert.h>


/******************************************************************************
 class Sales_item implementation
******************************************************************************/

//------------------------------------------------------------------------------
// Fiend functions
//------------------------------------------------------------------------------

std::ostream &operator<<(std::ostream &os, const Sales_item &obj)
{
  os << obj.isbn()
     << " "
     << obj.num_sold()
     << " "
     << obj.revenue()
     << " "
     << obj.avg_price();
  return os;
}

//------------------------------------------------------------------------------

std::istream &operator>>(std::istream &is, Sales_item &obj)
{
  double price;
  is >> obj.the_isbn >> obj.the_num_sold >> price;

  // check that the inputs succeeded
  if (is)
    obj.the_revenue = price*obj.num_sold();
  else 
    obj = Sales_item();  // input failed: reset object to default state

  return is;
}

//------------------------------------------------------------------------------

/*!\warning return a copy (temporary object) to a  new Sales_item object.
 */
Sales_item operator+(const Sales_item &obj1, const Sales_item &obj2)
{
  Sales_item retval(obj1);
  return (retval+=obj2);
}


//------------------------------------------------------------------------------
// Member functions
//------------------------------------------------------------------------------

Sales_item &Sales_item::operator+=(const Sales_item &obj)
{
  if((&obj != this) 
     and (this->isbn() == obj.isbn()))
    {
      this->the_num_sold += obj.num_sold();
      this->the_revenue += obj.revenue();
    }
  return *this;
}

//------------------------------------------------------------------------------

double Sales_item::avg_price() const
{
  if (num_sold()>0)
    return (revenue() / num_sold());
  else
    return 0;
}

//------------------------------------------------------------------------------

// EOFILE
