#ifndef BLAS_H
#define BLAS_H

#ifdef BLAS_NO_UNDERSCORE
# define DGEMM_NAME dgemm
# define DGER_NAME dger
# define DAXPY_NAME daxpy
#else
# define DGEMM_NAME dgemm_
# define DGER_NAME dger_
# define DAXPY_NAME daxpy_
#endif

void DGEMM_NAME(char* , char* ,int* , int* , int* , double* , double* , int* , double* , int* , double* , double* , int* );
void DGER_NAME(int* m, int* n, double* alpha, double* x, int* incx, double* y, int* incy, double* a, int* lda);
void DAXPY_NAME(int* n, double* alpha, double* x, int* incx, double* y, int* incy);

#endif // BLAS_H
