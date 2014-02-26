#include <math.h>
#include <omp.h>

#include "safemalloc.h"
#include "ccsd_t_kernels.h"

double dger_gflops(int m, int n);
double dgemm_gflops(int m, int n, int k);

void rand_array(long long n, double * a)
{
    #pragma omp parallel for schedule(static)
    for (long long i=0; i<n; i++)
        a[i] = 1.0 - 2*(double)rand()/(double)RAND_MAX;

    return;
}

void zero_array(long long n, double * a)
{
    #pragma omp parallel for schedule(static)
    for (long long i=0; i<n; i++)
        a[i] = 0.0;
    return;
}

void copy_array(long long n, double * a, double * b)
{
    #pragma omp parallel for schedule(static)
    for (long long i=0; i<n; i++)
        b[i] = a[i];
    return;
}

double norm_array(long long n, const double * a)
{
    double norm = 0.0;
    for (long long i=0; i<n; i++)
        norm += a[i]*a[i];

    return norm;
}

double diff_array(long long n, const double * a, const double * b)
{
    double diff = 0.0;
    for (long long i=0; i<n; i++)
        diff += fabs(a[i]-b[i]);

    return diff;
}

int main(int argc, char * argv[])
{
    int tilesize = ((argc>1) ? atoi(argv[1]) : 16);

    printf("testing NWChem CCSD(T) kernels on %d threads with tilesize %d \n", omp_get_max_threads(), tilesize);

    long long tile2    = tilesize*tilesize;
    long long tile4    = tile2*tile2;
    long long tile6    = tile4*tile2;
    long long tile7    = tile6*tilesize;

    double eff_peak = -9999.9;
    /* approximate achievable peak by
     * T3(ijk,abc) = T1(i,j)*V(k,abc) */
    eff_peak = dger_gflops(tilesize*tilesize,
                           tilesize*tilesize*tilesize*tilesize);
    printf("DGER  gigaflop/s of your processor is %lf \n", eff_peak);
    /* approximate achievable peak by
     * T3(ijk,abc) = T2(ijk,l)*V(l,abc) */
    eff_peak = dgemm_gflops(tilesize*tilesize*tilesize,
                            tilesize*tilesize*tilesize,
                            tilesize);
    printf("DGEMM gigaflop/s of your processor is %lf \n", eff_peak);
    fflush(stdout);

    double tt0, tt1, ttt0, ttt1, dt;

    /* reference */
    double * t1  = safemalloc( tile2*sizeof(double) );
    double * t2  = safemalloc( tile4*sizeof(double) );
    double * v2  = safemalloc( tile4*sizeof(double) );
    double * t3r = safemalloc( tile6*sizeof(double) );
    double * t3o = safemalloc( tile6*sizeof(double) );
    double * t3c = safemalloc( tile6*sizeof(double) );

    tt0 = omp_get_wtime();
    rand_array(tile2, t1);
    rand_array(tile4, t2);
    rand_array(tile4, v2);
    tt1 = omp_get_wtime();
    printf("randomized initialization took %lf seconds \n", tt1-tt0);

    printf("\nSTARTING FORTRAN REFERENCE KERNELS \n");
    fflush(stdout);
    for (int i=0; i<2; i++)
    {
        long long totalflops = 0;

        zero_array(tile6, t3r);

        ttt0 = omp_get_wtime();

#ifdef DO_S1
        tt0 = omp_get_wtime();
        omp_sd_t_s1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_1_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_s1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_2_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_s1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_3_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_s1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_4_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_s1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_5_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_s1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_6_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_s1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_7_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_s1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_8_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_s1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_9_", dt, (2e-9*tile6)/dt );

        totalflops = 2*9*tile6;
#endif

#ifdef DO_D1
        tt0 = omp_get_wtime();
        omp_sd_t_d1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_1_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_2_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_3_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_4_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_5_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_6_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_7_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_8_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_9_", dt, (2e-9*tile7)/dt );

        totalflops = 2*9*tile7;
#endif

#ifdef DO_D2
        tt0 = omp_get_wtime();
        omp_sd_t_d2_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_1_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d2_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_2_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d2_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_3_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d2_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_4_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d2_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_5_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d2_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_6_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d2_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_7_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d2_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_8_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d2_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_9_", dt, (2e-9*tile7)/dt );

        totalflops = 2*9*tile7;
#endif

        ttt1 = omp_get_wtime();
        dt = ttt1-ttt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "total", dt, (1e-9*totalflops)/dt );

        fflush(stdout);
    }

    printf("\nSTARTING FORTRAN OPENMP KERNELS \n");
    fflush(stdout);
    for (int i=0; i<2; i++)
    {
        long long totalflops = 0;

        zero_array(tile6, t3o);

        ttt0 = omp_get_wtime();

#ifdef DO_S1
        tt0 = omp_get_wtime();
        omp_sd_t_s1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_1_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_s1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_2_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_s1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_3_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_s1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_4_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_s1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_5_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_s1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_6_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_s1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_7_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_s1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_8_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_s1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_9_", dt, (2e-9*tile6)/dt );

        totalflops = 2*9*tile6;
#endif

#ifdef DO_D1
        tt0 = omp_get_wtime();
        omp_sd_t_d1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_1_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_2_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_3_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_4_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_5_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_6_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_7_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_8_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_9_", dt, (2e-9*tile7)/dt );

        totalflops = 2*9*tile7;
#endif

#ifdef DO_D2
        tt0 = omp_get_wtime();
        omp_sd_t_d2_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_1_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d2_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_2_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d2_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_3_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d2_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_4_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d2_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_5_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d2_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_6_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d2_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_7_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d2_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_8_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d2_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_9_", dt, (2e-9*tile7)/dt );

        totalflops = 2*9*tile7;
#endif

        ttt1 = omp_get_wtime();
        dt = ttt1-ttt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "total", dt, (1e-9*totalflops)/dt );

        fflush(stdout);
    }

#if DO_C_KERNELS
    printf("\nSTARTING C99 KERNELS \n");
    fflush(stdout);
    for (int i=0; i<2; i++)
    {
        long long totalflops = 0;

        zero_array(tile6, t3c);

        ttt0 = omp_get_wtime();

#ifdef DO_S1
        tt0 = omp_get_wtime();
        f2c_sd_t_s1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_1_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_s1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_2_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_s1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_3_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_s1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_4_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_s1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_5_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_s1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_6_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_s1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_7_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_s1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_8_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_s1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_9_", dt, (2e-9*tile6)/dt );

        totalflops = 2*9*tile6;
#endif

#ifdef DO_D1
        tt0 = omp_get_wtime();
        f2c_sd_t_d1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_1_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_2_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_3_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_4_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_5_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_6_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_7_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_8_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_9_", dt, (2e-9*tile7)/dt );

        totalflops = 2*9*tile7;
#endif

#ifdef DO_D2
        tt0 = omp_get_wtime();
        f2c_sd_t_d2_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_1_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d2_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_2_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d2_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_3_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d2_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_4_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d2_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_5_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d2_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_6_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d2_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_7_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d2_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_8_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d2_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_9_", dt, (2e-9*tile7)/dt );

        totalflops = 2*9*tile7;
#endif

        ttt1 = omp_get_wtime();
        dt = ttt1-ttt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "total", dt, (1e-9*totalflops)/dt );

        fflush(stdout);
    }
#endif // DO_C_KERNELS

    printf("\n");

    double e1 = diff_array(tile2, t1, t1);
    double e2 = diff_array(tile4, t2, t2);
    double e3 = diff_array(tile4, v2, v2);
    double e4 = diff_array(tile6, t3r, t3o);
    double e5 = diff_array(tile6, t3r, t3c);
    printf("differences: t1 = %lf, t2 = %lf, v2 = %lf, t3o = %30.15lf, t3c = %30.15lf \n", e1, e2, e3, e4, e5);
    if (fabs(e4)>1.e-7 || fabs(e5)>1.e-7) {
        printf("ERROR!!!\n");
        exit(1);
    }

    double n1  = norm_array(tile2, t1);
    double n2  = norm_array(tile4, t2);
    double n3  = norm_array(tile4, v2);
    double n4r = norm_array(tile6, t3r);
    double n4o = norm_array(tile6, t3o);
    double n4c = norm_array(tile6, t3c);
    printf("norm: t1 = %lf, t2 = %lf, v2 = %lf, t3 = %lf, %lf, %lf \n", n1, n2, n3, n4r, n4o, n4c);

    free(t3c);
    free(t3o);
    free(t3r);
    free(v2);
    free(t2);
    free(t1);

    printf("ALL DONE \n");
    fflush(stdout);

    return 0;
}
