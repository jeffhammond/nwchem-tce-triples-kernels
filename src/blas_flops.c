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

#include "blas.h"

/* number of test repititions */
static const int nr = 1;

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
    //int colc = n;

    long mn = m*n;
    long mk = m*k;
    long kn = k*n;

    double * a = safemalloc( mk*sizeof(double) );
    double * b = safemalloc( kn*sizeof(double) );
    double * c = safemalloc( mn*sizeof(double) );
    if (a==NULL || b==NULL || c==NULL) {
        if (a!=NULL) safefree(a);
        if (b!=NULL) safefree(b);
        if (c!=NULL) safefree(c);
        printf("dgemm_flops: skipping test because memory could not be allocated \n");
        return 0.0;
    }

    OMP_PARALLEL
    {
        double denom = 2.0/(double)RAND_MAX;

        OMP_FOR
        for (long i=0; i<mk; i++)
            a[i] =  1.0 - denom*(double)rand();

        OMP_FOR
        for (long i=0; i<kn; i++)
            b[i] =  1.0 - denom*(double)rand();

        OMP_FOR
        for (long i=0; i<mn; i++)
            c[i] =  1.0 - denom*(double)rand();
    }

    char notrans = 'n';
    double alpha = 1.0;
    double beta  = 1.0;

    /* warmup */
    DGEMM_NAME(&notrans, &notrans, &rowa, &colb, &cola,
           &alpha, a, &rowa, b, &rowb,
           &beta, c, &rowc);
    double tt0 = omp_get_wtime();
    for (int r = 0; r<nr; r++)
        DGEMM_NAME(&notrans, &notrans, &rowa, &colb, &cola,
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

    safefree(c);
    safefree(b);
    safefree(a);

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
    if (a==NULL || x==NULL || y==NULL) {
    if (a!=NULL) safefree(a);
    if (x!=NULL) safefree(x);
    if (y!=NULL) safefree(y);
    printf("dger_flops: skipping test because memory could not be allocated \n");
        return 0.0;
    }

    OMP_PARALLEL
    {
        double denom = 2.0/(double)RAND_MAX;

        OMP_FOR
        for (long i=0; i<m; i++)
            x[i] =  1.0 - denom*(double)rand();

        OMP_FOR
        for (long i=0; i<n; i++)
            y[i] =  1.0 - denom*(double)rand();

        OMP_FOR
        for (long i=0; i<mn; i++)
            a[i] =  1.0 - denom*(double)rand();
    }

    int inc = 1;
    double alpha = 1.0;

    /* warmup */
    DGER_NAME(&m, &n, &alpha, x, &inc, y, &inc, a, &m);
    double tt0 = omp_get_wtime();
    for (int r = 0; r<nr; r++)
        DGER_NAME(&m, &n, &alpha, x, &inc, y, &inc, a, &m);
    double tt1 = omp_get_wtime();

    double dt = (tt1-tt0)/nr;
    double result = (2.e-9*mn/dt);
#ifdef DEBUG
    printf("DGER(m=%d,n=%d,alpha=%lf) took %lf seconds, GF/s = %lf \n",
           m, n, alpha, dt, result);
    fflush(stdout);
#endif

    safefree(a);
    safefree(y);
    safefree(x);

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
    if (x==NULL || y==NULL) {
    if (x!=NULL) safefree(x);
    if (y!=NULL) safefree(y);
    printf("daxpy_flops: skipping test because memory could not be allocated \n");
        return 0.0;
    }

    OMP_PARALLEL
    {
        double denom = 2.0/(double)RAND_MAX;

        OMP_FOR
        for (int i=0; i<n; i++)
            x[i] =  1.0 - denom*(double)rand();

        OMP_FOR
        for (int i=0; i<n; i++)
            y[i] =  1.0 - denom*(double)rand();
    }

    int inc = 1;
    double alpha = 1.0;

    /* warmup */
    DAXPY_NAME(&n, &alpha, x, &inc, y, &inc);
    double tt0 = omp_get_wtime();
    for (int r = 0; r<nr; r++)
        DAXPY_NAME(&n, &alpha, x, &inc, y, &inc);
    double tt1 = omp_get_wtime();

    double dt = (tt1-tt0)/nr;
    double result = (2.e-9*n/dt);
#ifdef DEBUG
    printf("DAXPY(n=%d,alpha=%lf) took %lf seconds, GF/s = %lf \n",
           n, alpha, dt, result);
    fflush(stdout);
#endif

    safefree(y);
    safefree(x);

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
    if (x==NULL || y==NULL) {
    if (x!=NULL) safefree(x);
    if (y!=NULL) safefree(y);
    printf("memcpy_bandwidth: skipping test because memory could not be allocated \n");
        return 0.0;
    }

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

    safefree(y);
    safefree(x);

    return result;
}
