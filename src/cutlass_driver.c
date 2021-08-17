#include <math.h>

#ifdef _OPENMP
#include <omp.h>
#else
#warning Fake OpenMP
#include "fake_omp.h"
#endif

#include "safemalloc.h"

#include "ccsd_t_kernels_cutlass.h"

/* how many times to iterate */
const int reps = 5;

void cutlass_driver(int kernel, int tilesize,
                    long long tile2, long long tile4, long long tile6, long long tile7,
                    double * t1, double * t2, double * v2, double * t3x)
{
    double tt0 = 0.0, tt1 = 0.0, ttt0 = 0.0, ttt1 = 0.0, dt = 0.0;

    tt0 = omp_get_wtime();
    rand_array(tile2, t1);
    rand_array(tile4, t2);
    rand_array(tile4, v2);
    tt1 = omp_get_wtime();
    printf("randomized initialization took %lf s \n", tt1-tt0);

    if (t3x==NULL) {
      printf("skipping CUTLASS kernels because memory was not allocated. \n");
    } else {
      printf("\nSTARTING CUTLASS KERNELS \n");
      fflush(stdout);
      for (int i=0; i<reps; i++)
      {
        long long totalflops = 0;
        zero_array(tile6, t3x);
        ttt0 = omp_get_wtime();
#ifdef DO_S1
        if (kernel<0 || kernel==1) {
            tt0 = omp_get_wtime();
            cut_sd_t_s1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_1", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==2) {
            tt0 = omp_get_wtime();
            cut_sd_t_s1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_2", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==3) {
            tt0 = omp_get_wtime();
            cut_sd_t_s1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_3", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==4) {
            tt0 = omp_get_wtime();
            cut_sd_t_s1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_4", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==5) {
            tt0 = omp_get_wtime();
            cut_sd_t_s1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_5", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==6) {
            tt0 = omp_get_wtime();
            cut_sd_t_s1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_6", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==7) {
            tt0 = omp_get_wtime();
            cut_sd_t_s1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_7", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==8) {
            tt0 = omp_get_wtime();
            cut_sd_t_s1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_8", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==9) {
            tt0 = omp_get_wtime();
            cut_sd_t_s1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_9", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
#endif
#ifdef DO_D1
        if (kernel<0 || kernel==1) {
            tt0 = omp_get_wtime();
            cut_sd_t_d1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_1", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==2) {
            tt0 = omp_get_wtime();
            cut_sd_t_d1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_2", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==3) {
            tt0 = omp_get_wtime();
            cut_sd_t_d1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_3", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==4) {
            tt0 = omp_get_wtime();
            cut_sd_t_d1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_4", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==5) {
            tt0 = omp_get_wtime();
            cut_sd_t_d1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_5", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==6) {
            tt0 = omp_get_wtime();
            cut_sd_t_d1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_6", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==7) {
            tt0 = omp_get_wtime();
            cut_sd_t_d1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_7", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==8) {
            tt0 = omp_get_wtime();
            cut_sd_t_d1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_8", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==9) {
            tt0 = omp_get_wtime();
            cut_sd_t_d1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_9", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
#endif
#ifdef DO_D2
        if (kernel<0 || kernel==1) {
            tt0 = omp_get_wtime();
            cut_sd_t_d2_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_1", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==2) {
            tt0 = omp_get_wtime();
            cut_sd_t_d2_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_2", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==3) {
            tt0 = omp_get_wtime();
            cut_sd_t_d2_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_3", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==4) {
            tt0 = omp_get_wtime();
            cut_sd_t_d2_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_4", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==5) {
            tt0 = omp_get_wtime();
            cut_sd_t_d2_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_5", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==6) {
            tt0 = omp_get_wtime();
            cut_sd_t_d2_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_6", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==7) {
            tt0 = omp_get_wtime();
            cut_sd_t_d2_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_7", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==8) {
            tt0 = omp_get_wtime();
            cut_sd_t_d2_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_8", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==9) {
            tt0 = omp_get_wtime();
            cut_sd_t_d2_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3x, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_9", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
#endif
        ttt1 = omp_get_wtime();
        dt = ttt1-ttt0;
        printf("%d: %s time = %lf s GF/s = %lf \n", i, "total", dt, (1e-9*totalflops)/dt );
        fflush(stdout);
      }
    }

}
