#include <stdio.h>

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#ifdef _OPENMP
#include <omp.h>
#else
double omp_get_wtime(void) { return 0.0; }
#endif

#include "ccsd_t_kernels.h"

/* if reps>1, verification is turned off */
const int reps = 1;

/****************************************************************/

int posix_memalign(void **memptr, size_t alignment, size_t size);

#define ALIGNMENT 128

void * safemalloc(size_t n)
{
    int rc = -1;
    void * ptr = NULL;
    rc = posix_memalign( &ptr, ALIGNMENT, n);

    if ( ptr==NULL || rc!=0 )
    {
        fprintf( stderr , "%ld bytes could not be allocated \n" , (long)n );
        exit(1);
    }

    return ptr;
}

/* if third argument is NULL, this function just prints the array in the second argument */
size_t arraydiff(size_t n, const double * restrict correct, const double * restrict test, char * label)
{
    size_t errors = 0;
    const double tolerance = 1.0e-13;

    if (correct!=NULL && test!=NULL) {
        for (size_t i=0; i<n; i++) {
            errors += ( fabs(correct[i]-test[i])<tolerance ? 0 : 1);
        }

        if (errors) {
            printf("############ there were %zu errors in %s ############\n", errors, label);
            printf("%10s %15s %15s \n", "index", "correct", label);
            for (size_t i=0; i<n; i++) {
                printf("%10d %15.7f %15.7f \n", i, correct[i], test[i]);
            }
        }
    } else if (correct!=NULL && test==NULL) {
        printf("%10s %15s \n", "index", label);
        for (size_t i=0; i<n; i++) {
            printf("%10d %15.7f \n", i, correct[i]);
        }
    } 

    return errors;
}

/****************************************************************/

int main(int argc, char * argv[])
{
    int tilesize = ((argc>1) ? atoi(argv[1]) : 10);

#ifdef _OPENMP
    int num_threads = omp_get_max_threads();
#else
    int num_threads = 1;
#endif

    printf("testing NWChem CCSD(T) kernels on %d threads with tilesize %d \n", num_threads, tilesize);
    fflush(stdout);

    size_t tile2 = tilesize*tilesize;
    size_t tile4 = tile2*tile2;
    size_t tile6 = tile4*tile2;
    size_t tile7 = tile6*tilesize;
   
    double * t1 = safemalloc( tile2*sizeof(double) );
    double * t2 = safemalloc( tile4*sizeof(double) );
    double * v2 = safemalloc( tile4*sizeof(double) );
    double * t3 = safemalloc( tile6*sizeof(double) );

#if DO_FORTRAN

    #pragma omp parallel
    {
        #pragma omp parallel for
        for (size_t i=0; i<tile2; i++) t1[i] = (1.0+i); 
        #pragma omp parallel for
        for (size_t i=0; i<tile4; i++) t2[i] = (1.0+i); 
        #pragma omp parallel for
        for (size_t i=0; i<tile4; i++) v2[i] = (1.0+i); 
        #pragma omp parallel for
        for (size_t i=0; i<tile6; i++) t3[i] = 0.0; 
    }

    for (int i=0; i<reps; i++)
    {
        unsigned long long totalflops = 0;
        double tt0, tt1, ttt0, ttt1, dt;

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

        totalflops += 2*9*tile6;
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

        totalflops += 2*9*tile7;
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

        totalflops += 2*9*tile7;
#endif

        ttt1 = omp_get_wtime();
        dt = ttt1-ttt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "total", dt, (1e-9*totalflops)/dt );

        fflush(stdout);
    }

#else // DO_FORTRAN

    #pragma omp parallel
    {
        #pragma omp parallel for
        for (size_t i=0; i<tile2; i++) t1[i] = (1.0+i); 
        #pragma omp parallel for
        for (size_t i=0; i<tile4; i++) t2[i] = (1.0+i); 
        #pragma omp parallel for
        for (size_t i=0; i<tile4; i++) v2[i] = (1.0+i); 
        #pragma omp parallel for
        for (size_t i=0; i<tile6; i++) t3[i] = 0.0; 
    }

    for (int i=0; i<reps; i++)
    {
        unsigned long long totalflops = 0;
        double tt0, tt1, ttt0, ttt1, dt;

        ttt0 = omp_get_wtime();

#ifdef DO_S1
        tt0 = omp_get_wtime();
        f2c_sd_t_s1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_s1_1_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_s1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_s1_2_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_s1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_s1_3_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_s1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_s1_4_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_s1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_s1_5_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_s1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_s1_6_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_s1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_s1_7_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_s1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_s1_8_", dt, (2e-9*tile6)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_s1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t1, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_s1_9_", dt, (2e-9*tile6)/dt );

        totalflops += 2*9*tile6;
#endif

#ifdef DO_D1
        tt0 = omp_get_wtime();
        f2c_sd_t_d1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_d1_1_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_d1_2_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_d1_3_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_d1_4_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_d1_5_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_d1_6_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_d1_7_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_d1_8_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_d1_9_", dt, (2e-9*tile7)/dt );

        totalflops += 2*9*tile7;
#endif

#ifdef DO_D2
        tt0 = omp_get_wtime();
        f2c_sd_t_d2_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_d2_1_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d2_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_d2_2_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d2_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_d2_3_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d2_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_d2_4_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d2_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_d2_5_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d2_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_d2_6_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d2_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_d2_7_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d2_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_d2_8_", dt, (2e-9*tile7)/dt );

        tt0 = omp_get_wtime();
        f2c_sd_t_d2_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3, t2, v2);
        tt1 = omp_get_wtime();
        dt = tt1-tt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "f2c_sd_t_d2_9_", dt, (2e-9*tile7)/dt );

        totalflops += 2*9*tile7;
#endif

        ttt1 = omp_get_wtime();
        dt = ttt1-ttt0;
        printf("%d: %s time = %lf seconds gigaflop/s = %lf \n", i, "total", dt, (1e-9*totalflops)/dt );

        fflush(stdout);
    }

#endif // DO_FORTRAN

    if (reps==1) {
        /* c = clean i.e. reference data */
        double * t1c = safemalloc( tile2*sizeof(double) );
        double * t2c = safemalloc( tile4*sizeof(double) );
        double * v2c = safemalloc( tile4*sizeof(double) );
        double * t3c = safemalloc( tile6*sizeof(double) );

        for (size_t i=0; i<tile2; i++) t1c[i] = (1.0+i); 
        for (size_t i=0; i<tile4; i++) t2c[i] = (1.0+i); 
        for (size_t i=0; i<tile4; i++) v2c[i] = (1.0+i); 
        for (size_t i=0; i<tile6; i++) t3c[i] = 0.0; 

#ifdef DO_S1
        clean_sd_t_s1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1c, v2c);
        clean_sd_t_s1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1c, v2c);
        clean_sd_t_s1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1c, v2c);
        clean_sd_t_s1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1c, v2c);
        clean_sd_t_s1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1c, v2c);
        clean_sd_t_s1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1c, v2c);
        clean_sd_t_s1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1c, v2c);
        clean_sd_t_s1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1c, v2c);
        clean_sd_t_s1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1c, v2c);
#endif
#ifdef DO_D1
        clean_sd_t_d1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2c, v2c);
        clean_sd_t_d1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2c, v2c);
        clean_sd_t_d1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2c, v2c);
        clean_sd_t_d1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2c, v2c);
        clean_sd_t_d1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2c, v2c);
        clean_sd_t_d1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2c, v2c);
        clean_sd_t_d1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2c, v2c);
        clean_sd_t_d1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2c, v2c);
        clean_sd_t_d1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2c, v2c);
#endif
#ifdef DO_D2
        clean_sd_t_d2_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2c, v2c);
        clean_sd_t_d2_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2c, v2c);
        clean_sd_t_d2_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2c, v2c);
        clean_sd_t_d2_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2c, v2c);
        clean_sd_t_d2_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2c, v2c);
        clean_sd_t_d2_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2c, v2c);
        clean_sd_t_d2_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2c, v2c);
        clean_sd_t_d2_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2c, v2c);
        clean_sd_t_d2_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2c, v2c);
#endif

        size_t et1 = arraydiff(tile2, t1c, t1, "t1");
        size_t et2 = arraydiff(tile4, t2c, t2, "t2");
        size_t ev2 = arraydiff(tile4, v2c, v2, "v2");
        size_t et3 = arraydiff(tile6, t3c, t3, "t3");

        if (et1==0 && et2==0 && ev2==0 && et3==0)
            printf("Congratulations!  Your code is correct. \n");
        else
            printf("Commence swearing!  Your code is wrong. \n");

        free(t3c);
        free(v2c);
        free(t2c);
        free(t1c);
    }

    free(t3);
    free(v2);
    free(t2);
    free(t1);

    printf("ALL DONE \n");
    fflush(stdout);

    return 0;
}



