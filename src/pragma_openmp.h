#ifndef PRAGMA_OPENMP_H
#define PRAGMA_OPENMP_H

#if defined(_OPENMP) && (( __STDC_VERSION__ >= 199901L ) || (__cplusplus >= 201103L ))

#define PRAGMA(x) _Pragma(#x)

#define OMP_PARALLEL PRAGMA(omp parallel)
#define OMP_PARALLEL_FOR PRAGMA(omp parallel for schedule(static))
#define OMP_FOR PRAGMA(omp for schedule(static))

#define OMP_PARALLEL_FOR_COLLAPSE(n) PRAGMA(omp parallel for collapse(n) schedule(static))
#define OMP_PARALLEL_FOR_COLLAPSE2 OMP_PARALLEL_FOR_COLLAPSE(2)
#define OMP_PARALLEL_FOR_COLLAPSE3 OMP_PARALLEL_FOR_COLLAPSE(3)
#define OMP_PARALLEL_FOR_COLLAPSE4 OMP_PARALLEL_FOR_COLLAPSE(4)

#define OMP_PARALLEL_FOR_REDUCE_ADD(r) PRAGMA(omp parallel for reduction (+ : r) schedule(static))

#else

#warning No OpenMP, either because compiler does not understand OpenMP or C99/C++11 _Pragma.

#define OMP_PARALLEL
#define OMP_PARALLEL_FOR
#define OMP_FOR
#define OMP_PARALLEL_FOR_COLLAPSE(n)
#define OMP_PARALLEL_FOR_COLLAPSE2
#define OMP_PARALLEL_FOR_COLLAPSE3
#define OMP_PARALLEL_FOR_COLLAPSE4
#define OMP_PARALLEL_FOR_REDUCE_ADD(r)

#endif

#endif // PRAGMA_OPENMP_H
