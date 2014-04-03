#ifndef FORTRAN_INTEGER_H
#define FORTRAN_INTEGER_H

#include <stdint.h>

#if FORTRAN_INTEGER_SIZE==4
typedef int32_t fint;
#else
typedef int64_t fint;
#endif

#endif // FORTRAN_INTEGER_H
