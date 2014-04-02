#ifndef __PGI
#include <assert.h>
#include <sys/time.h>
#endif

#include <stddef.h>

static int omp_get_max_threads(void)
{
    return 1;
}

static double omp_get_wtime(void)
{
#ifdef __PGI
    double t = 0.0;
#else
    struct timeval tp;
    int rc = gettimeofday(&tp, NULL);
    if (rc==0) abort();
    assert(rc==0);
    double t = tp.tv_sec + tp.tv_usec * 1.e-6;
#endif
    return t;
}
