/* declared with Fortran semantics, hence no use of const but all pointers are restrict */

#include <stdint.h>

/* TODO The Fortran interfaces need to use fint not int. */

#if FORTRAN_INTEGER_SIZE==4
typedef int32_t fint;
#else
typedef int64_t fint;
#endif

void omp_sd_t_s1_1_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);
void omp_sd_t_s1_2_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);
void omp_sd_t_s1_3_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);
void omp_sd_t_s1_4_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);
void omp_sd_t_s1_5_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);
void omp_sd_t_s1_6_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);
void omp_sd_t_s1_7_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);
void omp_sd_t_s1_8_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);
void omp_sd_t_s1_9_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);

void omp_sd_t_d1_1_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);
void omp_sd_t_d1_2_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);
void omp_sd_t_d1_3_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);
void omp_sd_t_d1_4_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);
void omp_sd_t_d1_5_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);
void omp_sd_t_d1_6_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);
void omp_sd_t_d1_7_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);
void omp_sd_t_d1_8_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);
void omp_sd_t_d1_9_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);

void omp_sd_t_d2_1_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);
void omp_sd_t_d2_2_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);
void omp_sd_t_d2_3_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);
void omp_sd_t_d2_4_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);
void omp_sd_t_d2_5_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);
void omp_sd_t_d2_6_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);
void omp_sd_t_d2_7_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);
void omp_sd_t_d2_8_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);
void omp_sd_t_d2_9_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);

void ref_sd_t_s1_1_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);
void ref_sd_t_s1_2_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);
void ref_sd_t_s1_3_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);
void ref_sd_t_s1_4_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);
void ref_sd_t_s1_5_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);
void ref_sd_t_s1_6_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);
void ref_sd_t_s1_7_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);
void ref_sd_t_s1_8_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);
void ref_sd_t_s1_9_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);

void ref_sd_t_d1_1_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);
void ref_sd_t_d1_2_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);
void ref_sd_t_d1_3_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);
void ref_sd_t_d1_4_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);
void ref_sd_t_d1_5_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);
void ref_sd_t_d1_6_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);
void ref_sd_t_d1_7_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);
void ref_sd_t_d1_8_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);
void ref_sd_t_d1_9_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);

void ref_sd_t_d2_1_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);
void ref_sd_t_d2_2_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);
void ref_sd_t_d2_3_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);
void ref_sd_t_d2_4_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);
void ref_sd_t_d2_5_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);
void ref_sd_t_d2_6_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);
void ref_sd_t_d2_7_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);
void ref_sd_t_d2_8_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);
void ref_sd_t_d2_9_(int * restrict h3, int * restrict h2, int * restrict h1, int * restrict p6, int * restrict p5, int * restrict p4, int * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);

void f2c_sd_t_s1_1_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);
void f2c_sd_t_s1_2_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);
void f2c_sd_t_s1_3_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);
void f2c_sd_t_s1_4_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);
void f2c_sd_t_s1_5_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);
void f2c_sd_t_s1_6_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);
void f2c_sd_t_s1_7_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);
void f2c_sd_t_s1_8_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);
void f2c_sd_t_s1_9_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, double * restrict t3, double * restrict t1, double * restrict v2);

void f2c_sd_t_d1_1_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, fint * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);
void f2c_sd_t_d1_2_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, fint * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);
void f2c_sd_t_d1_3_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, fint * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);
void f2c_sd_t_d1_4_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, fint * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);
void f2c_sd_t_d1_5_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, fint * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);
void f2c_sd_t_d1_6_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, fint * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);
void f2c_sd_t_d1_7_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, fint * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);
void f2c_sd_t_d1_8_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, fint * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);
void f2c_sd_t_d1_9_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, fint * restrict h7, double * restrict t3, double * restrict t2, double * restrict v2);

void f2c_sd_t_d2_1_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, fint * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);
void f2c_sd_t_d2_2_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, fint * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);
void f2c_sd_t_d2_3_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, fint * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);
void f2c_sd_t_d2_4_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, fint * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);
void f2c_sd_t_d2_5_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, fint * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);
void f2c_sd_t_d2_6_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, fint * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);
void f2c_sd_t_d2_7_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, fint * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);
void f2c_sd_t_d2_8_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, fint * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);
void f2c_sd_t_d2_9_(fint * restrict h3, fint * restrict h2, fint * restrict h1, fint * restrict p6, fint * restrict p5, fint * restrict p4, fint * restrict p7, double * restrict t3, double * restrict t2, double * restrict v2);

