#include <math.h>
#include <omp.h>

#include "safemalloc.h"
#include "ccsd_t_kernels.h"

double dgemm_flops(int m, int n, int k);

void zero_arrays(int tilesize, double * t1, double * t2, double * v2, double * t3)
{
    long long tile2    = tilesize*tilesize;
    long long tile4    = tile2*tile2;
    long long tile6    = tile4*tile2;
    long long tile7    = tile6*tilesize;

    #pragma omp parallel
    {
        #pragma omp for nowait schedule(static)
        for (long long i=0; i<tile2; i++)
            t1[i] = 1.0/(1.0+i);

        #pragma omp for nowait schedule(static)
        for (long long i=0; i<tile4; i++)
            t2[i] = 1.0/(1.0+i);

        #pragma omp for nowait schedule(static)
        for (long long i=0; i<tile4; i++)
            v2[i] = 1.0/(1.0+i);

        #pragma omp for nowait schedule(static)
        for (long long i=0; i<tile6; i++)
            t3[i] = 0.0;
    }

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
    int tilesize = ((argc>1) ? atoi(argv[1]) : 10);

    printf("testing NWChem CCSD(T) kernels on %d threads with tilesize %d \n", omp_get_max_threads(), tilesize);

    long long tile2    = tilesize*tilesize;
    long long tile4    = tile2*tile2;
    long long tile6    = tile4*tile2;
    long long tile7    = tile6*tilesize;

    /* approximate achievable peak by
     * T3(ijk,abc) = T2(ijk,l)*V(l,abc) */
    double eff_peak = dgemm_flops(tilesize*tilesize*tilesize,
                                  tilesize*tilesize*tilesize,
                                  tilesize);
    printf("effective peak flop/s of your processor is %lf \n", eff_peak);
    fflush(stdout);

    double tt0, tt1, ttt0, ttt1, dt;

    /* reference */
    double * t1r = safemalloc( tile2*sizeof(double) );
    double * t2r = safemalloc( tile4*sizeof(double) );
    double * v2r = safemalloc( tile4*sizeof(double) );
    double * t3r = safemalloc( tile6*sizeof(double) );

    /* threaded */
    double * t1o = safemalloc( tile2*sizeof(double) );
    double * t2o = safemalloc( tile4*sizeof(double) );
    double * v2o = safemalloc( tile4*sizeof(double) );
    double * t3o = safemalloc( tile6*sizeof(double) );

    zero_arrays(tilesize, t1r, t2r, v2r, t3r);

    {
#ifdef DO_S1
        ref_sd_t_s1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1r, v2r);
        ref_sd_t_s1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1r, v2r);
        ref_sd_t_s1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1r, v2r);
        ref_sd_t_s1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1r, v2r);
        ref_sd_t_s1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1r, v2r);
        ref_sd_t_s1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1r, v2r);
        ref_sd_t_s1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1r, v2r);
        ref_sd_t_s1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1r, v2r);
        ref_sd_t_s1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1r, v2r);
#endif

#ifdef DO_D1
        ref_sd_t_d1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2r, v2r);
        ref_sd_t_d1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2r, v2r);
        ref_sd_t_d1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2r, v2r);
        ref_sd_t_d1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2r, v2r);
        ref_sd_t_d1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2r, v2r);
        ref_sd_t_d1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2r, v2r);
        ref_sd_t_d1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2r, v2r);
        ref_sd_t_d1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2r, v2r);
        ref_sd_t_d1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2r, v2r);
#endif

#ifdef DO_D2
        ref_sd_t_d2_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2r, v2r);
        ref_sd_t_d2_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2r, v2r);
        ref_sd_t_d2_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2r, v2r);
        ref_sd_t_d2_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2r, v2r);
        ref_sd_t_d2_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2r, v2r);
        ref_sd_t_d2_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2r, v2r);
        ref_sd_t_d2_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2r, v2r);
        ref_sd_t_d2_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2r, v2r);
        ref_sd_t_d2_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2r, v2r);
#endif
    }

    for (int i=0; i<2; i++)
    {
        zero_arrays(tilesize, t1o, t2o, v2o, t3o);

        long long totalflops = 0;

        ttt0 = omp_get_wtime();

#ifdef DO_S1
        tt0 = omp_get_wtime();
        omp_sd_t_s1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_1_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_s1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_2_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_s1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_3_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_s1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_4_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_s1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_5_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_s1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_6_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_s1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_7_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_s1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_8_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_s1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_9_", dt, (2e-9*tile6)/dt );

        totalflops = 2*9*tile6;
#endif

#ifdef DO_D1
        tt0 = omp_get_wtime();
        omp_sd_t_d1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_1_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_2_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_3_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_4_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_5_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_6_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_7_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_8_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_9_", dt, (2e-9*tile7)/dt );

        totalflops = 2*9*tile7;
#endif

#ifdef DO_D2
        tt0 = omp_get_wtime();
        omp_sd_t_d2_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_1_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d2_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_2_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d2_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_3_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d2_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_4_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d2_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_5_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d2_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_6_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d2_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_7_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d2_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2o, v2o);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_8_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        omp_sd_t_d2_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2o, v2o);
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
    printf("\n");

    double e1 = diff_array(tile2, t1r, t1o);
    double e2 = diff_array(tile4, t2r, t2o);
    double e3 = diff_array(tile4, v2r, v2o);
    double e4 = diff_array(tile6, t3r, t3o);

    printf("differences: t1 = %lf, t2 = %lf, v2 = %lf, t3 = %30.15lf \n", e1, e2, e3, e4);

    double n1r = norm_array(tile2, t1r);
    double n2r = norm_array(tile4, t2r);
    double n3r = norm_array(tile4, v2r);
    double n4r = norm_array(tile6, t3r);

    printf("norms (r): t1 = %lf, t2 = %lf, v2 = %lf, t3 = %30.15lf \n", n1r, n2r, n3r, n4r);

    double n1o = norm_array(tile2, t1o);
    double n2o = norm_array(tile4, t2o);
    double n3o = norm_array(tile4, v2o);
    double n4o = norm_array(tile6, t3o);

    printf("norms (o): t1 = %lf, t2 = %lf, v2 = %lf, t3 = %30.15lf \n", n1o, n2o, n3o, n4o);

    free(t3o);
    free(v2o);
    free(t2o);
    free(t1o);

    free(t3r);
    free(v2r);
    free(t2r);
    free(t1r);

    printf("ALL DONE \n");
    fflush(stdout);

    return 0;
}
