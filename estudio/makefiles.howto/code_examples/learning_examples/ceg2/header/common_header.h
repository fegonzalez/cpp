#ifndef COMMON_HEADER_H
#define COMMON_HEADER_H

typedef int T;

const T nonlocal_var = 71; 


//------------------------------------------------------------------------------
// 1) Test type 1. Testing references as functions parameters
//------------------------------------------------------------------------------

/*!\fn void ftest1_ref_as_fnparam(T &);

  \brief Memory reference received as parameter to a function
*/
void ftest1_ref_as_fnparam(T&);



//------------------------------------------------------------------------------
// 2) Test type 2. Testing functions returning a reference 
//------------------------------------------------------------------------------

/*!\fn T& ftest2_return_local_ref();

  \brief Function returning a LOCAL VAR memory reference.
*/
/* T& ftest2_return_local_ref(); */


/*!\fn ftest2_return_nonlocal_ref();

  \brief Function returning a NON-LOCAL VAR memory reference.
*/
/* T& ftest2_return_nonlocal_ref(); */


//------------------------------------------------------------------------------
// 3) Test type 3. Testing read/write references
//------------------------------------------------------------------------------
   
void ftest3_read_ref_memory();  // reading the reference memory address
                                // i.e. asssert(...), operator==()

void ftest3_read_ref_data();    // reading the referenced data

void ftest3_write_ref_memory(); // writing the reference memory address

void ftest3_write_ref_data();   // writing the referenced data

#endif
