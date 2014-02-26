#include <math.h>
#include <omp.h>

#include "safemalloc.h"

void dgemm_(char* , char* ,int* , int* , int* , double* , double* , int* , double* , int* , double* , double* , int* );

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
    dgemm_(&notrans, &notrans, &rowa, &colb, &cola,
           &alpha, a, &rowa, b, &rowb,
           &beta, c, &rowc);
    double tt1 = omp_get_wtime();

    unsigned long long mnk = m*n*k;
    double dt = tt1-tt0;
    double result = (2.e-9*mnk/dt);
#ifdef DEBUG
    printf("DGEMM(%c,%c,m=%d,n=%d,k=%d,alpha=%lf,beta=%lf) took %lf seconds, GF/s = %lf \n",
           'n', 'n', m, n, k, alpha, beta, dt, result);
    fflush(stdout);
#endif

    free(c);
    free(b);
    free(a);

    return result;
}
