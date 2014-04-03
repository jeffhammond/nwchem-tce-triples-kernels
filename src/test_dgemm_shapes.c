#ifdef _OPENMP
#include <omp.h>
#else
#include "fake_omp.h"
#endif

#include "safemalloc.h"

double dgemm_gflops(int m, int n, int k);

int main(int argc, char * argv[])
{
    int maxm = (argc>1) ? atoi(argv[1]) : 1000;
    int incm = (argc>2) ? atoi(argv[2]) : 100;
    int maxk = (argc>3) ? atoi(argv[3]) : 1000;
    int inck = (argc>4) ? atoi(argv[4]) : 100;

    printf("testing DGEMM %d threads \n", omp_get_max_threads());
    printf("maxm=%d, incm=%d, maxk=%d, inck=%d\n", maxm, incm, maxk, inck);

    for (int m=incm; m<=maxm; m+=incm) {
        int n = m;
        for (int k=inck; k<=maxk; k+=inck) {
            double eff_peak = dgemm_gflops(m,n,k);
            printf("m=n=%5d, k=%5d = %lf GF/s \n", m, k, eff_peak);
        }
    }

    return 0;
}
