#include <assert.h>
#include <sys/time.h>

static int omp_get_max_threads(void)
{
    return 1;
}

static double omp_get_wtime(void)
{
    struct timeval tp;
    int rc = gettimeofday(&tp, NULL);
    assert(rc==0);
    double t = tp.tv_sec + tp.tv_usec * 1.e-6;
    return t;
}
