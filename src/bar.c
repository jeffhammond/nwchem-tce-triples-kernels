#include <stdio.h>
#include <omp.h>

int main(void)
{
    const int n=10000;
    for (int j=0; j<20; j++) {
        #pragma omp parallel
        {
            double t0 = omp_get_wtime();
            for (int i=0; i<n; i++) {
              #pragma omp barrier
            }
            double t1 = omp_get_wtime();
            if (omp_get_thread_num()==1)
                printf("round %d: %d barriers took %lf us per call\n", j, n, 1e6*(t1-t0)/n);
        }
    }
    return 0;
}
