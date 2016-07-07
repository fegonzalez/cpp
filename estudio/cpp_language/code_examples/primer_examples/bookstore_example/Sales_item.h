#ifndef SALES_ITEM__H
#define SALES_ITEM__H


#include <iosfwd>    // iostream declarations only 
/* #include <iostream>  // using std::string */
#include <string>

//==============================================================================

const std::string DEF_ISBN ="";

class Sales_item;

std::ostream &operator<<(std::ostream &os, const Sales_item &obj);


/*!\fn std::istream &operator>>(std::istream &is, Sales_item &obj);

  \brief Input: isbn units price
*/
std::istream &operator>>(std::istream &is, Sales_item &obj);


/*!\fn Sales_item operator+(const Sales_item &obj1, const Sales_item &obj2);

  \brief The two objects must refer to the same ISBN. The result is a
  new Sales_item object whose ISBN is that of its operands and whose
  number sold and revenue are the sum of the corresponding values in
  its operands.
*/
Sales_item operator+(const Sales_item &obj1, const Sales_item &obj2);

//==============================================================================

/*!\class Sales_item 

  \brief Sales_item class is to represent the total revenue, number of
  copies sold, and average sales price for a book. How these data are stored or
  computed is not our concern.
*/
class Sales_item
{
  friend std::ostream &operator<<(std::ostream &os, const Sales_item &obj);
  friend std::istream &operator>>(std::istream &is, Sales_item &obj);
  friend Sales_item operator+(const Sales_item &obj1,
			      const Sales_item &obj2);

 public:

  Sales_item() = default;
  explicit Sales_item(std::istream &is) { is >> *this; };
    
  std::string isbn() const {return the_isbn;}
  unsigned int num_sold() const {return the_num_sold;}
  double revenue() const {return the_revenue;}
  inline double avg_price() const;

  Sales_item& operator=(const Sales_item& newval) = default;

  /*!\fn Sales_item& operator+=(const Sales_item& obj);

    \warning The two objects must refer to the same ISBN.
  */
  Sales_item& operator+=(const Sales_item& obj);
  
 private:

  //data area
  std::string the_isbn = DEF_ISBN;
  unsigned int the_num_sold = 0;
  double the_revenue = 0.0;
  
};

//==============================================================================

#endif // SALES_ITEM__H
