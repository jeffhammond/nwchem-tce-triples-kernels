#include <math.h>

#ifdef _OPENMP
#include <omp.h>
#else
#include "fake_omp.h"
#endif
#include "pragma_openmp.h"

#include "safemalloc.h"
#include "ccsd_t_kernels.h"

/* how many times to iterate */
const int reps = 5;

/* threshold to print an error message */
const double thresh = 1.0e-6;

double dgemm_gflops(int m, int n, int k);
double dger_gflops(int m, int n);
double daxpy_gflops(int n);
double memcpy_bandwidth(size_t n);

void print_array(long long n, double * a)
{
    if (a==NULL || n<=0) return;

    for (long long i=0; i<n; i++)
        printf("%d %lf\n",i,a[i]);
    fflush(stdout);
    return;
}

void print_array2(long long n, double * a, double * b)
{
    if (a==NULL || b==NULL || n<=0) return;

    for (long long i=0; i<n; i++)
        printf("%d %lf %lf\n",i,a[i],b[i]);
    fflush(stdout);
    return;
}

void rand_array(long long n, double * a)
{
    if (a==NULL || n<=0) return;

    OMP_PARALLEL_FOR
    for (long long i=0; i<n; i++)
        a[i] = 1.0 - 2*(double)rand()/(double)RAND_MAX;
    return;
}

void zero_array(long long n, double * a)
{
    if (a==NULL || n<=0) return;

    OMP_PARALLEL_FOR
    for (long long i=0; i<n; i++)
        a[i] = 0.0;
    return;
}

void copy_array(long long n, double * a, double * b)
{
    if (a==NULL || b==NULL || n<=0) return;

    OMP_PARALLEL_FOR
    for (long long i=0; i<n; i++)
        b[i] = a[i];
    return;
}

double norm_array(long long n, const double * a)
{
    if (a==NULL || n<=0) return 0.0;

    double norm = 0.0;
    OMP_PARALLEL_FOR_REDUCE_ADD(norm)
    for (long long i=0; i<n; i++)
        norm += a[i]*a[i];
    return norm;
}

double diff_array(long long n, const double * a, const double * b)
{
    if (a==NULL || b==NULL || n<=0) return 0.0;

    double diff = 0.0;
    OMP_PARALLEL_FOR_REDUCE_ADD(diff)
    for (long long i=0; i<n; i++)
        diff += fabs(a[i]-b[i]);
    return diff;
}

int main(int argc, char * argv[])
{
    int tilesize = ((argc>1) ? atoi(argv[1]) : 16);
    int kernel   = ((argc>2) ? atoi(argv[2]) : -1);

    long long tile2    = tilesize*tilesize;
    long long tile3    = tile2*tilesize;
    long long tile4    = tile2*tile2;
    long long tile6    = tile3*tile3;
    long long tile7    = tile4*tile3;

    printf("testing NWChem CCSD(T) kernels on %d threads with tilesize %d \n", omp_get_max_threads(), tilesize);

#if 0
    double eff_peak = -9999.9;

    /* approximate memory bandwidth (memcpy) */
    eff_peak = memcpy_bandwidth(tile6);
    printf("MEMCPY gigabytes/s of your processor is %lf \n", eff_peak);
    fflush(stdout);

    if (tilesize <= 32) /* test for overflow */ {
        /* approximate achievable peak for a rather large DAXPY */
        eff_peak = daxpy_gflops(tile6);
        printf("DAXPY GF/s of your processor is %lf \n", eff_peak);
        fflush(stdout);
    }

    /* approximate achievable peak by T3(ijk,abc) = T1(i,j)*V(k,abc) */
    eff_peak = dger_gflops(tile2, tile4);
    printf("DGER  GF/s of your processor is %lf \n", eff_peak);
    fflush(stdout);

    /* approximate achievable peak by T3(ijk,abc) = T2(ijk,l)*V(l,abc) */
    eff_peak = dgemm_gflops(tile3,
                            tile3,
                            tilesize);
    printf("DGEMM (k=t) GF/s of your processor is %lf \n", eff_peak);
    fflush(stdout);

    /* approximate achievable peak for a DGEMM with large enough k */
    eff_peak = dgemm_gflops(tile3, tile3, tile2);
    printf("DGEMM (k=t^2) GF/s of your processor is %lf \n", eff_peak);
    fflush(stdout);
#endif

    double tt0 = 0.0, tt1 = 0.0, ttt0 = 0.0, ttt1 = 0.0, dt = 0.0;

    /* reference */
    double * t1  = safemalloc( tile2*sizeof(double) );
    double * t2  = safemalloc( tile4*sizeof(double) );
    double * v2  = safemalloc( tile4*sizeof(double) );

    tt0 = omp_get_wtime();
    rand_array(tile2, t1);
    rand_array(tile4, t2);
    rand_array(tile4, v2);
    tt1 = omp_get_wtime();
    printf("randomized initialization took %lf s \n", tt1-tt0);

    double * t3o = safemalloc( tile6*sizeof(double) );
    if (t3o==NULL) {
      printf("skipping Fortran OpenMP kernels because memory could not be allocated. \n");
    } else {
      printf("\nSTARTING FORTRAN OPENMP KERNELS \n");
      fflush(stdout);
      for (int i=0; i<reps; i++)
      {
        long long totalflops = 0;
        zero_array(tile6, t3o);
        ttt0 = omp_get_wtime();
#ifdef DO_S1
        if (kernel<0 || kernel==1) {
            tt0 = omp_get_wtime();
            omp_sd_t_s1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_1", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==2) {
            tt0 = omp_get_wtime();
            omp_sd_t_s1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_2", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==3) {
            tt0 = omp_get_wtime();
            omp_sd_t_s1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_3", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==4) {
            tt0 = omp_get_wtime();
            omp_sd_t_s1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_4", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==5) {
            tt0 = omp_get_wtime();
            omp_sd_t_s1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_5", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==6) {
            tt0 = omp_get_wtime();
            omp_sd_t_s1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_6", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==7) {
            tt0 = omp_get_wtime();
            omp_sd_t_s1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_7", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==8) {
            tt0 = omp_get_wtime();
            omp_sd_t_s1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_8", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==9) {
            tt0 = omp_get_wtime();
            omp_sd_t_s1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_9", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
#endif
#ifdef DO_D1
        if (kernel<0 || kernel==1) {
            tt0 = omp_get_wtime();
            omp_sd_t_d1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_1", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==2) {
            tt0 = omp_get_wtime();
            omp_sd_t_d1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_2", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==3) {
            tt0 = omp_get_wtime();
            omp_sd_t_d1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_3", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==4) {
            tt0 = omp_get_wtime();
            omp_sd_t_d1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_4", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==5) {
            tt0 = omp_get_wtime();
            omp_sd_t_d1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_5", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==6) {
            tt0 = omp_get_wtime();
            omp_sd_t_d1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_6", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==7) {
            tt0 = omp_get_wtime();
            omp_sd_t_d1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_7", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==8) {
            tt0 = omp_get_wtime();
            omp_sd_t_d1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_8", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==9) {
            tt0 = omp_get_wtime();
            omp_sd_t_d1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_9", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
#endif
#ifdef DO_D2
        if (kernel<0 || kernel==1) {
            tt0 = omp_get_wtime();
            omp_sd_t_d2_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_1", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==2) {
            tt0 = omp_get_wtime();
            omp_sd_t_d2_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_2", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==3) {
            tt0 = omp_get_wtime();
            omp_sd_t_d2_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_3", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==4) {
            tt0 = omp_get_wtime();
            omp_sd_t_d2_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_4", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==5) {
            tt0 = omp_get_wtime();
            omp_sd_t_d2_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_5", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==6) {
            tt0 = omp_get_wtime();
            omp_sd_t_d2_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_6", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==7) {
            tt0 = omp_get_wtime();
            omp_sd_t_d2_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_7", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==8) {
            tt0 = omp_get_wtime();
            omp_sd_t_d2_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_8", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==9) {
            tt0 = omp_get_wtime();
            omp_sd_t_d2_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3o, t2, v2);
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

    double * t3r = safemalloc( tile6*sizeof(double) );
    if (t3r==NULL) {
      printf("skipping Fortran reference kernels because memory could not be allocated. \n");
    } else {
      printf("\nSTARTING FORTRAN REFERENCE KERNELS \n");
      fflush(stdout);
      for (int i=0; i<reps; i++)
      {
        long long totalflops = 0;
        zero_array(tile6, t3r);
        ttt0 = omp_get_wtime();
#ifdef DO_S1
        if (kernel<0 || kernel==1) {
            tt0 = omp_get_wtime();
            ref_sd_t_s1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_1", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==2) {
            tt0 = omp_get_wtime();
            ref_sd_t_s1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_2", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==3) {
            tt0 = omp_get_wtime();
            ref_sd_t_s1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_3", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==4) {
            tt0 = omp_get_wtime();
            ref_sd_t_s1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_4", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==5) {
            tt0 = omp_get_wtime();
            ref_sd_t_s1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_5", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==6) {
            tt0 = omp_get_wtime();
            ref_sd_t_s1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_6", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==7) {
            tt0 = omp_get_wtime();
            ref_sd_t_s1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_7", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==8) {
            tt0 = omp_get_wtime();
            ref_sd_t_s1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_8", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==9) {
            tt0 = omp_get_wtime();
            ref_sd_t_s1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_9", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
#endif
#ifdef DO_D1
        if (kernel<0 || kernel==1) {
            tt0 = omp_get_wtime();
            ref_sd_t_d1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_1", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==2) {
            tt0 = omp_get_wtime();
            ref_sd_t_d1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_2", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==3) {
            tt0 = omp_get_wtime();
            ref_sd_t_d1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_3", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==4) {
            tt0 = omp_get_wtime();
            ref_sd_t_d1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_4", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==5) {
            tt0 = omp_get_wtime();
            ref_sd_t_d1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_5", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==6) {
            tt0 = omp_get_wtime();
            ref_sd_t_d1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_6", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==7) {
            tt0 = omp_get_wtime();
            ref_sd_t_d1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_7", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==8) {
            tt0 = omp_get_wtime();
            ref_sd_t_d1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_8", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==9) {
            tt0 = omp_get_wtime();
            ref_sd_t_d1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_9", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
#endif
#ifdef DO_D2
        if (kernel<0 || kernel==1) {
            tt0 = omp_get_wtime();
            ref_sd_t_d2_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_1", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==2) {
            tt0 = omp_get_wtime();
            ref_sd_t_d2_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_2", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==3) {
            tt0 = omp_get_wtime();
            ref_sd_t_d2_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_3", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==4) {
            tt0 = omp_get_wtime();
            ref_sd_t_d2_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_4", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==5) {
            tt0 = omp_get_wtime();
            ref_sd_t_d2_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_5", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==6) {
            tt0 = omp_get_wtime();
            ref_sd_t_d2_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_6", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==7) {
            tt0 = omp_get_wtime();
            ref_sd_t_d2_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_7", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==8) {
            tt0 = omp_get_wtime();
            ref_sd_t_d2_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_8", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==9) {
            tt0 = omp_get_wtime();
            ref_sd_t_d2_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3r, t2, v2);
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

#if DO_C_KERNELS
    double * t3c = safemalloc( tile6*sizeof(double) );
    if (t3c==NULL) {
      printf("skipping C 1-D kernels because memory could not be allocated. \n");
    } else {
      printf("\nSTARTING C 1-D KERNELS \n");
      fflush(stdout);
      for (int i=0; i<reps; i++)
      {
        long long totalflops = 0;
        zero_array(tile6, t3c);
        ttt0 = omp_get_wtime();
#ifdef DO_S1
        if (kernel<0 || kernel==1) {
            tt0 = omp_get_wtime();
            c1d_sd_t_s1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_1", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==2) {
            tt0 = omp_get_wtime();
            c1d_sd_t_s1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_2", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==3) {
            tt0 = omp_get_wtime();
            c1d_sd_t_s1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_3", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==4) {
            tt0 = omp_get_wtime();
            c1d_sd_t_s1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_4", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==5) {
            tt0 = omp_get_wtime();
            c1d_sd_t_s1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_5", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==6) {
            tt0 = omp_get_wtime();
            c1d_sd_t_s1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_6", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==7) {
            tt0 = omp_get_wtime();
            c1d_sd_t_s1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_7", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==8) {
            tt0 = omp_get_wtime();
            c1d_sd_t_s1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_8", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==9) {
            tt0 = omp_get_wtime();
            c1d_sd_t_s1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_9", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
#endif
#ifdef DO_D1
        if (kernel<0 || kernel==1) {
            tt0 = omp_get_wtime();
            c1d_sd_t_d1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_1", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==2) {
            tt0 = omp_get_wtime();
            c1d_sd_t_d1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_2", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==3) {
            tt0 = omp_get_wtime();
            c1d_sd_t_d1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_3", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==4) {
            tt0 = omp_get_wtime();
            c1d_sd_t_d1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_4", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==5) {
            tt0 = omp_get_wtime();
            c1d_sd_t_d1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_5", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==6) {
            tt0 = omp_get_wtime();
            c1d_sd_t_d1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_6", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==7) {
            tt0 = omp_get_wtime();
            c1d_sd_t_d1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_7", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==8) {
            tt0 = omp_get_wtime();
            c1d_sd_t_d1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_8", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==9) {
            tt0 = omp_get_wtime();
            c1d_sd_t_d1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_9", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
#endif
#ifdef DO_D2
        if (kernel<0 || kernel==1) {
            tt0 = omp_get_wtime();
            c1d_sd_t_d2_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_1", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==2) {
            tt0 = omp_get_wtime();
            c1d_sd_t_d2_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_2", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==3) {
            tt0 = omp_get_wtime();
            c1d_sd_t_d2_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_3", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==4) {
            tt0 = omp_get_wtime();
            c1d_sd_t_d2_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_4", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==5) {
            tt0 = omp_get_wtime();
            c1d_sd_t_d2_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_5", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==6) {
            tt0 = omp_get_wtime();
            c1d_sd_t_d2_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_6", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==7) {
            tt0 = omp_get_wtime();
            c1d_sd_t_d2_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_7", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==8) {
            tt0 = omp_get_wtime();
            c1d_sd_t_d2_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_8", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==9) {
            tt0 = omp_get_wtime();
            c1d_sd_t_d2_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3c, t2, v2);
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

    //double * t3d = safemalloc( tile6*sizeof(double) );
#if 0
    if (t3d==NULL) {
      printf("skipping C N-D kernels because memory could not be allocated. \n");
    } else {
      printf("\nSTARTING C N-D KERNELS \n");
      fflush(stdout);
      for (int i=0; i<reps; i++)
      {
        long long totalflops = 0;
        zero_array(tile6, t3d);
        ttt0 = omp_get_wtime();
#ifdef DO_S1
        if (kernel<0 || kernel==1) {
            tt0 = omp_get_wtime();
            cNd_sd_t_s1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_1", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==2) {
            tt0 = omp_get_wtime();
            cNd_sd_t_s1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_2", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==3) {
            tt0 = omp_get_wtime();
            cNd_sd_t_s1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_3", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==4) {
            tt0 = omp_get_wtime();
            cNd_sd_t_s1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_4", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==5) {
            tt0 = omp_get_wtime();
            cNd_sd_t_s1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_5", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==6) {
            tt0 = omp_get_wtime();
            cNd_sd_t_s1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_6", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==7) {
            tt0 = omp_get_wtime();
            cNd_sd_t_s1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_7", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==8) {
            tt0 = omp_get_wtime();
            cNd_sd_t_s1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_8", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==9) {
            tt0 = omp_get_wtime();
            cNd_sd_t_s1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_9", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
#endif
#ifdef DO_D1
        if (kernel<0 || kernel==1) {
            tt0 = omp_get_wtime();
            cNd_sd_t_d1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_1", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==2) {
            tt0 = omp_get_wtime();
            cNd_sd_t_d1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_2", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==3) {
            tt0 = omp_get_wtime();
            cNd_sd_t_d1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_3", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==4) {
            tt0 = omp_get_wtime();
            cNd_sd_t_d1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_4", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==5) {
            tt0 = omp_get_wtime();
            cNd_sd_t_d1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_5", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==6) {
            tt0 = omp_get_wtime();
            cNd_sd_t_d1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_6", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==7) {
            tt0 = omp_get_wtime();
            cNd_sd_t_d1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_7", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==8) {
            tt0 = omp_get_wtime();
            cNd_sd_t_d1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_8", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==9) {
            tt0 = omp_get_wtime();
            cNd_sd_t_d1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_9", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
#endif
#ifdef DO_D2
        if (kernel<0 || kernel==1) {
            tt0 = omp_get_wtime();
            cNd_sd_t_d2_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_1", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==2) {
            tt0 = omp_get_wtime();
            cNd_sd_t_d2_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_2", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==3) {
            tt0 = omp_get_wtime();
            cNd_sd_t_d2_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_3", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==4) {
            tt0 = omp_get_wtime();
            cNd_sd_t_d2_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_4", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==5) {
            tt0 = omp_get_wtime();
            cNd_sd_t_d2_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_5", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==6) {
            tt0 = omp_get_wtime();
            cNd_sd_t_d2_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_6", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==7) {
            tt0 = omp_get_wtime();
            cNd_sd_t_d2_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_7", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==8) {
            tt0 = omp_get_wtime();
            cNd_sd_t_d2_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_8", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==9) {
            tt0 = omp_get_wtime();
            cNd_sd_t_d2_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3d, t2, v2);
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
#endif // C1D disabled
#endif // DO_C_KERNELS

    double * t3b = safemalloc( tile6*sizeof(double) );
    if (t3b==NULL) {
      printf("skipping Fortran-BLAS kernels because memory could not be allocated. \n");
    } else {
      printf("\nSTARTING FORTRAN-BLAS KERNELS \n");
      fflush(stdout);
      for (int i=0; i<reps; i++)
      {
        long long totalflops = 0;
        zero_array(tile6, t3b);
        ttt0 = omp_get_wtime();
#ifdef DO_S1
        if (kernel<0 || kernel==1) {
            tt0 = omp_get_wtime();
            blas_sd_t_s1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_1", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==2) {
            tt0 = omp_get_wtime();
            blas_sd_t_s1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_2", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==3) {
            tt0 = omp_get_wtime();
            blas_sd_t_s1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_3", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==4) {
            tt0 = omp_get_wtime();
            blas_sd_t_s1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_4", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==5) {
            tt0 = omp_get_wtime();
            blas_sd_t_s1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_5", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==6) {
            tt0 = omp_get_wtime();
            blas_sd_t_s1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_6", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==7) {
            tt0 = omp_get_wtime();
            blas_sd_t_s1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_7", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==8) {
            tt0 = omp_get_wtime();
            blas_sd_t_s1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_8", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==9) {
            tt0 = omp_get_wtime();
            blas_sd_t_s1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t1, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_9", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
#endif
#ifdef DO_D1
        if (kernel<0 || kernel==1) {
            tt0 = omp_get_wtime();
            blas_sd_t_d1_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_1", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==2) {
            tt0 = omp_get_wtime();
            blas_sd_t_d1_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_2", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==3) {
            tt0 = omp_get_wtime();
            blas_sd_t_d1_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_3", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==4) {
            tt0 = omp_get_wtime();
            blas_sd_t_d1_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_4", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==5) {
            tt0 = omp_get_wtime();
            blas_sd_t_d1_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_5", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==6) {
            tt0 = omp_get_wtime();
            blas_sd_t_d1_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_6", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==7) {
            tt0 = omp_get_wtime();
            blas_sd_t_d1_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_7", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==8) {
            tt0 = omp_get_wtime();
            blas_sd_t_d1_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_8", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==9) {
            tt0 = omp_get_wtime();
            blas_sd_t_d1_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_9", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
#endif
#ifdef DO_D2
        if (kernel<0 || kernel==1) {
            tt0 = omp_get_wtime();
            blas_sd_t_d2_1_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_1", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==2) {
            tt0 = omp_get_wtime();
            blas_sd_t_d2_2_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_2", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==3) {
            tt0 = omp_get_wtime();
            blas_sd_t_d2_3_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_3", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==4) {
            tt0 = omp_get_wtime();
            blas_sd_t_d2_4_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_4", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==5) {
            tt0 = omp_get_wtime();
            blas_sd_t_d2_5_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_5", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==6) {
            tt0 = omp_get_wtime();
            blas_sd_t_d2_6_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_6", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==7) {
            tt0 = omp_get_wtime();
            blas_sd_t_d2_7_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_7", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==8) {
            tt0 = omp_get_wtime();
            blas_sd_t_d2_8_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t2, v2);
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_8", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==9) {
            tt0 = omp_get_wtime();
            blas_sd_t_d2_9_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, t3b, t2, v2);
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

    printf("\n");
    double diff_t3o = diff_array(tile6, t3r, t3o);
    printf("||t3o-t3r||_1 = %30.15lf %s\n", diff_t3o, diff_t3o > thresh ? "(FAIL)" : "");
#if DO_C_KERNELS
    double diff_t3c = diff_array(tile6, t3r, t3c);
    printf("||t3c-t3r||_1 = %30.15lf %s\n", diff_t3c, diff_t3c > thresh ? "(FAIL)" : "");
    //double diff_t3d = diff_array(tile6, t3r, t3d);
    //printf("||t3d-t3r||_1 = %30.15lf %s\n", diff_t3d, diff_t3d > thresh ? "(XFAIL)" : "");
#endif // DO_C_KERNELS
    double diff_t3b = diff_array(tile6, t3r, t3b);
    printf("||t3b-t3r||_1 = %30.15lf %s\n", diff_t3b, diff_t3b > thresh ? "(FAIL)" : "");
    if (diff_t3b>thresh) {
        print_array2(tile6, t3r, t3b);
    }

    double n1  = norm_array(tile2, t1);
    double n2  = norm_array(tile4, t2);
    double n3  = norm_array(tile4, v2);
    printf("norm: t1 = %lf, t2 = %lf, v2 = %lf\n", n1, n2, n3);
    double n4r = norm_array(tile6, t3r);
    printf("norm: t3r = %lf\n", n4r);
    double n4o = norm_array(tile6, t3o);
    printf("norm: t3o = %lf\n", n4o);
#if DO_C_KERNELS
    double n4c = norm_array(tile6, t3c);
    printf("norm: t3c = %lf\n", n4c);
    //double n4d = norm_array(tile6, t3d);
    //printf("norm: t3d = %lf <<< This will not agree.\n", n4d);
#endif
    double n4b = norm_array(tile6, t3b);
    printf("norm: t3b = %lf\n", n4b);

    safefree(t3b);
#if DO_C_KERNELS
    //safefree(t3d);
    safefree(t3c);
#endif
    safefree(t3o);
    safefree(t3r);
    safefree(v2);
    safefree(t2);
    safefree(t1);

    printf("ALL DONE \n");
    fflush(stdout);

    return 0;
}
