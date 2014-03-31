#include <math.h>

#ifdef _OPENMP
#include <omp.h>
#else
#include "fake-omp.h"
#endif

#include "safemalloc.h"

void dgemm_(char* , char* ,int* , int* , int* , double* , double* , int* , double* , int* , double* , double* , int* );
void dger_(int* m, int* n, double* alpha, double* x, int* incx, double* y, int* incy, double* a, int* lda);

/* number of test repititions */
#ifdef __bgq__
const int nr = 1;
#else
const int nr = 10;
#endif

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

    #pragma omp parallel
    {
        double denom = 2.0/(double)RAND_MAX;

        #pragma omp for
        for (long i=0; i<mk; i++)
            a[i] =  1.0 - denom*(double)rand();

        #pragma omp for
        for (long i=0; i<kn; i++)
            b[i] =  1.0 - denom*(double)rand();

        #pragma omp for
        for (long i=0; i<mn; i++)
            c[i] =  1.0 - denom*(double)rand();
    }

    char notrans = 'n';
    double alpha = 1.0;
    double beta  = 1.0;

    double tt0 = omp_get_wtime();
    for (int r = 0; r<nr; r++)
        dgemm_(&notrans, &notrans, &rowa, &colb, &cola,
               &alpha, a, &rowa, b, &rowb,
               &beta, c, &rowc);
    double tt1 = omp_get_wtime();

    unsigned long long mnk = m*n*k;
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

    #pragma omp parallel
    {
        double denom = 2.0/(double)RAND_MAX;

        #pragma omp for
        for (long i=0; i<m; i++)
            x[i] =  1.0 - denom*(double)rand();

        #pragma omp for
        for (long i=0; i<n; i++)
            y[i] =  1.0 - denom*(double)rand();

        #pragma omp for
        for (long i=0; i<mn; i++)
            a[i] =  1.0 - denom*(double)rand();
    }

    int inc = 1;
    double alpha = 1.0;

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
