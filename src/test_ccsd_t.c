#include <omp.h>

#include "safemalloc.h"
#include "ccsd_t_kernels.h"

int main(int argc, char * argv[])
{
    int tilesize = ((argc>1) ? atoi(argv[1]) : 10);

    printf("testing NWChem CCSD(T) kernels on %d threads with tilesize %d \n", omp_get_max_threads(), tilesize);
    fflush(stdout);

    long long tile2    = tilesize*tilesize;
    long long tile4    = tile2*tile2;
    long long tile6    = tile4*tile2;
    long long tile7    = tile6*tilesize;
   
    double tt0, tt1, ttt0, ttt1, dt;

    double * t1 = safemalloc( tile2*sizeof(double) );
    double * t2 = safemalloc( tile4*sizeof(double) );
    double * v2 = safemalloc( tile4*sizeof(double) );
    double * t3 = safemalloc( tile6*sizeof(double) );

    tt0 = omp_get_wtime();
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
    tt1 = omp_get_wtime();
    dt = tt1-tt0;
    printf("memory initialization %lf seconds \n", dt);
    fflush(stdout);

    for (int i=0; i<2; i++)
    {
        long long totalflops = 0;

        ttt0 = omp_get_wtime();

#ifdef DO_S1
        tt0 = omp_get_wtime();
        sd_t_s1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_1_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        sd_t_s1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_2_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        sd_t_s1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_3_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        sd_t_s1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_4_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        sd_t_s1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_5_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        sd_t_s1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_6_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        sd_t_s1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_7_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        sd_t_s1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_8_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        sd_t_s1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_s1_9_", dt, (2e-9*tile6)/dt );

        totalflops = 2*9*tile6;
#endif

#ifdef DO_D1
        tt0 = omp_get_wtime();
        sd_t_d1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_1_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        sd_t_d1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_2_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        sd_t_d1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_3_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        sd_t_d1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_4_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        sd_t_d1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_5_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        sd_t_d1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_6_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        sd_t_d1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_7_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        sd_t_d1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_8_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        sd_t_d1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d1_9_", dt, (2e-9*tile7)/dt );

        totalflops = 2*9*tile7;
#endif

#ifdef DO_D2
        tt0 = omp_get_wtime();
        sd_t_d2_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_1_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        sd_t_d2_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_2_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        sd_t_d2_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_3_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        sd_t_d2_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_4_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        sd_t_d2_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_5_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        sd_t_d2_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_6_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        sd_t_d2_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_7_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        sd_t_d2_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "sd_t_d2_8_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        sd_t_d2_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
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

    free(t3);
    free(v2);
    free(t2);
    free(t1);

    printf("ALL DONE \n");
    fflush(stdout);

    return 0;
}
