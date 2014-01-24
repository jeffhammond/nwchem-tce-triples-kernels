/* These have been separated out from ccsd_t_singles_l.F and ccsd_t_doubles_l.F
 * and converted from Fortran 77 to C99 by hand. */

#include <stdint.h>

#if FORTRAN_INTEGER_SIZE==4
typedef int32_t fint;
#elif FORTRAN_INTEGER_SIZE==8
typedef int64_t fint;
#else
#error You must define FORTRAN_INTEGER_SIZE to 4 or 8.
#endif

/* The possible downcast from fint to int is safe because array dimensions
 * are on the order of 30, i.e. nowhere near INT_MAX. */

void f2c_sd_t_s1_1_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d, 
                    double * restrict t3, double * restrict t1, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    for (int p4=0; p4<p4u; p4++)
    for (int p5=0; p5<p5u; p5++)
    for (int p6=0; p6<p6u; p6++)
    for (int h1=0; h1<h1u; h1++)
    for (int h2=0; h2<h2u; h2++)
    for (int h3=0; h3<h3u; h3++)
    //t3(h3,h2,h1,p6,p5,p4)+=t1(p4,h1)*v2(h3,h2,p6,p5); 
    t3[h3+h3u*(h2+h2u*(h1+h1u*(p6+p6u*(p5+p5u*p4))))] += t1[p4+p4u*h1] * v2[h3+h3u*(h2+h2u*(p6+p6u*p5))];
    return;
}

void f2c_sd_t_s1_2_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d, 
                    double * restrict t3, double * restrict t1, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    for (int p4=0; p4<p4u; p4++)
    for (int p5=0; p5<p5u; p5++)
    for (int p6=0; p6<p6u; p6++)
    for (int h2=0; h2<h2u; h2++)
    for (int h1=0; h1<h1u; h1++)
    for (int h3=0; h3<h3u; h3++)
    //t3(h3,h1,h2,p6,p5,p4)-=t1(p4,h1)*v2(h3,h2,p6,p5);
    t3[h3+h3u*(h1+h1u*(h2+h2u*(p6+p6u*(p5+p5u*p4))))] -= t1[p4+p4u*h1] * v2[h3+h3u*(h2+h2u*(p6+p6u*p5))];
    return;
}

void f2c_sd_t_s1_3_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d, 
                    double * restrict t3, double * restrict t1, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    for (int p4=0; p4<p4u; p4++)
    for (int p5=0; p5<p5u; p5++)
    for (int p6=0; p6<p6u; p6++)
    for (int h2=0; h2<h2u; h2++)
    for (int h3=0; h3<h3u; h3++)
    for (int h1=0; h1<h1u; h1++)
    //t3(h1,h3,h2,p6,p5,p4)+=t1(p4,h1)*v2(h3,h2,p6,p5);
    t3[h1+h1u*(h3+h3u*(h2+h2u*(p6+p6u*(p5+p5u*p4))))] += t1[p4+p4u*h1] * v2[h3+h3u*(h2+h2u*(p6+p6u*p5))];
    return;
}

void f2c_sd_t_s1_4_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d, 
                    double * restrict t3, double * restrict t1, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    for (int p5=0; p5<p5u; p5++)
    for (int p4=0; p4<p4u; p4++)
    for (int p6=0; p6<p6u; p6++)
    for (int h1=0; h1<h1u; h1++)
    for (int h2=0; h2<h2u; h2++)
    for (int h3=0; h3<h3u; h3++)
    //t3(h3,h2,h1,p6,p4,p5)-=t1(p4,h1)*v2(h3,h2,p6,p5);
    t3[h3+h3u*(h2+h2u*(h1+h1u*(p6+p6u*(p4+p4u*p5))))] -= t1[p4+p4u*h1] * v2[h3+h3u*(h2+h2u*(p6+p6u*p5))];
    return;
}

void f2c_sd_t_s1_5_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d, 
                    double * restrict t3, double * restrict t1, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    for (int p5=0; p5<p5u; p5++)
    for (int p4=0; p4<p4u; p4++)
    for (int p6=0; p6<p6u; p6++)
    for (int h2=0; h2<h2u; h2++)
    for (int h1=0; h1<h1u; h1++)
    for (int h3=0; h3<h3u; h3++)
    //t3(h3,h1,h2,p6,p4,p5)+=t1(p4,h1)*v2(h3,h2,p6,p5);
    t3[h3+h3u*(h1+h1u*(h2+h2u*(p6+p6u*(p4+p4u*p5))))] += t1[p4+p4u*h1] * v2[h3+h3u*(h2+h2u*(p6+p6u*p5))];
    return;
}

void f2c_sd_t_s1_6_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d, 
                    double * restrict t3, double * restrict t1, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    for (int p5=0; p5<p5u; p5++)
    for (int p4=0; p4<p4u; p4++)
    for (int p6=0; p6<p6u; p6++)
    for (int h2=0; h2<h2u; h2++)
    for (int h3=0; h3<h3u; h3++)
    for (int h1=0; h1<h1u; h1++)
    //t3(h1,h3,h2,p6,p4,p5)-=t1(p4,h1)*v2(h3,h2,p6,p5);
    t3[h1+h1u*(h3+h3u*(h2+h2u*(p6+p6u*(p4+p4u*p5))))] -= t1[p4+p4u*h1] * v2[h3+h3u*(h2+h2u*(p6+p6u*p5))];
    return;
}

void f2c_sd_t_s1_7_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d, 
                    double * restrict t3, double * restrict t1, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    for (int p5=0; p5<p5u; p5++)
    for (int p6=0; p6<p6u; p6++)
    for (int p4=0; p4<p4u; p4++)
    for (int h1=0; h1<h1u; h1++)
    for (int h2=0; h2<h2u; h2++)
    for (int h3=0; h3<h3u; h3++)
    //t3(h3,h2,h1,p4,p6,p5)+=t1(p4,h1)*v2(h3,h2,p6,p5);
    t3[h3+h3u*(h2+h2u*(h1+h1u*(p4+p4u*(p6+p6u*p5))))] += t1[p4+p4u*h1] * v2[h3+h3u*(h2+h2u*(p6+p6u*p5))];
    return;
}

void f2c_sd_t_s1_8_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d, 
                    double * restrict t3, double * restrict t1, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    for (int p5=0; p5<p5u; p5++)
    for (int p6=0; p6<p6u; p6++)
    for (int p4=0; p4<p4u; p4++)
    for (int h2=0; h2<h2u; h2++)
    for (int h1=0; h1<h1u; h1++)
    for (int h3=0; h3<h3u; h3++)
    //t3(h3,h1,h2,p4,p6,p5)-=t1(p4,h1)*v2(h3,h2,p6,p5);
    t3[h3+h3u*(h1+h1u*(h2+h2u*(p4+p4u*(p6+p6u*p5))))] -= t1[p4+p4u*h1] * v2[h3+h3u*(h2+h2u*(p6+p6u*p5))];
    return;
}

void f2c_sd_t_s1_9_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d, 
                    double * restrict t3, double * restrict t1, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    for (int p5=0; p5<p5u; p5++)
    for (int p6=0; p6<p6u; p6++)
    for (int p4=0; p4<p4u; p4++)
    for (int h2=0; h2<h2u; h2++)
    for (int h3=0; h3<h3u; h3++)
    for (int h1=0; h1<h1u; h1++)
    //t3(h1,h3,h2,p4,p6,p5)+=t1(p4,h1)*v2(h3,h2,p6,p5);
    t3[h1+h1u*(h3+h3u*(h2+h2u*(p4+p4u*(p6+p6u*p5))))] += t1[p4+p4u*h1] * v2[h3+h3u*(h2+h2u*(p6+p6u*p5))];
    return;
}

#if 0
void f2c_sd_t_d1_1_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d, 
                    const fint * h7d, 
                    double * restrict t3, double * restrict t2, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    const int h7u = (int)(*h7d);
    for (int p4=0; p4<p4u; p4++)
    for (int p5=0; p5<p5u; p5++)
    for (int p6=0; p6<p6u; p6++)
    for (int h1=0; h1<h1u; h1++)
    for (int h2=0; h2<h2u; h2++)
    for (int h3=0; h3<h3u; h3++)
    for (int h7=0; h7<h7u; h7++)
    t3(h3,h2,h1,p6,p5,p4)-=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    return;
}

void f2c_sd_t_d1_2_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d,
                    const fint * h7d, 
                    double * restrict t3, double * restrict t2, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    const int h7u = (int)(*h7d);
    for (int p4=0; p4<p4u; p4++)
    for (int p5=0; p5<p5u; p5++)
    for (int p6=0; p6<p6u; p6++)
    for (int h2=0; h2<h2u; h2++)
    for (int h1=0; h1<h1u; h1++)
    for (int h3=0; h3<h3u; h3++)
    for (int h7=0; h7<h7u; h7++)
    t3(h3,h1,h2,p6,p5,p4)+=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    return;
}

void f2c_sd_t_d1_3_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d,
                    const fint * h7d, 
                    double * restrict t3, double * restrict t2, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    const int h7u = (int)(*h7d);
    for (int p4=0; p4<p4u; p4++)
    for (int p5=0; p5<p5u; p5++)
    for (int p6=0; p6<p6u; p6++)
    for (int h2=0; h2<h2u; h2++)
    for (int h3=0; h3<h3u; h3++)
    for (int h1=0; h1<h1u; h1++)
    for (int h7=0; h7<h7u; h7++)
    t3(h1,h3,h2,p6,p5,p4)-=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    return;
}

void f2c_sd_t_d1_4_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d,
                    const fint * h7d, 
                    double * restrict t3, double * restrict t2, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    const int h7u = (int)(*h7d);
    for (int p6=0; p6<p6u; p6++)
    for (int p4=0; p4<p4u; p4++)
    for (int p5=0; p5<p5u; p5++)
    for (int h1=0; h1<h1u; h1++)
    for (int h2=0; h2<h2u; h2++)
    for (int h3=0; h3<h3u; h3++)
    for (int h7=0; h7<h7u; h7++)
    t3(h3,h2,h1,p5,p4,p6)-=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    return;
}

void f2c_sd_t_d1_5_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d,
                    const fint * h7d, 
                    double * restrict t3, double * restrict t2, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    const int h7u = (int)(*h7d);
    for (int p6=0; p6<p6u; p6++)
    for (int p4=0; p4<p4u; p4++)
    for (int p5=0; p5<p5u; p5++)
    for (int h2=0; h2<h2u; h2++)
    for (int h1=0; h1<h1u; h1++)
    for (int h3=0; h3<h3u; h3++)
    for (int h7=0; h7<h7u; h7++)
    t3(h3,h1,h2,p5,p4,p6)+=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    return;
}

void f2c_sd_t_d1_6_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d,
                    const fint * h7d, 
                    double * restrict t3, double * restrict t2, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    const int h7u = (int)(*h7d);
    for (int p6=0; p6<p6u; p6++)
    for (int p4=0; p4<p4u; p4++)
    for (int p5=0; p5<p5u; p5++)
    for (int h2=0; h2<h2u; h2++)
    for (int h3=0; h3<h3u; h3++)
    for (int h1=0; h1<h1u; h1++)
    for (int h7=0; h7<h7u; h7++)
    t3(h1,h3,h2,p5,p4,p6)-=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    return;
}

void f2c_sd_t_d1_7_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d, 
                    const fint * h7d, 
                    double * restrict t3, double * restrict t2, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    const int h7u = (int)(*h7d);
    for (int p4=0; p4<p4u; p4++)
    for (int p6=0; p6<p6u; p6++)
    for (int p5=0; p5<p5u; p5++)
    for (int h1=0; h1<h1u; h1++)
    for (int h2=0; h2<h2u; h2++)
    for (int h3=0; h3<h3u; h3++)
    for (int h7=0; h7<h7u; h7++)
    t3(h3,h2,h1,p5,p6,p4)+=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    return;
}

void f2c_sd_t_d1_8_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d, 
                    const fint * h7d, 
                    double * restrict t3, double * restrict t2, double * restrict v2)
{
    for (int p4=0; p4<p4u; p4++)
    for (int p6=0; p6<p6u; p6++)
    for (int p5=0; p5<p5u; p5++)
    for (int h2=0; h2<h2u; h2++)
    for (int h1=0; h1<h1u; h1++)
    for (int h3=0; h3<h3u; h3++)
    for (int h7=0; h7<h7u; h7++)
    t3(h3,h1,h2,p5,p6,p4)-=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    return;
}

void f2c_sd_t_d1_9_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d, 
                    const fint * h7d, 
                    double * restrict t3, double * restrict t2, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    const int h7u = (int)(*h7d);
    for (int p4=0; p4<p4u; p4++)
    for (int p6=0; p6<p6u; p6++)
    for (int p5=0; p5<p5u; p5++)
    for (int h2=0; h2<h2u; h2++)
    for (int h3=0; h3<h3u; h3++)
    for (int h1=0; h1<h1u; h1++)
    for (int h7=0; h7<h7u; h7++)
    t3(h1,h3,h2,p5,p6,p4)+=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    return;
}

void f2c_sd_t_d2_1_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d, 
                    const fint * p7d, 
                    double * restrict t3, double * restrict t2, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    const int p7u = (int)(*p7d);
    for (int p4=0; p4<p4u; p4++)
    for (int p5=0; p5<p5u; p5++)
    for (int p6=0; p6<p6u; p6++)
    for (int h1=0; h1<h1u; h1++)
    for (int h2=0; h2<h2u; h2++)
    for (int h3=0; h3<h3u; h3++)
    for (int p7=0; p7<p7u; p7++)
    t3(h3,h2,h1,p6,p5,p4)-=t2(p7,p4,h1,h2)*v2(p7,h3,p6,p5);
    return;
}

void f2c_sd_t_d2_2_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d, 
                    const fint * p7d, 
                    double * restrict t3, double * restrict t2, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    const int p7u = (int)(*p7d);
    for (int p4=0; p4<p4u; p4++)
    for (int p5=0; p5<p5u; p5++)
    for (int p6=0; p6<p6u; p6++)
    for (int h3=0; h3<h3u; h3++)
    for (int h1=0; h1<h1u; h1++)
    for (int h2=0; h2<h2u; h2++)
    for (int p7=0; p7<p7u; p7++)
    t3(h2,h1,h3,p6,p5,p4)-=t2(p7,p4,h1,h2)*v2(p7,h3,p6,p5);
    return;
}

void f2c_sd_t_d2_3_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d, 
                    const fint * p7d, 
                    double * restrict t3, double * restrict t2, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    const int p7u = (int)(*p7d);
    for (int p4=0; p4<p4u; p4++)
    for (int p5=0; p5<p5u; p5++)
    for (int p6=0; p6<p6u; p6++)
    for (int h1=0; h1<h1u; h1++)
    for (int h3=0; h3<h3u; h3++)
    for (int h2=0; h2<h2u; h2++)
    for (int p7=0; p7<p7u; p7++)
    t3(h2,h3,h1,p6,p5,p4)+=t2(p7,p4,h1,h2)*v2(p7,h3,p6,p5);
    return;
}

void f2c_sd_t_d2_4_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d, 
                    const fint * p7d, 
                    double * restrict t3, double * restrict t2, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    const int p7u = (int)(*p7d);
    for (int p5=0; p5<p5u; p5++)
    for (int p4=0; p4<p4u; p4++)
    for (int p6=0; p6<p6u; p6++)
    for (int h1=0; h1<h1u; h1++)
    for (int h2=0; h2<h2u; h2++)
    for (int h3=0; h3<h3u; h3++)
    for (int p7=0; p7<p7u; p7++)
    t3(h3,h2,h1,p6,p4,p5)+=t2(p7,p4,h1,h2)*v2(p7,h3,p6,p5);
    return;
}

void f2c_sd_t_d2_5_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d, 
                    const fint * p7d, 
                    double * restrict t3, double * restrict t2, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    const int p7u = (int)(*p7d);
    for (int p5=0; p5<p5u; p5++)
    for (int p4=0; p4<p4u; p4++)
    for (int p6=0; p6<p6u; p6++)
    for (int h3=0; h3<h3u; h3++)
    for (int h1=0; h1<h1u; h1++)
    for (int h2=0; h2<h2u; h2++)
    for (int p7=0; p7<p7u; p7++)
    t3(h2,h1,h3,p6,p4,p5)+=t2(p7,p4,h1,h2)*v2(p7,h3,p6,p5);
    return;
}

void f2c_sd_t_d2_6_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d, 
                    const fint * p7d, 
                    double * restrict t3, double * restrict t2, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    const int p7u = (int)(*p7d);
    for (int p5=0; p5<p5u; p5++)
    for (int p4=0; p4<p4u; p4++)
    for (int p6=0; p6<p6u; p6++)
    for (int h1=0; h1<h1u; h1++)
    for (int h3=0; h3<h3u; h3++)
    for (int h2=0; h2<h2u; h2++)
    for (int p7=0; p7<p7u; p7++)
    t3(h2,h3,h1,p6,p4,p5)-=t2(p7,p4,h1,h2)*v2(p7,h3,p6,p5);
    return;
}

void f2c_sd_t_d2_7_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d, 
                    const fint * p7d, 
                    double * restrict t3, double * restrict t2, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    const int p7u = (int)(*p7d);
    for (int p5=0; p5<p5u; p5++)
    for (int p6=0; p6<p6u; p6++)
    for (int p4=0; p4<p4u; p4++)
    for (int h1=0; h1<h1u; h1++)
    for (int h2=0; h2<h2u; h2++)
    for (int h3=0; h3<h3u; h3++)
    for (int p7=0; p7<p7u; p7++)
    t3(h3,h2,h1,p4,p6,p5)-=t2(p7,p4,h1,h2)*v2(p7,h3,p6,p5);
    return;
}

void f2c_sd_t_d2_8_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d, 
                    const fint * p7d, 
                    double * restrict t3, double * restrict t2, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    const int p7u = (int)(*p7d);
    for (int p5=0; p5<p5u; p5++)
    for (int p6=0; p6<p6u; p6++)
    for (int p4=0; p4<p4u; p4++)
    for (int h3=0; h3<h3u; h3++)
    for (int h1=0; h1<h1u; h1++)
    for (int h2=0; h2<h2u; h2++)
    for (int p7=0; p7<p7u; p7++)
    t3(h2,h1,h3,p4,p6,p5)-=t2(p7,p4,h1,h2)*v2(p7,h3,p6,p5);
    return;
}

void f2c_sd_t_d2_9_(const fint * h3d, const fint * h2d, const fint * h1d, 
                    const fint * p6d, const fint * p5d, const fint * p4d, 
                    const fint * p7d, 
                    double * restrict t3, double * restrict t2, double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    const int p7u = (int)(*p7d);
    for (int p5=0; p5<p5u; p5++)
    for (int p6=0; p6<p6u; p6++)
    for (int p4=0; p4<p4u; p4++)
    for (int h1=0; h1<h1u; h1++)
    for (int h3=0; h3<h3u; h3++)
    for (int h2=0; h2<h2u; h2++)
    for (int p7=0; p7<p7u; p7++)
    t3(h2,h3,h1,p4,p6,p5)+=t2(p7,p4,h1,h2)*v2(p7,h3,p6,p5);
    return;
}

#endif
