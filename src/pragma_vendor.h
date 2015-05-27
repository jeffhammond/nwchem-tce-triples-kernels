#ifndef PRAGMA_VENDOR_H
#define PRAGMA_VENDOR_H

/* see http://stackoverflow.com/questions/2706286/pragmas-swp-ivdep-prefetch-support-in-various-compilers
 * if one desires support for additional compilers */

#if defined(_OPENMP)
#define OMP_SIMD _Pragma("omp simd")
#else
#define OMP_SIMD
#endif

/* C99 or C++11 */
#if (( __STDC_VERSION__ >= 199901L ) || (__cplusplus >= 201103L ))
# define PRAGMA(x) _Pragma(#x)
/* INTEL */
# if defined(__INTEL_COMPILER)
#  define PRAGMA_SIMD PRAGMA(simd)
#  define PRAGMA_IVDEP PRAGMA(ivdep)
#  define PRAGMA_UNROLL PRAGMA(unroll)
#  define PRAGMA_UNROLLN(n) PRAGMA(unroll(n))
/* Clang/LLVM */
# elif defined(__clang__)
#  define PRAGMA_SIMD OMP_SIMD
#  define PRAGMA_IVDEP PRAGMA(ivdep)
#  define PRAGMA_UNROLL
#  define PRAGMA_UNROLLN
/* Cray */
# elif defined(_CRAYC)
#  define PRAGMA_SIMD OMP_SIMD
#  define PRAGMA_IVDEP PRAGMA(ivdep)
#  define PRAGMA_UNROLL PRAGMA(unroll)
#  define PRAGMA_UNROLLN(n) PRAGMA(unroll(n))
/* PGI */
# elif defined(__PGI)
#  define PRAGMA_SIMD OMP_SIMD
#  define PRAGMA_IVDEP PRAGMA(ivdep)
/*#  define PRAGMA_IVDEP PRAGMA("loop ivdep")*/
#  define PRAGMA_UNROLL PRAGMA(unroll)
#  define PRAGMA_UNROLLN(n) PRAGMA(unroll(n))
/* GCC - might need to add version-dependence for ivdep */
# elif defined(__GNUC__)
#  define PRAGMA_SIMD PRAGMA(GCC simd)
#  define PRAGMA_IVDEP PRAGMA(GCC ivdep)
#  define PRAGMA_UNROLL
#  define PRAGMA_UNROLLN
/* IBM XL */
# elif defined(__IBMC__)
#  define PRAGMA_SIMD OMP_SIMD
/* This pragma does not work most places.
 * #  define PRAGMA_IVDEP PRAGMA(ibm independent_loop) */
#  define PRAGMA_IVDEP
#  define PRAGMA_UNROLL PRAGMA(unroll)
#  define PRAGMA_UNROLLN(n) PRAGMA(unroll(n))
/* Unsupported */
# else
#  define PRAGMA_SIMD
#  define PRAGMA_IVDEP
#  define PRAGMA_UNROLL
#  define PRAGMA_UNROLLN(n)
# endif
/* C90 or older */
#else
# warning Without a C99/C++11 compiler and PRAGMA, none of the pragmas will be active.
# define PRAGMA_SIMD
# define PRAGMA_IVDEP
# define PRAGMA_UNROLL
# define PRAGMA_UNROLLN(n)
# endif

#endif // PRAGMA_VENDOR_H
