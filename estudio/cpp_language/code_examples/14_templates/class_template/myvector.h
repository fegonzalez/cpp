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
#include <cstdlib> // __func__


template <typename T> class Vector;  //declaration

template <typename T>
std::ostream & operator<<(std::ostream & , const Vector<T> &);

template <typename T>
std::ostream & operator<<(std::ostream & , const Vector<T*> &);


/******************************************************************************/
/* Primary Template */ 
/******************************************************************************/

template <typename T>  class Vector // definition
{
  friend std::ostream & operator<< <T>    //!\warning <T> is required      
    (std::ostream & , const Vector<T> &); //          (see c++-howto.14.7.1)

 public:

  explicit Vector(size_t s=100);
  Vector(const Vector<T> & src);
  Vector<T>& operator=(const Vector<T> & src);
  ~Vector();

  T& operator[](unsigned int index);
  const T& operator[](unsigned int index)const;
  size_t size()const {return sz;}

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


template <typename T>
inline
Vector<T>::Vector(size_t s):
 sz(s),
 buff(new T[s])
{
  std::cout << "\nVector<T> explicit ctor(size_t s)\n";
}

//------------------------------------------------------------------------------
  
template <typename T>
Vector<T>::Vector(const Vector<T> & src):
sz(0),
  buff(nullptr)
{
  std::cout << "\nVector<T> copy ctor. (warning inside call to operator=)";

  *this = src; //use overloaded operator=
}

//------------------------------------------------------------------------------
 
template <typename T>
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
  
template <typename T>
inline
Vector<T>::~Vector()
{
  std::cout << "\nVector<T> destructor.\n";
 
  delete [] buff;
  buff = nullptr;    
}

//------------------------------------------------------------------------------
  
template <typename T>
inline
T& Vector<T>::operator[](unsigned int index)
{
  std::cout << "\nVector<T> operator[]\n";
  
  assert(index < size());
  return buff[index];
}

//------------------------------------------------------------------------------
  
template <typename T>
inline
const T& Vector<T>::operator[](unsigned int index)const
{
  //  std::cout << "\nCONST Vector<T> operator[] CONST";
  
  assert(index < size());
  return buff[index];
}

//------------------------------------------------------------------------------
  
template <typename T>
std::ostream & operator<<(std::ostream &os , const Vector<T> &src)
{
  os << "{";

  if(src.size()>0)
  {
    for(size_t loopi=0; loopi < src.size() - 1; ++loopi)
      os << " " << src[loopi] << ",";
    os << " " << src[src.size()-1];
  }
  
  os << "}";
  
  return os;
}



/******************************************************************************/
/* 14.1.2 Partial Specializations of a Class Template 

9) If you specialize a class template, you MUST also specialize all
   member functions. 

   WARNING  And all data members
*/ 
/******************************************************************************/

template <typename T>
class Vector<T*>    // partial specialization: type is T*
{
  friend std::ostream & operator<< <T*>    //!\warning <T*> is required
    (std::ostream & , const Vector<T*> &); //          (see c++-howto.14.7.1)

 public:

  explicit Vector(size_t s=100);
  ~Vector();  
  Vector(const Vector<T*> & src);
  Vector<T*>& operator=(const Vector<T*> & src);

  T& operator[](unsigned int index);
  const T& operator[](unsigned int index)const;
  size_t size()const {return sz;}

 private:
  
  size_t sz = 100;
  T**buff = nullptr;

  void release();

};


/******************************************************************************/
/* definitions of Partial Specializations of a Class Template */ 
/******************************************************************************/

template <typename T>
inline
Vector<T*>::Vector(size_t s):
 sz(s),
 buff(new T*[s])
{
  std::cout << "\nFunction: " << __func__;
}

//------------------------------------------------------------------------------
  
template <typename T>
inline
Vector<T*>::~Vector()
{
  std::cout << "\nFunction: " << __func__;
  release();
}

  
//------------------------------------------------------------------------------
    
template <typename T>
void Vector<T*>::release()
{
  std::cout << "\nFunction: " << __func__;

  for(size_t loopi=0; loopi< sz; ++loopi)
  {
    delete(buff[loopi]);
    buff[loopi] = nullptr;
  }
  delete [] buff;
  buff = nullptr;
}

//------------------------------------------------------------------------------
  
template <typename T>
Vector<T*>::Vector(const Vector<T*> & src):
sz(0), buff(nullptr)
{
  std::cout << "\nFunction: " << __func__;

  *this = src; //use overloaded operator=
}

//------------------------------------------------------------------------------
 
template <typename T>
Vector<T*> & Vector<T*>::operator=(const Vector<T*> & src)
{
  std::cout << "\nFunction: " << __func__;
  
  if(not(this==&src))
  {
    //release element ptr. by element ptr.
    release();

    sz = src.sz;
    buff = new T[src.sz];
    assert(buff);
    //copy element ptr. by element ptr.
    for(size_t loopi=0; loopi< src.sz; ++loopi)
    {
      assert(src[loopi]);
      buff[loopi] = new T(*(src[loopi]));	      
      assert(buff[loopi]);
    }
  }
    return *this;
}

//------------------------------------------------------------------------------
  
template <typename T>
inline
T& Vector<T*>::operator[](unsigned int index)
{
  std::cout << "\nFunction: " << __func__;
  
  assert(index < size());
  assert((buff[index]));
  return *(buff[index]);
}

//------------------------------------------------------------------------------
  
template <typename T>
inline
const T& Vector<T*>::operator[](unsigned int index)const
{
  std::cout << "\nFunction: " << __func__;
  
  assert(index < size());
  assert((buff[index]));
  return *(buff[index]);
}

//------------------------------------------------------------------------------
  
template <typename T>
std::ostream & operator<<(std::ostream &os , const Vector<T*> &src)
{
  os << "{";

  if(src.size()>0)
  {
    for(size_t loopi=0; loopi < src.size() - 1; ++loopi)
      os << " " << src[loopi] << ",";
    os << " " << src[src.size()-1];
  }
  
  os << "}";
  
  return os;
}
  
//------------------------------------------------------------------------------


#endif
