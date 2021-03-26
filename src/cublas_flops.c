#define DEBUG 1

#include <string.h>
#include <math.h>

#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>
#include <curand.h>
#include <cublas_v2.h>

// gettime.c
double gettime(void);

// safemalloc uses cudaMallocManaged
#define USE_CUDA_UM 1
#include "safemalloc.h"

/* number of test repititions */
static const int nr = 1;

curandGenerator_t gen;
cublasHandle_t h;

void init(void)
{
    int rc;
   
    rc = curandCreateGenerator(&gen, CURAND_RNG_PSEUDO_DEFAULT);
    if (rc != cudaSuccess)  {
        printf("curandCreateGenerator returned %d\n", rc);
    }

    rc = curandSetPseudoRandomGeneratorSeed(gen, 1234ULL);
    if (rc != cudaSuccess)  {
        printf("curandSetPseudoRandomGeneratorSeed returned %d\n", rc);
    }

    rc = cublasCreate(&h);
    if (rc != cudaSuccess)  {
        printf("cublasCreate returned %d\n", rc);
    }
    cudaDeviceSynchronize();
}

void final(void)
{
    int rc;
    cudaDeviceSynchronize();

    rc = curandDestroyGenerator(gen);
    if (rc != cudaSuccess)  {
        printf("curandDestroyGenerator returned %d\n", rc);
    }
   
    rc = cublasDestroy(h);
    if (rc != cudaSuccess)  {
        printf("cublasDestroy returned %d\n", rc);
    }
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

    cublasOperation_t notrans = CUBLAS_OP_N;
    double alpha = 1.0;
    double beta  = 1.0;

    /* warmup */
    cudaDeviceSynchronize();
    cublasDgemm(h, notrans, notrans, rowa, colb, cola,
		&alpha, a, rowa, b, rowb,
		&beta, c, rowc);
    cudaDeviceSynchronize();
    double tt0 = gettime();
    for (int r = 0; r<nr; r++) {
        cublasDgemm(h, notrans, notrans, rowa, colb, cola,
		    &alpha, a, rowa, b, rowb,
		    &beta, c, rowc);
        cudaDeviceSynchronize();
    }
    double tt1 = gettime();

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

    int inc = 1;
    double alpha = 1.0;

    /* warmup */
    cublasDger(h ,m, n, &alpha, x, inc, y, inc, a, m);
    cudaDeviceSynchronize();
    double tt0 = gettime();
    for (int r = 0; r<nr; r++)
        cublasDger(h ,m, n, &alpha, x, inc, y, inc, a, m);
    cudaDeviceSynchronize();
    double tt1 = gettime();

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

    int rc;
    
    rc = curandGenerateUniformDouble(gen, x, n);
    if (rc != cudaSuccess)  {
        printf("curandGenerateUniformDouble returned %d\n", rc);
    }
    rc = curandGenerateUniformDouble(gen, y, n);
    if (rc != cudaSuccess)  {
        printf("curandGenerateUniformDouble returned %d\n", rc);
    }

    int inc = 1;
    double alpha = 1.0;

    /* warmup */
    cublasDaxpy(h ,n, &alpha, x, inc, y, inc);
    cudaDeviceSynchronize();
    double tt0 = gettime();
    for (int r = 0; r<nr; r++)
        cublasDaxpy(h, n, &alpha, x, inc, y, inc);
    cudaDeviceSynchronize();
    double tt1 = gettime();

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
