#ifndef NONEXTERN_B_H_
#define NONEXTERN_B_H_

//int shared_var; // ill-formed: multiple definition (a.h and b.h)

extern int shared_var; // ok: extern declaration

#endif
