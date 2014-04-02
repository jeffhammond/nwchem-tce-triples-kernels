#if __STDC_VERSION__ >= 199901L
# define PRAGMA(x) _Pragma(#x)
# if defined(__INTEL_COMPILER)
#  define PRAGMA_IVDEP PRAGMA(ivdep)
#  define PRAGMA_UNROLL PRAGMA(unroll)
#  define PRAGMA_UNROLLN(n) PRAGMA(unroll(n))
# elif defined(__clang__)
#  define PRAGMA_IVDEP PRAGMA(ivdep)
# elif defined(_CRAYC)
#  define PRAGMA_IVDEP PRAGMA(ivdep)
#  define PRAGMA_UNROLL PRAGMA(unroll)
#  define PRAGMA_UNROLLN(n) PRAGMA(unroll(n))
# elif defined(__PGI)
#  define PRAGMA_IVDEP PRAGMA(ivdep)
/*#  define PRAGMA_IVDEP PRAGMA("loop ivdep")*/
#  define PRAGMA_UNROLL PRAGMA(unroll)
#  define PRAGMA_UNROLLN(n) PRAGMA(unroll(n))
# elif defined(__GNUC__)
#  define PRAGMA_IVDEP PRAGMA(GCC ivdep)
#  define PRAGMA_UNROLL
#  define PRAGMA_UNROLLN
# elif defined(__IBMC__)
#  define PRAGMA_IVDEP PRAGMA(ibm independent_loop)
#  define PRAGMA_UNROLL PRAGMA(unroll)
#  define PRAGMA_UNROLLN(n) PRAGMA(unroll(n))
# else
#  define PRAGMA_IVDEP
#  define PRAGMA_UNROLL
#  define PRAGMA_UNROLLN(n)
# endif
#elif defined(__cplusplus)
# warning Stop using a C++ compiler for C code.
# define PRAGMA_IVDEP
# define PRAGMA_UNROLL
# define PRAGMA_UNROLLN(n)
#else
# warning Without a C99 compiler and PRAGMA, none of the pragmas will be active.
# define PRAGMA_IVDEP
# define PRAGMA_UNROLL
# define PRAGMA_UNROLLN(n)
# endif
