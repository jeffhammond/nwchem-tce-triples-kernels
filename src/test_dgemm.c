#include <omp.h>

#include "safemalloc.h"

void dgemm_(char* , char* ,int* , int* , int* , double* , double* , int* , double* , int* , double* , double* , int* );

double dgemm_gflops(int m, int n, int k)
{
#ifdef DEBUG
    printf("testing DGEMM on %d threads with (m,n,k) = (%d,%d,%d) \n", omp_get_max_threads(), m, n, k);
    fflush(stdout);
#endif

    int mn = m*n;
    int mk = m*k;
    int kn = k*n;

    double mnk = (1.0*m)*(1.0*n)*(1.0*k);

    int rowc = m;
    int rowa = m;
    int cola = k;
    int rowb = k;
    int colb = n;
    int colc = n;

    double tt0, tt1, i, dt1, dt2, dt3;

    double * a = safemalloc( mk*sizeof(double) );
    double * b = safemalloc( kn*sizeof(double) );
    double * c = safemalloc( mn*sizeof(double) );

    #pragma omp parallel
    {
        #pragma omp for nowait
        for (int i=0; i<mk; i++)
            a[i] = 1.0/(1.0+i);

        #pragma omp for nowait
        for (int i=0; i<kn; i++)
            b[i] = 1.0/(1.0+i);

        #pragma omp for nowait
        for (int i=0; i<mn; i++)
            c[i] = 1.0/(1.0+i);
    }

    double result = -9999999.9;
    {
        double alpha;
        double beta;

        alpha = 1.0;
        beta  = 0.0;

        tt0 = omp_get_wtime();
        dgemm_("n","n", &rowa, &colb, &cola,
               &alpha, a, &rowa, b, &rowb,
               &beta, c, &rowc);
        tt1 = omp_get_wtime();
        dt1 = tt1-tt0;
#ifdef DEBUG
        printf("DGEMM(%c,%c,m=%d,n=%d,k=%d,alpha=%lf,beta=%lf) took %lf seconds, GF/s = %lf \n",
               'n', 'n', m, n, k, alpha, beta, dt1, 2.0*mnk*1.e-9/dt1);
#endif

        alpha = 1.0;
        beta  = 1.0;

        tt0 = omp_get_wtime();
        dgemm_("n","n", &rowa, &colb, &cola,
               &alpha, a, &rowa, b, &rowb,
               &beta, c, &rowc);
        tt1 = omp_get_wtime();
        dt2 = tt1-tt0;
        result = (2.0*mnk*1.e-9/dt2);
#ifdef DEBUG
        printf("DGEMM(%c,%c,m=%d,n=%d,k=%d,alpha=%lf,beta=%lf) took %lf seconds, GF/s = %lf \n",
               'n', 'n', m, n, k, alpha, beta, dt2, 2.0*mnk*1.e-9/dt2);
        printf("result = %lf \n", result);
#endif

        alpha = 0.5;
        beta  = 1.0;

        tt0 = omp_get_wtime();
        dgemm_("n","n", &rowa, &colb, &cola,
               &alpha, a, &rowa, b, &rowb,
               &beta, c, &rowc);
        tt1 = omp_get_wtime();
        dt3 = tt1-tt0;
#ifdef DEBUG
        printf("DGEMM(%c,%c,m=%d,n=%d,k=%d,alpha=%lf,beta=%lf) took %lf seconds, GF/s = %lf \n",
               'n', 'n', m, n, k, alpha, beta, dt3, 2.0*mnk*1.e-9/dt3);
#endif

        fflush(stdout);
    }

    free(c);
    free(b);
    free(a);

    return result;
}
