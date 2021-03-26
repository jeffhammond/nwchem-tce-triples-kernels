#include <omp.h>

double gettime(void)
{
  return omp_get_wtime();
}
