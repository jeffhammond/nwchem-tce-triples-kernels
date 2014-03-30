/* These have been separated out from ccsd_t_singles_l.F and ccsd_t_doubles_l.F
 * and converted from Fortran 77 to C99 by hand. */

#include "ccsd_t_kernels.h"

/* The possible downcast from fint to int is safe because array dimensions
 * are on the order of 30, i.e. nowhere near INT_MAX. */

static inline void __c99_sd_t_s1_1(const int h3u, const int h2u, const int h1u,
                                   const int p6u, const int p5u, const int p4u,
                                   double t3[p4u][p5u][p6u][h1u][h2u][h3u],
                                   const double t1[h1u][p4u],
                                   const double v2[p5u][p6u][h2u][h3u])
{
#ifdef _OPENMP
#pragma omp parallel for collapse(4)
#pragma omp default(shared) schedule(static)
#endif
    for (int p4=0; p4<p4u; p4++)
    for (int p5=0; p5<p5u; p5++)
    for (int p6=0; p6<p6u; p6++)
    for (int h1=0; h1<h1u; h1++)
    for (int h2=0; h2<h2u; h2++)
    for (int h3=0; h3<h3u; h3++)
    //t3(h3,h2,h1,p6,p5,p4)+=t1(p4,h1)*v2(h3,h2,p6,p5);
    t3[p4][p5][p6][h1][h2][h3] += t1[h1][p4] * v2[p5][p6][h2][h3];
    return;
}

void c99_sd_t_s1_1_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    double * restrict t3, const double * restrict t1, const double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    __c99_sd_t_s1_1(h3u, h2u, h1u, p6u, p5u, p4u, t3, t1, v2);
    return;
}

void c99_sd_t_s1_2_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    double * restrict t3, const double * restrict t1, const double * restrict v2)
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

void c99_sd_t_s1_3_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    double * restrict t3, const double * restrict t1, const double * restrict v2)
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

void c99_sd_t_s1_4_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    double * restrict t3, const double * restrict t1, const double * restrict v2)
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

void c99_sd_t_s1_5_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    double * restrict t3, const double * restrict t1, const double * restrict v2)
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

void c99_sd_t_s1_6_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    double * restrict t3, const double * restrict t1, const double * restrict v2)
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

void c99_sd_t_s1_7_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    double * restrict t3, const double * restrict t1, const double * restrict v2)
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

void c99_sd_t_s1_8_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    double * restrict t3, const double * restrict t1, const double * restrict v2)
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

void c99_sd_t_s1_9_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    double * restrict t3, const double * restrict t1, const double * restrict v2)
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

static inline void __c99_sd_t_d1_1(const int h3u, const int h2u, const int h1u,
                                   const int p6u, const int p5u, const int p4u,
                                   const int h7u,
                                   double t3[p4u][p5u][p6u][h1u][h2u][h3u],
                                   const double t2[h1u][p5u][p4u][h7u],
                                   const double v2[h7u][p6u][h2u][h3u])
{
#ifdef _OPENMP
#pragma omp parallel for collapse(4)
#pragma omp default(shared) schedule(static)
#endif
    for (int p4=0; p4<p4u; p4++)
    for (int p5=0; p5<p5u; p5++)
    for (int p6=0; p6<p6u; p6++)
    for (int h1=0; h1<h1u; h1++)
    for (int h2=0; h2<h2u; h2++)
    for (int h3=0; h3<h3u; h3++)
    for (int h7=0; h7<h7u; h7++)
    //t3(h3,h2,h1,p6,p5,p4)-=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    t3[p4][p5][p6][h1][h2][h3] += t2[h1][p5][p4][h7] * v2[h7][p6][h2][h3];
    return;
}

void c99_sd_t_d1_1_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    fint * h7d,
                    double * restrict t3, const double * restrict t2, const double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    const int h7u = (int)(*h7d);
    __c99_sd_t_d1_1(h3u, h2u, h1u, p6u, p5u, p4u, h7u, t3, t2, v2);
    return;
}

void c99_sd_t_d1_2_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    fint * h7d,
                    double * restrict t3, const double * restrict t2, const double * restrict v2)
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
    //t3(h3,h1,h2,p6,p5,p4)+=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    t3[h3+h3u*(h1+h1u*(h2+h2u*(p6+p6u*(p5+p5u*p4))))] += t2[h7+h7u*(p4+p4u*(p5+p5u*h1))] * v2[h3+h3u*(h2+h2u*(p6+p6u*h7))];
    return;
}

void c99_sd_t_d1_3_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    fint * h7d,
                    double * restrict t3, const double * restrict t2, const double * restrict v2)
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
    //t3(h1,h3,h2,p6,p5,p4)-=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    t3[h1+h1u*(h3+h3u*(h2+h2u*(p6+p6u*(p5+p5u*p4))))] -= t2[h7+h7u*(p4+p4u*(p5+p5u*h1))] * v2[h3+h3u*(h2+h2u*(p6+p6u*h7))];
    return;
}

void c99_sd_t_d1_4_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    fint * h7d,
                    double * restrict t3, const double * restrict t2, const double * restrict v2)
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
    //t3(h3,h2,h1,p5,p4,p6)-=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    t3[h3+h3u*(h2+h2u*(h1+h1u*(p5+p5u*(p4+p4u*p6))))] -= t2[h7+h7u*(p4+p4u*(p5+p5u*h1))] * v2[h3+h3u*(h2+h2u*(p6+p6u*h7))];
    return;
}

void c99_sd_t_d1_5_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    fint * h7d,
                    double * restrict t3, const double * restrict t2, const double * restrict v2)
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
    //t3(h3,h1,h2,p5,p4,p6)+=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    t3[h3+h3u*(h1+h1u*(h2+h2u*(p5+p5u*(p4+p4u*p6))))] += t2[h7+h7u*(p4+p4u*(p5+p5u*h1))] * v2[h3+h3u*(h2+h2u*(p6+p6u*h7))];
    return;
}

void c99_sd_t_d1_6_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    fint * h7d,
                    double * restrict t3, const double * restrict t2, const double * restrict v2)
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
    //t3(h1,h3,h2,p5,p4,p6)-=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    t3[h1+h1u*(h3+h3u*(h2+h2u*(p5+p5u*(p4+p4u*p6))))] -= t2[h7+h7u*(p4+p4u*(p5+p5u*h1))] * v2[h3+h3u*(h2+h2u*(p6+p6u*h7))];
    return;
}

void c99_sd_t_d1_7_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    fint * h7d,
                    double * restrict t3, const double * restrict t2, const double * restrict v2)
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
    //t3(h3,h2,h1,p5,p6,p4)+=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    t3[h3+h3u*(h2+h2u*(h1+h1u*(p5+p5u*(p6+p6u*p4))))] += t2[h7+h7u*(p4+p4u*(p5+p5u*h1))] * v2[h3+h3u*(h2+h2u*(p6+p6u*h7))];
    return;
}

void c99_sd_t_d1_8_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    fint * h7d,
                    double * restrict t3, const double * restrict t2, const double * restrict v2)
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
    for (int h1=0; h1<h1u; h1++)
    for (int h3=0; h3<h3u; h3++)
    for (int h7=0; h7<h7u; h7++)
    //t3(h3,h1,h2,p5,p6,p4)-=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    t3[h3+h3u*(h1+h1u*(h2+h2u*(p5+p5u*(p6+p6u*p4))))] -= t2[h7+h7u*(p4+p4u*(p5+p5u*h1))] * v2[h3+h3u*(h2+h2u*(p6+p6u*h7))];
    return;
}

void c99_sd_t_d1_9_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    fint * h7d,
                    double * restrict t3, const double * restrict t2, const double * restrict v2)
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
    //t3(h1,h3,h2,p5,p6,p4)+=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    t3[h1+h1u*(h3+h3u*(h2+h2u*(p5+p5u*(p6+p6u*p4))))] += t2[h7+h7u*(p4+p4u*(p5+p5u*h1))] * v2[h3+h3u*(h2+h2u*(p6+p6u*h7))];
    return;
}

void c99_sd_t_d2_1_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    fint * h7d,
                    double * restrict t3, const double * restrict t2, const double * restrict v2)
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
    //t3(h3,h2,h1,p6,p5,p4)-=t2(h7,p4,h1,h2)*v2(h7,h3,p6,p5);
    t3[h3+h3u*(h2+h2u*(h1+h1u*(p6+p6u*(p5+p5u*p4))))] -= t2[h7+h7u*(p4+p4u*(h1+h1u*h2))] * v2[h7+h7u*(h3+h3u*(p6+p6u*p5))];
    return;
}

void c99_sd_t_d2_2_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    fint * h7d,
                    double * restrict t3, const double * restrict t2, const double * restrict v2)
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
    for (int h3=0; h3<h3u; h3++)
    for (int h1=0; h1<h1u; h1++)
    for (int h2=0; h2<h2u; h2++)
    for (int h7=0; h7<h7u; h7++)
    //t3(h2,h1,h3,p6,p5,p4)-=t2(h7,p4,h1,h2)*v2(h7,h3,p6,p5);
    t3[h2+h2u*(h1+h1u*(h3+h3u*(p6+p6u*(p5+p5u*p4))))] -= t2[h7+h7u*(p4+p4u*(h1+h1u*h2))] * v2[h7+h7u*(h3+h3u*(p6+p6u*p5))];
    return;
}

void c99_sd_t_d2_3_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    fint * h7d,
                    double * restrict t3, const double * restrict t2, const double * restrict v2)
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
    for (int h3=0; h3<h3u; h3++)
    for (int h2=0; h2<h2u; h2++)
    for (int h7=0; h7<h7u; h7++)
    //t3(h2,h3,h1,p6,p5,p4)+=t2(h7,p4,h1,h2)*v2(h7,h3,p6,p5);
    t3[h2+h2u*(h3+h3u*(h1+h1u*(p6+p6u*(p5+p5u*p4))))] += t2[h7+h7u*(p4+p4u*(h1+h1u*h2))] * v2[h7+h7u*(h3+h3u*(p6+p6u*p5))];
    return;
}

void c99_sd_t_d2_4_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    fint * h7d,
                    double * restrict t3, const double * restrict t2, const double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    const int h7u = (int)(*h7d);
    for (int p5=0; p5<p5u; p5++)
    for (int p4=0; p4<p4u; p4++)
    for (int p6=0; p6<p6u; p6++)
    for (int h1=0; h1<h1u; h1++)
    for (int h2=0; h2<h2u; h2++)
    for (int h3=0; h3<h3u; h3++)
    for (int h7=0; h7<h7u; h7++)
    //t3(h3,h2,h1,p6,p4,p5)+=t2(h7,p4,h1,h2)*v2(h7,h3,p6,p5);
    t3[h3+h3u*(h2+h2u*(h1+h1u*(p6+p6u*(p4+p4u*p5))))] += t2[h7+h7u*(p4+p4u*(h1+h1u*h2))] * v2[h7+h7u*(h3+h3u*(p6+p6u*p5))];
    return;
}

void c99_sd_t_d2_5_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    fint * h7d,
                    double * restrict t3, const double * restrict t2, const double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    const int h7u = (int)(*h7d);
    for (int p5=0; p5<p5u; p5++)
    for (int p4=0; p4<p4u; p4++)
    for (int p6=0; p6<p6u; p6++)
    for (int h3=0; h3<h3u; h3++)
    for (int h1=0; h1<h1u; h1++)
    for (int h2=0; h2<h2u; h2++)
    for (int h7=0; h7<h7u; h7++)
    //t3(h2,h1,h3,p6,p4,p5)+=t2(h7,p4,h1,h2)*v2(h7,h3,p6,p5);
    t3[h2+h2u*(h1+h1u*(h3+h3u*(p6+p6u*(p4+p4u*p5))))] += t2[h7+h7u*(p4+p4u*(h1+h1u*h2))] * v2[h7+h7u*(h3+h3u*(p6+p6u*p5))];
    return;
}

void c99_sd_t_d2_6_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    fint * h7d,
                    double * restrict t3, const double * restrict t2, const double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    const int h7u = (int)(*h7d);
    for (int p5=0; p5<p5u; p5++)
    for (int p4=0; p4<p4u; p4++)
    for (int p6=0; p6<p6u; p6++)
    for (int h1=0; h1<h1u; h1++)
    for (int h3=0; h3<h3u; h3++)
    for (int h2=0; h2<h2u; h2++)
    for (int h7=0; h7<h7u; h7++)
    //t3(h2,h3,h1,p6,p4,p5)-=t2(h7,p4,h1,h2)*v2(h7,h3,p6,p5);
    t3[h2+h2u*(h3+h3u*(h1+h1u*(p6+p6u*(p4+p4u*p5))))] -= t2[h7+h7u*(p4+p4u*(h1+h1u*h2))] * v2[h7+h7u*(h3+h3u*(p6+p6u*p5))];
    return;
}

void c99_sd_t_d2_7_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    fint * h7d,
                    double * restrict t3, const double * restrict t2, const double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    const int h7u = (int)(*h7d);
    for (int p5=0; p5<p5u; p5++)
    for (int p6=0; p6<p6u; p6++)
    for (int p4=0; p4<p4u; p4++)
    for (int h1=0; h1<h1u; h1++)
    for (int h2=0; h2<h2u; h2++)
    for (int h3=0; h3<h3u; h3++)
    for (int h7=0; h7<h7u; h7++)
    //t3(h3,h2,h1,p4,p6,p5)-=t2(h7,p4,h1,h2)*v2(h7,h3,p6,p5);
    t3[h3+h3u*(h2+h2u*(h1+h1u*(p4+p4u*(p6+p6u*p5))))] -= t2[h7+h7u*(p4+p4u*(h1+h1u*h2))] * v2[h7+h7u*(h3+h3u*(p6+p6u*p5))];
    return;
}

void c99_sd_t_d2_8_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    fint * h7d,
                    double * restrict t3, const double * restrict t2, const double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    const int h7u = (int)(*h7d);
    for (int p5=0; p5<p5u; p5++)
    for (int p6=0; p6<p6u; p6++)
    for (int p4=0; p4<p4u; p4++)
    for (int h3=0; h3<h3u; h3++)
    for (int h1=0; h1<h1u; h1++)
    for (int h2=0; h2<h2u; h2++)
    for (int h7=0; h7<h7u; h7++)
    //t3(h2,h1,h3,p4,p6,p5)-=t2(h7,p4,h1,h2)*v2(h7,h3,p6,p5);
    t3[h2+h2u*(h1+h1u*(h3+h3u*(p4+p4u*(p6+p6u*p5))))] -= t2[h7+h7u*(p4+p4u*(h1+h1u*h2))] * v2[h7+h7u*(h3+h3u*(p6+p6u*p5))];
    return;
}

void c99_sd_t_d2_9_(fint * h3d, fint * h2d, fint * h1d,
                    fint * p6d, fint * p5d, fint * p4d,
                    fint * h7d,
                    double * restrict t3, const double * restrict t2, const double * restrict v2)
{
    const int h1u = (int)(*h1d);
    const int h2u = (int)(*h2d);
    const int h3u = (int)(*h3d);
    const int p4u = (int)(*p4d);
    const int p5u = (int)(*p5d);
    const int p6u = (int)(*p6d);
    const int h7u = (int)(*h7d);
    for (int p5=0; p5<p5u; p5++)
    for (int p6=0; p6<p6u; p6++)
    for (int p4=0; p4<p4u; p4++)
    for (int h1=0; h1<h1u; h1++)
    for (int h3=0; h3<h3u; h3++)
    for (int h2=0; h2<h2u; h2++)
    for (int h7=0; h7<h7u; h7++)
    //t3(h2,h3,h1,p4,p6,p5)+=t2(h7,p4,h1,h2)*v2(h7,h3,p6,p5);
    t3[h2+h2u*(h3+h3u*(h1+h1u*(p4+p4u*(p6+p6u*p5))))] += t2[h7+h7u*(p4+p4u*(h1+h1u*h2))] * v2[h7+h7u*(h3+h3u*(p6+p6u*p5))];
    return;
}
