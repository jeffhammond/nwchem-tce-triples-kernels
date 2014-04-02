#if defined(_OPENMP) && ( __STDC_VERSION__ >= 199901L )

#define OMP_PARALLEL _Pragma("omp parallel")
#define OMP_PARALLEL_FOR _Pragma("omp parallel for schedule(static)")
#define OMP_FOR _Pragma("omp for schedule(static)")
/* I cannot figure out how to use variables inside of these things... */
#define OMP_PARALLEL_FOR_COLLAPSE2 _Pragma("omp parallel for collapse(2) schedule(static)")
#define OMP_PARALLEL_FOR_COLLAPSE3 _Pragma("omp parallel for collapse(3) schedule(static)")
#define OMP_PARALLEL_FOR_COLLAPSE4 _Pragma("omp parallel for collapse(4) schedule(static)")
#define OMP_PARALLEL_FOR_REDUCE_ADD _Pragma("omp parallel for reduction (+ : r) schedule(static)")

#else

#error No OpenMP, either because compiler does not understand OpenMP or C99 _Pragma.

#define OMP_PARALLEL
#define OMP_PARALLEL_FOR
#define OMP_FOR
#define OMP_PARALLEL_FOR_COLLAPSE2
#define OMP_PARALLEL_FOR_COLLAPSE3
#define OMP_PARALLEL_FOR_COLLAPSE4
#define OMP_PARALLEL_FOR_REDUCE_ADD

#endif
