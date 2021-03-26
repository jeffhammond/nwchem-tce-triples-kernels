#include <time.h>    // clock_gettime, timespec_get
#include <assert.h>
#include <errno.h>

#if defined(_OPENMP) && 0

#include <omp.h>

// OpenMP has its own timer and is desirable since it will
// not overcount by measuring processor time.
double gettime(void)
{
    return omp_get_wtime();
}

// Apple does not have C11 support in the C standard library...
#elif defined(__APPLE__) && 0

#include <mach/mach.h>
#include <mach/mach_time.h>

double gettime(void)
{
    mach_timebase_info_data_t info;
    mach_timebase_info(&info);
    uint64_t at = mach_absolute_time();
    return ( 1.e-9 * at * info.numer / info.denom );
}

// gettimeofday is the worst timer, but should work everywhere.
// This addresses issues with clock_gettime and timespec_get
// library support in Travis.
#elif defined(USE_GETTIMEOFDAY)

#include <sys/time.h>

double gettime(void)
{
  struct timeval tv;
  gettimeofday( &tv, NULL);
  double t  = (double) tv.tv_sec + (double) tv.tv_usec * 1.0e-6;
  return t;
}

// GCC claims to be C11 without knowing if glibc is compliant.
// glibc added support for timespec_get in version 2.16.
// (https://gcc.gnu.org/wiki/C11Status)
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L) && \
      defined(__GLIBC__) && defined(__GLIBC_MINOR__) && \
      (((__GLIBC__ == 2) && (__GLIBC_MINOR__ >= 16)) || (__GLIBC__ > 2))

double gettime(void)
{
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    time_t s  = ts.tv_sec;
    long   ns = ts.tv_nsec;
    double t  = (double)s + 1.e-9 * (double)ns;
    return t;
}

// clock_gettime is not supported everywhere, or requires explicit librt.
#elif defined(CLOCK_PROCESS_CPUTIME_ID)

double gettime(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
    time_t s  = ts.tv_sec;
    long   ns = ts.tv_nsec;
    double t  = (double)s + 1.e-9 * (double)ns;
    return t;
}

#else

#include <sys/time.h>

double gettime(void)
{
  struct timeval tv;
  gettimeofday( &tv, NULL);
  double t  = (double) tv.tv_sec + (double) tv.tv_usec * 1.0e-6;
  return t;
}

#endif // timers
