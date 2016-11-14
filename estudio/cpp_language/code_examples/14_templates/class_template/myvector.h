#ifndef MYVECTOR_H_
#define MYVECTOR_H_

/*\file myvector.h

  \brief C++ Template study. c++.howto, chaper 14.
*/


/*!\test [k1401]

#14.1.1 Declaring a Class Template

*/


#include <cstddef>
#include <cassert>
#include <iostream>


template <class T> class Vector;  //declaration

template <class T>
std::ostream & operator<<(std::ostream & , const Vector<T> &); 

template <class T>  class Vector // definition
{
 public:

  
  explicit Vector(size_t s=100); // equivalent to Vector<T>(size_t s=100);
  Vector(const Vector<T> & src);
  Vector<T>& operator=(const Vector<T> & src);
  ~Vector();

  T& operator[](unsigned int index);
  const T& operator[](unsigned int index)const;
  size_t size()const;


  bool template_never_used_doesneed_definition()const;

  bool template_used_needs_definition()const {return true;}
  
 private:

  size_t sz = 100;
  T *buff = nullptr;
};


/******************************************************************************/
/* definitions of (template class Vector's) member functions follow
   the class declaration.
*/
/******************************************************************************/


template <class T>
Vector<T>::Vector(size_t s):
 sz(s),
 buff(new T[s])
{
  std::cout << "\nVector<T> explicit ctor(size_t s)\n";
}

//------------------------------------------------------------------------------
  
template <class T>
Vector<T>::Vector(const Vector<T> & src):
sz(0),
  buff(nullptr)
{
  std::cout << "\nVector<T> copy ctor. (warning inside call to oeprator=\n";

  *this = src; //use overloaded operator=
}

//------------------------------------------------------------------------------
 
template <class T>
Vector<T> & Vector<T>::operator=(const Vector<T> & src)
{
  std::cout << "\nVector<T> operator=()\n";
  
  if(not(this==&src))
  {
    delete [] buff;
    buff = nullptr;

    sz = src.sz;
    buff = new T[src.sz];
    assert(buff);
    for(size_t loopi=0; loopi< src.sz; ++loopi)
      buff[loopi] = src[loopi];
  }
    return *this;
}

//------------------------------------------------------------------------------
  
template <class T>
Vector<T>::~Vector()
{
  std::cout << "\nVector<T> destructor.\n";
 
  delete [] buff;
  buff = nullptr;    
}

//------------------------------------------------------------------------------
  
template <class T>
inline
T& Vector<T>::operator[](unsigned int index)
{
  std::cout << "\nVector<T> operator[]\n";
  
  assert(index < size());
  return buff[index];
}

//------------------------------------------------------------------------------
  
template <class T>
inline
const T& Vector<T>::operator[](unsigned int index)const
{
  //  std::cout << "\nCONST Vector<T> operator[] CONST";
  
  assert(index < size());
  return buff[index];
}

//------------------------------------------------------------------------------
  
template <class T>
inline
size_t Vector<T>::size()const
{
  return sz;
}

//------------------------------------------------------------------------------
  
template <class T>
std::ostream & operator<<(std::ostream &os , const Vector<T> &obj)
{
  os << "{";

  if(obj.size()>0)
  {
    for(size_t loopi=0; loopi < obj.size() - 1; ++loopi)
      os << " " << obj[loopi] << ",";
    os << " " << obj[obj.size()-1];
  }
  
  os << "}";
  
  return os;
}

//------------------------------------------------------------------------------
  


#endif
