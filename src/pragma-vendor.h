#if __STDC_VERSION__ >= 199901L
# if defined(__INTEL_COMPILER)
#  define PRAGMA_IVDEP _Pragma("ivdep")
# elif defined(__clang__)
#  define PRAGMA_IVDEP _Pragma("ivdep")
# elif defined(_CRAYC)
#  define PRAGMA_IVDEP _Pragma("ivdep")
# elif defined(__PGI)
#  define PRAGMA_IVDEP _Pragma("ivdep")
/*#  define PRAGMA_IVDEP _Pragma("loop ivdep")*/
# elif defined(__GNUC__)
#  define PRAGMA_IVDEP _Pragma("GCC ivdep")
# elif defined(__IBMC__)
#  define PRAGMA_IVDEP _Pragma("ibm independent_loop")
# else
#  define PRAGMA_IVDEP
# endif
#elif defined(__cplusplus)
# warning Stop using a C++ compiler for C code.
# define PRAGMA_IVDEP
#else
# warning Without a C99 compiler and _Pragma, none of the pragmas will be active.
# define PRAGMA_IVDEP
# endif
