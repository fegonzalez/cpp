
#include <iostream>
#include <string>

#include <cstdio> //snprintf
#include <cstring>

//   g++ -std=c++11  -Wall -Werror  arrays_in_cpp.cpp

/**@file arrays_in_cpp.cpp  

   - I   Passing arrays as function arguments
   - II  How to return a local array from a C/C++ function?
   - III How to initialize an static array member

   - Reference documents:
     [1] "The ANSI C Programming Language", Brian W. Kernighan
     [2] https://www.geeksforgeeks.org/return-local-array-c-function/

 */


/*******************************************************************************/
/* I Passing arrays as function arguments

   [1] 5.3 Pointers and Arrays:

   << When an array name is passed to a function, what is passed is the
   location of the initial element (a memory address, a pointer) (*) >>

   (*) @warning: therefore, the content can be changed.


   - function parameters - equivalent assignments: (char*) 

     void f(char *s);   // explicit => preferred
     void f(char s[]);
     void f(char s[3] ); // eqivalent, the dimension information is discarded.

*/
/*******************************************************************************/

  typedef char t_identifier[35];

// C modes
void print_c1(const char *s, unsigned int len);   // explicit => preferred
void print_c2(const char s[], unsigned int len);  // implicit array => equivalent c1 
void print_c3(const char *s); ///@warning, '\0' expected (undefined behaviour otherwise
void print_c4(const char s[1000] ); // equivalent, the dimension information is discarded.

void print_c5(const t_identifier s); // equivalent



/**@warning NOT equivalent. Due to the reference ('&') the dimension
   MUST be exact (eg. 35); compilation error otherwise.
   [ Example 
     char cadena[3] = {'2','5','R'};
     print_c6(cadena); error: invalid initialization of reference of type 
                       ‘const char (&)[35]’ from expression of type ‘char [3]’
   -- end example ]
  */
void print_c6(const t_identifier &s); ///@warning NOT equivalent.
void set_c1(char *s, unsigned int len);   // explicit => preferred
void set_c2(char s[], unsigned int len);  // implicit array => equivalent c1 
void fn_arguments_C_test();

// C++ modes
void byref1 
(const int (&a)[4],// (&a) required unless typedef, otherwise...
                   //...compiler error: declaration of ‘a’ as array of references
 unsigned int len);

typedef int T_ARRAY_ENTEROS_LEN_4 [4];
void byref1_bis
(const T_ARRAY_ENTEROS_LEN_4 &a, //compiler OK
 unsigned int len);

template<class A> 
void byref2(const A& a, unsigned int len);
//void byref2(const A& a)  //C++11

void fn_arguments_CPP_test();

/*******************************************************************************/
/* II How to return a local array from a C/C++ function?

   [e.g. char cadena[3] = {'2','5','R'}; ]

II.1 Functions

a) ERROR: return a local variable. (trivial)
   - compilation: warning: << address of local variable 'arr' returned
                              [-Wreturn-local-addr] >>

   - output: UNDEFINED (It may produce values 10 20 as output or may
             produce garbage values or may crash.)
   - example: see retarray_error_undefined


b) VALID: return a dynamically allocated (new/malloc), (pointer to an)
          array. (trivial)         
   - problem: end of array management?
   - example: see retarray_dyn_alloc


c) VALID: return a static array. (trivial)
    - problem: end of array management?
    - example: see retarray_static


d) VALID: return an structure containing the array. (array members of
          structures are deeply copied!) [2]
    << We can wrap array in a structure/class and return an instance
    of the struct/class. The reason for this work is, array members of
    structures are deeply copied. In below program deep copy happens
    when we returned instance is copied in main. >> [2]

    - advantage: returns a copy, not a pointer
    - problem: is the inner array is too long, maybe a copy is too large.
    - example: see retarray_within_struct


II.2 class's member  functions

e) VALID: return a reference to a member array (trivial); 
f) VALID: return a POINTER to a member array

   - problems (e & f):
     * Encapsulation is breached, 
     * Lifetime issues, 
     * Invariant are no longer sustainable (except returning const &)

g) ERROR: return a local variable. (trivial)

*/
/******************************************************************************/

void return_array_test();
//int* retarray_error_undefined();
int* retarray_dyn_alloc();
int* retarray_static();

struct arrWrap { 
    int arr[100]; 
}; 
struct arrWrap retarray_within_struct();




class ClassWithArrayMember
{
public:

  ClassWithArrayMember()
  {
    /* Some operations on arr[] */
    arr[0] = 10; 
    arr[1] = 20;    
  }

  //  return a reference to a member array
  typedef int TarrayMember[100];
  const TarrayMember& getArray() const { return arr; }

  const int *getArrayPtr() const { return arr; }

  
  // g) copy of a member as an array of characters
  ///@error address of local variable ‘retCode’ returned
  const char* GetElementAsCharArray()const
  {  
    // char intermediateCode[2 + 1]; // code ("10") + terminating null character
    // char retCode[2]; ///error address of local variable ‘retCode’ returned
    
    // snprintf(intermediateCode, 2+1, "%02d", arr[0]);
    // strncpy(retCode, intermediateCode, 2);
    // return retCode;

          return "aa";
  }


private:
  int arr[100];
};


/******************************************************************************/
/* III How to initialize an static array member ?                             */
/******************************************************************************/

class ClassWithStaticArrayMember
{
public:

  static const char * test()
  {
    memset(r_cadena, R_CADENA_INIT_VALUE, R_CADENA_LEN);
    strcpy(r_cadena, "E_DISPONIBLE_CAMBIO");  
    return r_cadena;
  }

  static const char * get_cadena()
  {
    return r_cadena;
  }

private:
   static const size_t R_CADENA_LEN = 100;
   static const char R_CADENA_INIT_VALUE = ' ';
   static char r_cadena[R_CADENA_LEN]; // return value for obtenerEstado;
};


///HERE static member init
char ClassWithStaticArrayMember::r_cadena[R_CADENA_LEN] = {};

///@test static member init
void init_static_array_test()
{
  std::cout << "III.a Init value: <" << ClassWithStaticArrayMember::get_cadena()
	    << '>'
	    << std::endl;
  
  std::cout << "III.b test value <" << ClassWithStaticArrayMember::test()
	    << '>'
	    << std::endl;
}


/******************************************************************************/

int main()
{
  std::cout << "\n\nI Passing arrays as function arguments" << std::endl;

  std::cout << "\nC TEST " << std::endl;
  fn_arguments_C_test();
  std::cout << std::endl;

  std::cout << "\nc++ TEST " << std::endl;
  fn_arguments_CPP_test();
  std::cout << std::endl; 
  std::cout << std::endl;


  std::cout << "\n\nII How to return a local array from a C/C++ function?" 
	    << std::endl;
  return_array_test();
  std::cout << std::endl;
  std::cout << std::endl;


  std::cout << "\n\nIII How to initialise an static array member?" 
	    << std::endl;
  init_static_array_test();
  std::cout << std::endl;
  std::cout << std::endl;

  
  return 0;
}

/******************************************************************************/
/* Implementation: I Passing arrays as function arguments                     */
/******************************************************************************/

void print_c1(const char *s, unsigned int len)
{
  std::cout << '[';
  std::cout << ' ';

  for (unsigned int i=0; i < len; ++i)
    std::cout << s[i] << ' ';

  std::cout << ']';
  std::cout << std::endl;
}

//------------------------------------------------------------------------------

void print_c2(const char s[], unsigned int len)
{
  std::cout << '[';
  std::cout << ' ';

  for (unsigned int i=0; i < len; ++i)
    std::cout << s[i] << ' ';

  std::cout << ']';
  std::cout << std::endl;
}

//------------------------------------------------------------------------------

///@warning , '\0' expected (undefined behaviour otherwise
void print_c3(const char *s)
{
  std::cout << '[';
  std::cout << s << ']';
  std::cout << std::endl;
}

//------------------------------------------------------------------------------

void print_c4(const char s[1000]) // equivalent, the dimension information is discarded
{
  std::cout << '[';
  std::cout << s << ']';
  std::cout << std::endl;
}

//------------------------------------------------------------------------------

///@warning NOT equivalent, due to the reference ('&'), the dimension
///MUST be exact (eg. 35)
void print_c6(const t_identifier &s)
{
  std::cout << '[';
  std::cout << s << ']';
  std::cout << std::endl;
}

//------------------------------------------------------------------------------

void print_c5(const t_identifier s) // equivalent
{
  std::cout << '[';
  std::cout << s << ']';
  std::cout << std::endl;
}

//------------------------------------------------------------------------------

void set_c1(char *s, unsigned int len)
{ 
  for (unsigned int i=0; i < len; ++i)
  {
    // unsigned int next_char = 1 + static_cast<unsigned int>(s[i]);
    // s[i]=static_cast<char>(next_char);
    s[i] = s[i] + 1;
  }

}

//------------------------------------------------------------------------------

void set_c2(char s[], unsigned int len)
{
  for (unsigned int i=0; i < len; ++i)
    s[i]+=1;  // ascii 1 
}


//==============================================================================

void fn_arguments_C_test()
{
  const unsigned int LEN_CADENA = 3;
  char cadena[LEN_CADENA] = {'2','5','R'};

  std::cout << "SALIDA: (char *s, unsigned int len): ";
  print_c1(cadena, LEN_CADENA);

  std::cout << "SALIDA: (char [], unsigned int len): ";
  print_c2(cadena, LEN_CADENA);

  /// set test

  set_c1(cadena, LEN_CADENA);
  print_c1(cadena, LEN_CADENA);
  set_c2(cadena, LEN_CADENA);
  print_c2(cadena, LEN_CADENA); // print_c1 == print_c2

  std::cout << "SALIDA: (char *) sin cerrar con '\0': ";
  print_c3(cadena);
  print_c4(cadena);
  std::cout << "SALIDA: (char *) cerrada con '\0': ";
  cadena[LEN_CADENA-1]='\0'; ///@warning cadena[LEN_CADENA]='\0' =>
			     ///cerramos fuera del array original =>
			     ///undefined
  print_c3(cadena);
  print_c4(cadena);

  
  //print_c6(cadena); //error len(cadena) = 3; esperado 35
  //   arrays_in_cpp.cpp:310: error: invalid initialization of reference of type ‘const char (&)[35]’ from expression of type ‘char [3]’
  // arrays_in_cpp.cpp:250: error: in passing argument 1 of ‘void print_c6(const char (&)[35])’
  const unsigned int LEN_CADENA_35 = 35;
  char cadena35[LEN_CADENA_35] = {"cadena35"};
  print_c6(cadena35);

  print_c5(cadena35);
  cadena[0]= 'O';
  cadena[1]= 'k';
  print_c5(cadena);
  
  
}

//==============================================================================

/// w.quora.com/In-C++-functions-why-are-arrays-passed-by-reference-by-default

// << In C++, C-style arrays are only passed by reference when the
//    function’s parameter is a reference to an array (or to a suitable
//    template parameter). >>


void byref1 
(const int (&a)[4],  // (&a) required unless typedef: 
                     // compiler error: declaration of ‘a’ as array of references
 unsigned int len)

//(const int (&a)[4], unsigned int len) 
//(const int (&a)[4]) // C++11
{ 
  //C++11
  //  for (int n : a) std::cout << n << ' '; 


  //  for (int n = 0; n < sizeof(a); ++n) // error sizeof(a) = 16 bits 

  for (unsigned int n = 0; n < len; ++n)
    std::cout << n << ' '; 

  /// compilaion error (const int (a) [4]: assignment of read-only location ‘a[0]
  ///  a[0] = 7; 
}

//------------------------------------------------------------------------------

void byref1_bis
(const T_ARRAY_ENTEROS_LEN_4 &a, //compiler OK
 unsigned int len)
{

  for (unsigned int n = 0; n < len; ++n)
    std::cout << n << ' '; 

}
 
//------------------------------------------------------------------------------

template<class A> 
void byref2(const A& a, unsigned int len)
//void byref2(const A& a)  //C++11
{ 
  //  for (int n : a) std::cout << n << ' ';  //c++11

  for (unsigned int n = 0; n < len; ++n)
    std::cout << n << ' '; 

}
 
//------------------------------------------------------------------------------

void fn_arguments_CPP_test()
{
  int x[4] = {1,2,3,4};
  byref1(x, 4);
  std::cout << std::endl;
  byref1_bis(x, 4);
  std::cout << std::endl;
  byref2(x, 3); // ojo, le paso un 3 pq me da la gana, pq no tiene sentido '\0'
  std::cout << std::endl;
}


/******************************************************************************/
/* Implementation: II How to return a local array from a C/C++ function?      */
/******************************************************************************/

void return_array_test()
{
  // a) ERROR
  // int* ptr = retarray_error_undefined();
  // std::cout << ptr[0] << " " << ptr[1] << std::endl;

  // b) VALID return dynamically allocated array (C++ code)
  std::cout << "II.b VALID return dynamically allocated array"
	    << std::endl;

  int * ptrb = retarray_dyn_alloc();
  std::cout << ptrb[0] << " " << ptrb[1] << std::endl;
  delete [] ptrb; ptrb = 0;

  // c) VALID return static array (C++ code)
  std::cout << "II.c VALID return static array"
	    << std::endl;
  int * ptrc = retarray_static();
  std::cout << ptrc[0] << " " << ptrc[1] << std::endl;

  // d) VALID return struct
  std::cout << "II.d VALID return a wrapper struct with the array inside"
	    << std::endl;
  struct arrWrap x = retarray_within_struct();
  std::cout << x.arr[0] << " " << x.arr[1] << std::endl;


  // e) VALID: return a reference to a member array
  std::cout << "II.e VALID: return a reference to a member array"
	    << std::endl;

  ClassWithArrayMember y;
  const ClassWithArrayMember::TarrayMember& yarr = y.getArray();
  std::cout << yarr[0] << " " << yarr[1] << std::endl;

  
  // f) VALID: return a POINTER to a member array
  std::cout << "II.f VALID: return a pointer to a member array"
	    << std::endl;
  const int* yarr_ptr = y.getArrayPtr();
  std::cout << yarr_ptr[0] << " " << yarr_ptr[1] << std::endl;

  //only first elemented is printed: (*yarr_ptr)  IS  yarr_ptr[0] 
  std::cout << *yarr_ptr << std::endl; 


  // g) error: address of local variable ‘retCode’ returned
  const char *char_value = y.GetElementAsCharArray();
  std::cout << char_value[0] << " " << char_value[1] << std::endl;

  
  // g) copy of a member array
  // int* ptr = retarray_error_undefined();
  // std::cout << ptr[0] << " " << ptr[1] << std::endl;

}

//------------------------------------------------------------------------------

// a) ERROR
//
// output: UNDEFINED: 10 20 or garbage or crash
//
// C code is the same
/*
int* retarray_error_undefined()  
{ 
  int arr[100];  ///COMPILER: warning: address of local variable ‘arr’ returned !
  
    // Some operations on arr[]
    arr[0] = 10; 
    arr[1] = 20; 
  
    return arr; 
} 
*/

//------------------------------------------------------------------------------

// b) VALID return dynamically allocated array (C++ code)
//
// C code is the same ('malloc' instead 'new')
int* retarray_dyn_alloc() 
{ 
    int* arr = new int[100]; 
  
    /* Some operations on arr[] */
    arr[0] = 10; 
    arr[1] = 20; 
  
    return arr; 
}
 
//------------------------------------------------------------------------------

// c) VALID return static array (C++ code)
//
// C code is the same ('printf' instead 'cout')
int* retarray_static() 
{ 
    static int arr [100]; 
  
    /* Some operations on arr[] */
    arr[0] = 10; 
    arr[1] = 20; 
  
    return arr; 
}
 
//------------------------------------------------------------------------------

// d) VALID: return an structure containing the array. 
//
// C code is the same.
struct arrWrap retarray_within_struct()
{ 
  struct arrWrap x; 
  
  x.arr[0] = 10; 
  x.arr[1] = 20; 
  
  return x; ///@warning deep copy executed => nor returning a temporary local var
}



/******************************************************************************/

