#if USE_CUBLAS

#include <string.h>
#include <math.h>

#ifdef _OPENMP
#include <omp.h>
#else
#include "fake_omp.h"
#endif
#include "pragma_openmp.h"
#include "pragma_vendor.h"

#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>
#include <cublas_v2.h>

#define USE_CURAND 1
#ifdef USE_CURAND
#include <curand.h>
static curandGenerator_t gen;
#endif

// safemalloc uses cudaMallocManaged
#define USE_CUDA_UM 1
#include "safemalloc.h"

/* number of test repititions */
static const int nr = 1000;

void init(void)
{
    int rc = cudaDeviceSynchronize();
    if (rc != cudaSuccess)  {
        printf("cudaDeviceSynchronize returned %d\n", rc);
    }
   
#if USE_CURAND
    rc = curandCreateGenerator(&gen, CURAND_RNG_PSEUDO_DEFAULT);
    if (rc != cudaSuccess)  {
        printf("curandCreateGenerator returned %d\n", rc);
    }

    rc = curandSetPseudoRandomGeneratorSeed(gen, 1234ULL);
    if (rc != cudaSuccess)  {
        printf("curandSetPseudoRandomGeneratorSeed returned %d\n", rc);
    }
#endif

    rc = cudaDeviceSynchronize();
    if (rc != cudaSuccess)  {
        printf("cudaDeviceSynchronize returned %d\n", rc);
    }
}

void final(void)
{
    int rc = cudaDeviceSynchronize();
    if (rc != cudaSuccess)  {
        printf("cudaDeviceSynchronize returned %d\n", rc);
    }

#if USE_CURAND
    rc = curandDestroyGenerator(gen);
    if (rc != cudaSuccess)  {
        printf("curandDestroyGenerator returned %d\n", rc);
    }
#endif
}

double cudgemm_gflops(int m, int n, int k)
{
#ifdef DEBUG
    printf("testing CUBLAS DGEMM with (m,n,k) = (%d,%d,%d) \n", m, n, k);
    fflush(stdout);
#endif

    int rowc = m;
    int rowa = m;
    int cola = k;
    int rowb = k;
    int colb = n;
    //int colc = n;

    long mn = m*n;
    long mk = m*k;
    long kn = k*n;

    double * a = safemalloc( mk*sizeof(double) );
    double * b = safemalloc( kn*sizeof(double) );
    double * c = safemalloc( mn*sizeof(double) );
    if (a==NULL || b==NULL || c==NULL) {
        if (a!=NULL) safefree(a);
        if (b!=NULL) safefree(b);
        if (c!=NULL) safefree(c);
        printf("dgemm_flops: skipping test because memory could not be allocated \n");
        return 0.0;
    }

#if USE_CURAND
    {
        int rc;
        
        rc = curandGenerateUniformDouble(gen, a, mk);
        if (rc != cudaSuccess)  {
            printf("curandGenerateUniformDouble returned %d\n", rc);
        }
        rc = curandGenerateUniformDouble(gen, b, kn);
        if (rc != cudaSuccess)  {
            printf("curandGenerateUniformDouble returned %d\n", rc);
        }
        rc = curandGenerateUniformDouble(gen, c, mn);
        if (rc != cudaSuccess)  {
            printf("curandGenerateUniformDouble returned %d\n", rc);
	}
    }
#else
    {
        double denom = 2.0/(double)RAND_MAX;

        for (long i=0; i<mk; i++)
            a[i] =  1.0 - denom*(double)rand();

        for (long i=0; i<kn; i++)
            b[i] =  1.0 - denom*(double)rand();

        for (long i=0; i<mn; i++)
            c[i] =  1.0 - denom*(double)rand();
    }
#endif

    cublasOperation_t notrans = CUBLAS_OP_N;
    double alpha = 1.0;
    double beta  = 1.0;

    cublasHandle_t h;
    int rc = cublasCreate(&h);
    if (rc != cudaSuccess)  {
        printf("cublasCreate returned %d\n", rc);
    }

    /* warmup */
    cudaDeviceSynchronize();
    rc = cublasDgemm(h, notrans, notrans, rowa, colb, cola,
                         &alpha, a, rowa, b, rowb,
                         &beta, c, rowc);
    if (rc != cudaSuccess)  {
        printf("cublasDgemm returned %d\n", rc);
    }
    cudaDeviceSynchronize();
    double tt0 = omp_get_wtime();
    for (int r = 0; r<nr; r++) {
        cublasDgemm(h, notrans, notrans, rowa, colb, cola,
                    &alpha, a, rowa, b, rowb,
                    &beta, c, rowc);
    }
    cudaDeviceSynchronize();
    double tt1 = omp_get_wtime();
   
    rc = cublasDestroy(h);
    if (rc != cudaSuccess)  {
        printf("cublasDestroy returned %d\n", rc);
    }

    double mnk = m;
    mnk *= n;
    mnk *= k;
    printf("mnk=%lf\n",mnk);
    double dt = (tt1-tt0)/nr;
    double result = (2.e-9*mnk/dt);
#ifdef DEBUG
    printf("CUBLAS DGEMM(%c,%c,m=%d,n=%d,k=%d,alpha=%lf,beta=%lf) took %lf seconds, GF/s = %lf \n",
           notrans, notrans, m, n, k, alpha, beta, dt, result);
    fflush(stdout);
#endif

    safefree(c);
    safefree(b);
    safefree(a);

    return result;
}

double cudger_gflops(int m, int n)
{
#ifdef DEBUG
    printf("testing CUBLAS DGER with (m,n) = (%d,%d) \n", m, n);
    fflush(stdout);
#endif

    long mn = m*n;

    double * x = safemalloc( m*sizeof(double) );
    double * y = safemalloc( n*sizeof(double) );
    double * a = safemalloc( mn*sizeof(double) );
    if (a==NULL || x==NULL || y==NULL) {
    if (a!=NULL) safefree(a);
    if (x!=NULL) safefree(x);
    if (y!=NULL) safefree(y);
    printf("dger_flops: skipping test because memory could not be allocated \n");
        return 0.0;
    }

#if USE_CURAND
    {
        int rc;
        
        rc = curandGenerateUniformDouble(gen, a, mn);
        if (rc != cudaSuccess)  {
            printf("curandGenerateUniformDouble returned %d\n", rc);
        }
        rc = curandGenerateUniformDouble(gen, x, m);
        if (rc != cudaSuccess)  {
            printf("curandGenerateUniformDouble returned %d\n", rc);
        }
        rc = curandGenerateUniformDouble(gen, y, n);
        if (rc != cudaSuccess)  {
            printf("curandGenerateUniformDouble returned %d\n", rc);
        }
    }
#else
    {
        double denom = 2.0/(double)RAND_MAX;

        for (long i=0; i<m; i++)
            x[i] =  1.0 - denom*(double)rand();

        for (long i=0; i<n; i++)
            y[i] =  1.0 - denom*(double)rand();

        for (long i=0; i<mn; i++)
            a[i] =  1.0 - denom*(double)rand();
    }
#endif

    int inc = 1;
    double alpha = 1.0;

    cublasHandle_t h;
    int rc = cublasCreate(&h);
    if (rc != cudaSuccess)  {
        printf("cublasCreate returned %d\n", rc);
    }

    /* warmup */
    rc = cublasDger(h ,m, n, &alpha, x, inc, y, inc, a, m);
    if (rc != cudaSuccess)  {
        printf("cublasDger returned %d\n", rc);
    }
    cudaDeviceSynchronize();
    double tt0 = omp_get_wtime();
    for (int r = 0; r<nr; r++) {
        cublasDger(h ,m, n, &alpha, x, inc, y, inc, a, m);
    }
    cudaDeviceSynchronize();
    double tt1 = omp_get_wtime();
   
    rc = cublasDestroy(h);
    if (rc != cudaSuccess)  {
        printf("cublasDestroy returned %d\n", rc);
    }

    double dt = (tt1-tt0)/nr;
    double result = (2.e-9*m*n/dt);
#ifdef DEBUG
    printf("CUBLAS DGER(m=%d,n=%d,alpha=%lf) took %lf seconds, GF/s = %lf \n",
           m, n, alpha, dt, result);
    fflush(stdout);
#endif

    safefree(a);
    safefree(y);
    safefree(x);

    return result;
}

double cudaxpy_gflops(int n)
{
#ifdef DEBUG
    printf("testing CUBLAS DAXPY with n = %d \n", n);
    fflush(stdout);
#endif

    double * x = safemalloc( n*sizeof(double) );
    double * y = safemalloc( n*sizeof(double) );
    if (x==NULL || y==NULL) {
    if (x!=NULL) safefree(x);
    if (y!=NULL) safefree(y);
    printf("daxpy_flops: skipping test because memory could not be allocated \n");
        return 0.0;
    }

#if USE_CURAND
    {
        int rc;
        
        rc = curandGenerateUniformDouble(gen, x, n);
        if (rc != cudaSuccess)  {
            printf("curandGenerateUniformDouble returned %d\n", rc);
        }
        rc = curandGenerateUniformDouble(gen, y, n);
        if (rc != cudaSuccess)  {
            printf("curandGenerateUniformDouble returned %d\n", rc);
        }
    }
#else
    {
        double denom = 2.0/(double)RAND_MAX;

        for (int i=0; i<n; i++)
            x[i] =  1.0 - denom*(double)rand();

        for (int i=0; i<n; i++)
            y[i] =  1.0 - denom*(double)rand();
    }
#endif

    int inc = 1;
    double alpha = 1.0;

    cublasHandle_t h;
    int rc = cublasCreate(&h);
    if (rc != cudaSuccess)  {
        printf("cublasCreate returned %d\n", rc);
    }

    /* warmup */
    rc = cublasDaxpy(h ,n, &alpha, x, inc, y, inc);
    if (rc != cudaSuccess)  {
        printf("cublasDaxpy returned %d\n", rc);
    }
    cudaDeviceSynchronize();
    double tt0 = omp_get_wtime();
    for (int r = 0; r<nr; r++) {
        cublasDaxpy(h, n, &alpha, x, inc, y, inc);
    }
    cudaDeviceSynchronize();
    double tt1 = omp_get_wtime();
   
    rc = cublasDestroy(h);
    if (rc != cudaSuccess)  {
        printf("cublasDestroy returned %d\n", rc);
    }

    double dt = (tt1-tt0)/nr;
    double result = (2.e-9*n/dt);
#ifdef DEBUG
    printf("CUBLAS DAXPY(n=%d,alpha=%lf) took %lf seconds, GF/s = %lf \n",
           n, alpha, dt, result);
    fflush(stdout);
#endif

    safefree(y);
    safefree(x);

    return result;
}
#endif
