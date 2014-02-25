#include <omp.h>

#include "safemalloc.h"

void dgemm_(char* , char* ,int* , int* , int* , double* , double* , int* , double* , int* , double* , double* , int* );

int main(int argc, char * argv[])
{
    printf("testing MKL DGEMM on %d threads \n", omp_get_max_threads());
    fflush(stdout);

    int m = ((argc>1) ? atoi(argv[1]) : 400);
    int n = ((argc>2) ? atoi(argv[2]) : 400);
    int k = ((argc>3) ? atoi(argv[3]) : 400);

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

    double tt0, tt1, i, dt;

    tt0 = omp_get_wtime();
    double * a = safemalloc( mk*sizeof(double) );
    double * b = safemalloc( kn*sizeof(double) );
    double * c = safemalloc( mn*sizeof(double) );
    tt1 = omp_get_wtime();
    dt = tt1-tt0;
    printf("memory allocation of %ld MiB took %lf seconds \n", 
           (mn+mk+kn)*sizeof(double)/(1024*1024), dt);
    fflush(stdout);

    tt0 = omp_get_wtime();
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
    tt1 = omp_get_wtime();
    dt = tt1-tt0;
    printf("memory initialization %lf seconds \n", dt);
    fflush(stdout);

    for (int i=0; i<2; i++)
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
        dt = tt1-tt0;
        printf("%d: DGEMM(%s,%s,m=%d,n=%d,k=%d,alpha=%lf,beta=%lf) took %lf seconds, GF/s = %lf \n", 
               i, "n", "n", m, n, k, alpha, beta, dt, 2.0*mnk*1e-9/dt);

        alpha = 1.0;
        beta  = 1.0;

        tt0 = omp_get_wtime();
        dgemm_("n","n", &rowa, &colb, &cola, 
               &alpha, a, &rowa, b, &rowb, 
               &beta, c, &rowc);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: DGEMM(%s,%s,m=%d,n=%d,k=%d,alpha=%lf,beta=%lf) took %lf seconds, GF/s = %lf \n", 
               i, "n", "n", m, n, k, alpha, beta, dt, 2.0*mnk*1e-9/dt);

        alpha = 0.5;
        beta  = 1.0;

        tt0 = omp_get_wtime();
        dgemm_("n","n", &rowa, &colb, &cola, 
               &alpha, a, &rowa, b, &rowb, 
               &beta, c, &rowc);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: DGEMM(%s,%s,m=%d,n=%d,k=%d,alpha=%lf,beta=%lf) took %lf seconds, GF/s = %lf \n", 
               i, "n", "n", m, n, k, alpha, beta, dt, 2.0*mnk*1e-9/dt);

        fflush(stdout);
    }

    tt0 = omp_get_wtime();
    free(c);
    free(b);
    free(a);
    tt1 = omp_get_wtime();
    dt = tt1-tt0;
    printf("memory deallocation took %lf seconds \n", dt);

    printf("ALL DONE \n");
    fflush(stdout);

    return 0;
}
