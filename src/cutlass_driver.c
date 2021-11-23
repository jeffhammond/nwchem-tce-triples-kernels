#ifdef DO_CUTENSOR_KERNELS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef _OPENMP
#include <omp.h>
#else
#warning Fake OpenMP
#include "fake_omp.h"
#endif

//#include "safemalloc.h"
//void zero_array(long long n, double * a);
void acc_zero_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, double * restrict t3);

#include <cuda_runtime.h>
#include <cutensor.h>

void cutensor_driver(int reps, int kernel, int tilesize,
                    long long tile6, long long tile7,
                    const double * pT1, const double * pT2, const double * pV2, double * pT3)
{
    double tt0 = 0.0, tt1 = 0.0, ttt0 = 0.0, ttt1 = 0.0, dt = 0.0;

    cudaStream_t stream;
    cudaError_t s2 = cudaStreamCreate(&stream);
    if (s2) fprintf(stderr, "cudaStreamCreate\n");

    cutensorHandle_t h;

    cutensorStatus_t s = cutensorInit(&h);
    if (s) fprintf(stderr,"cutensorInit\n");

    cutensorContractionFind_t f;
    s = cutensorInitContractionFind(&h, &f, CUTENSOR_ALGO_DEFAULT);
    if (s) fprintf(stderr,"cutensorInitContractionFind\n");

    int64_t eT1[2]={tilesize,tilesize};
    int64_t eT2[4]={tilesize,tilesize,tilesize,tilesize};
    int64_t eV2[4]={tilesize,tilesize,tilesize,tilesize};
    int64_t eT3[6]={tilesize,tilesize,tilesize,tilesize,tilesize,tilesize};
    cutensorTensorDescriptor_t dT1,dT2,dV2,dT3;
    s = cutensorInitTensorDescriptor(&h, &dT1, 2, eT1, NULL, CUDA_R_64F, CUTENSOR_OP_IDENTITY);
    if (s) fprintf(stderr,"cutensorInitTensorDescriptor\n");
    s = cutensorInitTensorDescriptor(&h, &dT2, 4, eT2, NULL, CUDA_R_64F, CUTENSOR_OP_IDENTITY);
    if (s) fprintf(stderr,"cutensorInitTensorDescriptor\n");
    s = cutensorInitTensorDescriptor(&h, &dV2, 4, eV2, NULL, CUDA_R_64F, CUTENSOR_OP_IDENTITY);
    if (s) fprintf(stderr,"cutensorInitTensorDescriptor\n");
    s = cutensorInitTensorDescriptor(&h, &dT3, 6, eT3, NULL, CUDA_R_64F, CUTENSOR_OP_IDENTITY);
    if (s) fprintf(stderr,"cutensorInitTensorDescriptor\n");

    uint32_t aT1,aT2,aV2,aT3;
    s = cutensorGetAlignmentRequirement(&h, pT1, &dT1, &aT1);
    if (s) fprintf(stderr,"cutensorGetAlignmentRequirement\n");
    s = cutensorGetAlignmentRequirement(&h, pT2, &dT2, &aT2);
    if (s) fprintf(stderr,"cutensorGetAlignmentRequirement\n");
    s = cutensorGetAlignmentRequirement(&h, pV2, &dV2, &aV2);
    if (s) fprintf(stderr,"cutensorGetAlignmentRequirement\n");
    s = cutensorGetAlignmentRequirement(&h, pT3, &dT3, &aT3);
    if (s) fprintf(stderr,"cutensorGetAlignmentRequirement\n");

    cutensorContractionDescriptor_t dX[3][9];
    cutensorContractionPlan_t pX[3][9];
    double alpha[3][9];
    bool active[3][9] = {false};
    size_t max_worksize=0;
    {
        char h1 = 'a';
        char h2 = 'b';
        char h3 = 'c';
        char h7 = 'd';
        char p4 = 'e';
        char p5 = 'f';
        char p6 = 'g';
        char p7 = 'h';

        // s1_1 = [0][0]
        {
            int k = 0;
            int32_t mT3[6]={h3,h2,h1,p6,p5,p4};
            int32_t mT1[2]={p4,h1};
            int32_t mV2[4]={h3,h2,p6,p5};
            alpha[0][k] = 1;
            active[0][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[0][k], &dT1, mT1, aT1, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }
        // s1_2 = [0][0]
        {
            int k = 1;
            int32_t mT3[6]={h3,h1,h2,p6,p5,p4};
            int32_t mT1[2]={p4,h1};
            int32_t mV2[4]={h3,h2,p6,p5};
            alpha[0][k] = -1;
            active[0][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[0][k], &dT1, mT1, aT1, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }
        // s1_3 = [0][2]
        {
            int k = 2;
            int32_t mT3[6]={h1,h3,h2,p6,p5,p4};
            int32_t mT1[2]={p4,h1};
            int32_t mV2[4]={h3,h2,p6,p5};
            alpha[0][k] = 1;
            active[0][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[0][k], &dT1, mT1, aT1, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }
        // s1_4 = [0][3]
        {
            int k = 3;
            int32_t mT3[6]={h3,h2,h1,p6,p4,p5};
            int32_t mT1[2]={p4,h1};
            int32_t mV2[4]={h3,h2,p6,p5};
            alpha[0][k] = -1;
            active[0][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[0][k], &dT1, mT1, aT1, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }
        // s1_5 = [0][4]
        {
            int k = 4;
            int32_t mT3[6]={h3,h1,h2,p6,p4,p5};
            int32_t mT1[2]={p4,h1};
            int32_t mV2[4]={h3,h2,p6,p5};
            alpha[0][k] = 1;
            active[0][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[0][k], &dT1, mT1, aT1, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }
        // s1_6 = [0][5]
        {
            int k = 5;
            int32_t mT3[6]={h1,h3,h2,p6,p4,p5};
            int32_t mT1[2]={p4,h1};
            int32_t mV2[4]={h3,h2,p6,p5};
            alpha[0][k] = -1;
            active[0][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[0][k], &dT1, mT1, aT1, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }
        // s1_7 = [0][6]
        {
            int k = 6;
            int32_t mT3[6]={h3,h2,h1,p4,p6,p5};
            int32_t mT1[2]={p4,h1};
            int32_t mV2[4]={h3,h2,p6,p5};
            alpha[0][k] = 1;
            active[0][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[0][k], &dT1, mT1, aT1, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }
        // s1_8 = [0][7]
        {
            int k = 7;
            int32_t mT3[6]={h3,h1,h2,p4,p6,p5};
            int32_t mT1[2]={p4,h1};
            int32_t mV2[4]={h3,h2,p6,p5};
            alpha[0][k] = -1;
            active[0][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[0][k], &dT1, mT1, aT1, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }
        // s1_9 = [0][8]
        {
            int k = 8;
            int32_t mT3[6]={h1,h3,h2,p4,p6,p5};
            int32_t mT1[2]={p4,h1};
            int32_t mV2[4]={h3,h2,p6,p5};
            alpha[0][k] = 1;
            active[0][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[0][k], &dT1, mT1, aT1, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }

        // d1_1 = [1][0]
        {
            int k = 0;
            int32_t mT3[6]={h3,h2,h1,p6,p5,p4};
            int32_t mT2[4]={h7,p4,p5,h1};
            int32_t mV2[4]={h3,h2,p6,h7};
            alpha[1][k] = -1;
            active[1][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[1][k], &dT2, mT2, aT2, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }
        // d1_2 = [1][1]
        {
            int k = 1;
            int32_t mT3[6]={h3,h1,h2,p6,p5,p4};
            int32_t mT2[4]={h7,p4,p5,h1};
            int32_t mV2[4]={h3,h2,p6,h7};
            alpha[1][k] = 1;
            active[1][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[1][k], &dT2, mT2, aT2, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }
        // d1_3 = [1][2]
        {
            int k = 2;
            int32_t mT3[6]={h1,h3,h2,p6,p5,p4};
            int32_t mT2[4]={h7,p4,p5,h1};
            int32_t mV2[4]={h3,h2,p6,h7};
            alpha[1][k] = -1;
            active[1][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[1][k], &dT2, mT2, aT2, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }
        // d1_4 = [1][3]
        {
            int k = 3;
            int32_t mT3[6]={h3,h2,h1,p5,p4,p6};
            int32_t mT2[4]={h7,p4,p5,h1};
            int32_t mV2[4]={h3,h2,p6,h7};
            alpha[1][k] = -1;
            active[1][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[1][k], &dT2, mT2, aT2, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }
        // d1_5 = [1][4]
        {
            int k = 4;
            int32_t mT3[6]={h3,h1,h2,p5,p4,p6};
            int32_t mT2[4]={h7,p4,p5,h1};
            int32_t mV2[4]={h3,h2,p6,h7};
            alpha[1][k] = 1;
            active[1][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[1][k], &dT2, mT2, aT2, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }
        // d1_6 = [1][5]
        {
            int k = 5;
            int32_t mT3[6]={h1,h3,h2,p5,p4,p6};
            int32_t mT2[4]={h7,p4,p5,h1};
            int32_t mV2[4]={h3,h2,p6,h7};
            alpha[1][k] = -1;
            active[1][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[1][k], &dT2, mT2, aT2, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }
        // d1_7 = [1][6]
        {
            int k = 6;
            int32_t mT3[6]={h3,h2,h1,p5,p6,p4};
            int32_t mT2[4]={h7,p4,p5,h1};
            int32_t mV2[4]={h3,h2,p6,h7};
            alpha[1][k] = 1;
            active[1][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[1][k], &dT2, mT2, aT2, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }
        // d1_8 = [1][7]
        {
            int k = 7;
            int32_t mT3[6]={h3,h1,h2,p5,p6,p4};
            int32_t mT2[4]={h7,p4,p5,h1};
            int32_t mV2[4]={h3,h2,p6,h7};
            alpha[1][k] = -1;
            active[1][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[1][k], &dT2, mT2, aT2, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }
        // d1_9 = [1][8]
        {
            int k = 8;
            int32_t mT3[6]={h1,h3,h2,p5,p6,p4};
            int32_t mT2[4]={h7,p4,p5,h1};
            int32_t mV2[4]={h3,h2,p6,h7};
            alpha[1][k] = 1;
            active[1][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[1][k], &dT2, mT2, aT2, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }

        // d2_1 = [2][0]
        {
            int k = 0;
            int32_t mT3[6]={h3,h2,h1,p6,p5,p4};
            int32_t mT2[4]={p7,p4,h1,h2};
            int32_t mV2[4]={p7,h3,p6,p5};
            alpha[2][k] = -1;
            active[2][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[2][k], &dT2, mT2, aT2, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }
        // d2_2 = [2][1]
        {
            int k = 1;
            int32_t mT3[6]={h2,h1,h3,p6,p5,p4};
            int32_t mT2[4]={p7,p4,h1,h2};
            int32_t mV2[4]={p7,h3,p6,p5};
            alpha[2][k] = -1;
            active[2][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[2][k], &dT2, mT2, aT2, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }
        // d2_3 = [2][2]
        {
            int k = 2;
            int32_t mT3[6]={h2,h3,h1,p6,p5,p4};
            int32_t mT2[4]={p7,p4,h1,h2};
            int32_t mV2[4]={p7,h3,p6,p5};
            alpha[2][k] = 1;
            active[2][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[2][k], &dT2, mT2, aT2, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }
        // d2_4 = [2][3]
        {
            int k = 3;
            int32_t mT3[6]={h3,h2,h1,p6,p4,p5};
            int32_t mT2[4]={p7,p4,h1,h2};
            int32_t mV2[4]={p7,h3,p6,p5};
            alpha[2][k] = 1;
            active[2][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[2][k], &dT2, mT2, aT2, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }
        // d2_5 = [2][4]
        {
            int k = 4;
            int32_t mT3[6]={h2,h1,h3,p6,p4,p5};
            int32_t mT2[4]={p7,p4,h1,h2};
            int32_t mV2[4]={p7,h3,p6,p5};
            alpha[2][k] = 1;
            active[2][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[2][k], &dT2, mT2, aT2, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }
        // d2_6 = [2][5]
        {
            int k = 5;
            int32_t mT3[6]={h2,h3,h1,p6,p4,p5};
            int32_t mT2[4]={p7,p4,h1,h2};
            int32_t mV2[4]={p7,h3,p6,p5};
            alpha[2][k] = -1;
            active[2][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[2][k], &dT2, mT2, aT2, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }
        // d2_7 = [2][6]
        {
            int k = 6;
            int32_t mT3[6]={h3,h2,h1,p4,p6,p5};
            int32_t mT2[4]={p7,p4,h1,h2};
            int32_t mV2[4]={p7,h3,p6,p5};
            alpha[2][k] = -1;
            active[2][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[2][k], &dT2, mT2, aT2, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }
        // d2_8 = [2][7]
        {
            int k = 7;
            int32_t mT3[6]={h2,h1,h3,p4,p6,p5};
            int32_t mT2[4]={p7,p4,h1,h2};
            int32_t mV2[4]={p7,h3,p6,p5};
            alpha[2][k] = -1;
            active[2][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[2][k], &dT2, mT2, aT2, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }
        // d2_9 = [2][8]
        {
            int k = 8;
            int32_t mT3[6]={h2,h3,h1,p4,p6,p5};
            int32_t mT2[4]={p7,p4,h1,h2};
            int32_t mV2[4]={p7,h3,p6,p5};
            alpha[2][k] = 1;
            active[2][k] = true;
            s = cutensorInitContractionDescriptor(&h, &dX[2][k], &dT2, mT2, aT2, &dV2, mV2, aV2, &dT3, mT3, aT3, &dT3, mT3, aT3, CUTENSOR_R_MIN_64F);
            if (s) fprintf(stderr,"cutensorInitContractionDescriptor\n");
        }

        for (int i=0; i<3; i++) {
          for (int k=0; k<9; k++) {
            if (!active[i][k]) break;

            size_t worksize;

            s = cutensorContractionGetWorkspace(&h, &dX[i][k], &f, CUTENSOR_WORKSPACE_MAX, &worksize);
            //s = cutensorContractionGetWorkspace(&h, &dX[i][k], &f, CUTENSOR_WORKSPACE_RECOMMENDED, &worksize);
            if (s) fprintf(stderr,"cutensorContractionGetWorkspace\n");

            s = cutensorInitContractionPlan(&h, &pX[i][k], &dX[i][k], &f, worksize);
            if (s) fprintf(stderr,"cutensorInitContractionPlan\n");

            if (worksize > max_worksize) max_worksize = worksize;
          }
        }
    }

    void * pW = NULL;
    s2 = cudaMalloc(&pW, max_worksize);
    if (s2) fprintf(stderr, "cudaMalloc\n");

    double beta = 1;

    if (pT3==NULL) {
      printf("skipping CUTENSOR kernels because memory was not allocated. \n");
    } else {
      printf("\nSTARTING CUTENSOR KERNELS \n");
      fflush(stdout);
      for (int i=0; i<reps; i++)
      {
        long long totalflops = 0;
        //zero_array(tile6, pT3);
        acc_zero_(&tilesize, &tilesize, &tilesize, &tilesize, &tilesize, &tilesize, pT3);
        ttt0 = omp_get_wtime();
#ifdef DO_S1
        if (kernel<0 || kernel==1) {
            int k = 0;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[0][k], (void*) &alpha[0][k], pT1, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_1", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==2) {
            int k = 1;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[0][k], (void*) &alpha[0][k], pT1, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_2", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==3) {
            int k = 2;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[0][k], (void*) &alpha[0][k], pT1, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_3", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==4) {
            int k = 3;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[0][k], (void*) &alpha[0][k], pT1, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_4", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==5) {
            int k = 4;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[0][k], (void*) &alpha[0][k], pT1, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_5", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==6) {
            int k = 5;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[0][k], (void*) &alpha[0][k], pT1, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_6", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==7) {
            int k = 6;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[0][k], (void*) &alpha[0][k], pT1, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_7", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==8) {
            int k = 7;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[0][k], (void*) &alpha[0][k], pT1, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_8", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
        if (kernel<0 || kernel==9) {
            int k = 8;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[0][k], (void*) &alpha[0][k], pT1, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_9", dt, (2e-9*tile6)/dt );
            totalflops += 2*tile6;
        }
#endif
#ifdef DO_D1
        if (kernel<0 || kernel==1) {
            int k = 0;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[1][k], (void*) &alpha[1][k], pT2, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_1", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==2) {
            int k = 1;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[1][k], (void*) &alpha[1][k], pT2, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_2", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==3) {
            int k = 2;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[1][k], (void*) &alpha[1][k], pT2, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_3", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==4) {
            int k = 3;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[1][k], (void*) &alpha[1][k], pT2, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_4", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==5) {
            int k = 4;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[1][k], (void*) &alpha[1][k], pT2, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_5", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==6) {
            int k = 5;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[1][k], (void*) &alpha[1][k], pT2, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_6", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==7) {
            int k = 6;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[1][k], (void*) &alpha[1][k], pT2, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_7", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==8) {
            int k = 7;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[1][k], (void*) &alpha[1][k], pT2, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_8", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==9) {
            int k = 8;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[1][k], (void*) &alpha[1][k], pT2, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_9", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
#endif
#ifdef DO_D2
        if (kernel<0 || kernel==1) {
            int k = 0;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[2][k], (void*) &alpha[2][k], pT2, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_1", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==2) {
            int k = 1;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[2][k], (void*) &alpha[2][k], pT2, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_2", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==3) {
            int k = 2;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[2][k], (void*) &alpha[2][k], pT2, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_3", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==4) {
            int k = 3;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[2][k], (void*) &alpha[2][k], pT2, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_4", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==5) {
            int k = 4;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[2][k], (void*) &alpha[2][k], pT2, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_5", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==6) {
            int k = 5;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[2][k], (void*) &alpha[2][k], pT2, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_6", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==7) {
            int k = 6;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[2][k], (void*) &alpha[2][k], pT2, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_7", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==8) {
            int k = 7;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[2][k], (void*) &alpha[2][k], pT2, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
            tt1 = omp_get_wtime();
            dt = tt1-tt0;
            printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_8", dt, (2e-9*tile7)/dt );
            totalflops += 2*tile7;
        }
        if (kernel<0 || kernel==9) {
            int k = 8;
            tt0 = omp_get_wtime();
            s = cutensorContraction(&h, &pX[2][k], (void*) &alpha[2][k], pT2, pV2, (void*) &beta, pT3, pT3, pW, max_worksize, stream);
            if (s) fprintf(stderr, "cutensorContraction\n");
            s2 = cudaStreamSynchronize(stream);
            if (s2) fprintf(stderr, "cudaStreamSynchronize\n");
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

    s2 = cudaFree(pW);
    if (s2) fprintf(stderr, "cudaFree\n");

    s2 = cudaStreamDestroy(stream);
    if (s2) fprintf(stderr, "cudaStreamDestroy\n");
}

#endif
