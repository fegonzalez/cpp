#ifndef NONEXTERN_A_H_
#define NONEXTERN_A_H_

//int shared_var; // ill-formed: multiple definition (a.h and b.h)

extern int shared_var; // ok: extern declaration

#endif
