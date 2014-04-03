#include <string.h>
#include <math.h>

#ifdef _OPENMP
#include <omp.h>
#else
#include "fake_omp.h"
#endif
#include "pragma_openmp.h"
#include "pragma_vendor.h"

#include "safemalloc.h"

void dgemm_(char* , char* ,int* , int* , int* , double* , double* , int* , double* , int* , double* , double* , int* );
void dger_(int* m, int* n, double* alpha, double* x, int* incx, double* y, int* incy, double* a, int* lda);
void daxpy_(int* n, double* alpha, double* x, int* incx, double* y, int* incy);

/* number of test repititions */
const int nr = 1;

double dgemm_gflops(int m, int n, int k)
{
#ifdef DEBUG
    printf("testing DGEMM on %d threads with (m,n,k) = (%d,%d,%d) \n", omp_get_max_threads(), m, n, k);
    fflush(stdout);
#endif

    int rowc = m;
    int rowa = m;
    int cola = k;
    int rowb = k;
    int colb = n;
    int colc = n;

    long mn = m*n;
    long mk = m*k;
    long kn = k*n;

    double * a = safemalloc( mk*sizeof(double) );
    double * b = safemalloc( kn*sizeof(double) );
    double * c = safemalloc( mn*sizeof(double) );

    OMP_PARALLEL
    {
        double denom = 2.0/(double)RAND_MAX;

        OMP_FOR
        PRAGMA_IVDEP
        for (long i=0; i<mk; i++)
            a[i] =  1.0 - denom*(double)rand();

        OMP_FOR
        PRAGMA_IVDEP
        for (long i=0; i<kn; i++)
            b[i] =  1.0 - denom*(double)rand();

        OMP_FOR
        PRAGMA_IVDEP
        for (long i=0; i<mn; i++)
            c[i] =  1.0 - denom*(double)rand();
    }

    char notrans = 'n';
    double alpha = 1.0;
    double beta  = 1.0;

    /* warmup */
    dgemm_(&notrans, &notrans, &rowa, &colb, &cola,
           &alpha, a, &rowa, b, &rowb,
           &beta, c, &rowc);
    double tt0 = omp_get_wtime();
    for (int r = 0; r<nr; r++)
        dgemm_(&notrans, &notrans, &rowa, &colb, &cola,
               &alpha, a, &rowa, b, &rowb,
               &beta, c, &rowc);
    double tt1 = omp_get_wtime();

    unsigned long long mnk = m;
    mnk *= n;
    mnk *= k;
    double dt = (tt1-tt0)/nr;
    double result = (2.e-9*mnk/dt);
#ifdef DEBUG
    printf("DGEMM(%c,%c,m=%d,n=%d,k=%d,alpha=%lf,beta=%lf) took %lf seconds, GF/s = %lf \n",
           notrans, notrans, m, n, k, alpha, beta, dt, result);
    fflush(stdout);
#endif

    free(c);
    free(b);
    free(a);

    return result;
}

double dger_gflops(int m, int n)
{
#ifdef DEBUG
    printf("testing DGER on %d threads with (m,n) = (%d,%d) \n", omp_get_max_threads(), m, n);
    fflush(stdout);
#endif

    long mn = m*n;

    double * x = safemalloc( m*sizeof(double) );
    double * y = safemalloc( n*sizeof(double) );
    double * a = safemalloc( mn*sizeof(double) );

    OMP_PARALLEL
    {
        double denom = 2.0/(double)RAND_MAX;

        OMP_FOR
        PRAGMA_IVDEP
        for (long i=0; i<m; i++)
            x[i] =  1.0 - denom*(double)rand();

        OMP_FOR
        PRAGMA_IVDEP
        for (long i=0; i<n; i++)
            y[i] =  1.0 - denom*(double)rand();

        OMP_FOR
        PRAGMA_IVDEP
        for (long i=0; i<mn; i++)
            a[i] =  1.0 - denom*(double)rand();
    }

    int inc = 1;
    double alpha = 1.0;

    /* warmup */
    dger_(&m, &n, &alpha, x, &inc, y, &inc, a, &m);
    double tt0 = omp_get_wtime();
    for (int r = 0; r<nr; r++)
        dger_(&m, &n, &alpha, x, &inc, y, &inc, a, &m);
    double tt1 = omp_get_wtime();

    double dt = (tt1-tt0)/nr;
    double result = (2.e-9*mn/dt);
#ifdef DEBUG
    printf("DGER(m=%d,n=%d,alpha=%lf) took %lf seconds, GF/s = %lf \n",
           m, n, alpha, dt, result);
    fflush(stdout);
#endif

    free(a);
    free(y);
    free(x);

    return result;
}

double daxpy_gflops(int n)
{
#ifdef DEBUG
    printf("testing DAXPY on %d threads with n = %d \n", omp_get_max_threads(), n);
    fflush(stdout);
#endif

    double * x = safemalloc( n*sizeof(double) );
    double * y = safemalloc( n*sizeof(double) );

    OMP_PARALLEL
    {
        double denom = 2.0/(double)RAND_MAX;

        OMP_FOR
        PRAGMA_IVDEP
        for (int i=0; i<n; i++)
            x[i] =  1.0 - denom*(double)rand();

        OMP_FOR
        PRAGMA_IVDEP
        for (int i=0; i<n; i++)
            y[i] =  1.0 - denom*(double)rand();
    }

    int inc = 1;
    double alpha = 1.0;

    /* warmup */
    daxpy_(&n, &alpha, x, &inc, y, &inc);
    double tt0 = omp_get_wtime();
    for (int r = 0; r<nr; r++)
        daxpy_(&n, &alpha, x, &inc, y, &inc);
    double tt1 = omp_get_wtime();

    double dt = (tt1-tt0)/nr;
    double result = (2.e-9*n/dt);
#ifdef DEBUG
    printf("DAXPY(n=%d,alpha=%lf) took %lf seconds, GF/s = %lf \n",
           n, alpha, dt, result);
    fflush(stdout);
#endif

    free(y);
    free(x);

    return result;
}

double memcpy_bandwidth(size_t n)
{
#ifdef DEBUG
    printf("testing MEMCPY with %zu doubles\n", n);
    fflush(stdout);
#endif

    size_t b = n*sizeof(double);

    double * x = safemalloc(b);
    double * y = safemalloc(b);

    PRAGMA_IVDEP
    for (size_t i=0; i<n; i++)
        x[i] =  (double)i;

    PRAGMA_IVDEP
    for (size_t i=0; i<n; i++)
        y[i] =  0.0;

    /* warmup */
    memcpy(y, x, b);
    double tt0 = omp_get_wtime();
    for (int r = 0; r<nr; r++)
        memcpy(y, x, b);
    double tt1 = omp_get_wtime();

    double dt = (tt1-tt0)/nr;
    double result = 1.e-9*b/dt;
#ifdef DEBUG
    printf("MEMCPY of %zu bytes took %lf seconds, GB/s = %lf \n",
           b, dt, result);
    fflush(stdout);
#endif

    free(y);
    free(x);

    return result;
}
