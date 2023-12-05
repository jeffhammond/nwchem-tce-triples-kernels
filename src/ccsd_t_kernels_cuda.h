void cuda_sd_t_s1_1(int tilesize, double * restrict t3, const double * restrict t1, const double * restrict v2)
{
    //t3(h3,h2,h1,p6,p5,p4)+=t1(p4,h1)*v2(h3,h2,p6,p5);
    t3[h3+tilesize*(h2+tilesize*(h1+tilesize*(p6+tilesize*(p5+tilesize*p4))))] += t1[p4+tilesize*h1] * v2[h3+tilesize*(h2+tilesize*(p6+tilesize*p5))];
}

void cuda_sd_t_s1_2(int tilesize, double * restrict t3, const double * restrict t1, const double * restrict v2)
{
    //t3(h3,h1,h2,p6,p5,p4)-=t1(p4,h1)*v2(h3,h2,p6,p5);
    t3[h3+tilesize*(h1+tilesize*(h2+tilesize*(p6+tilesize*(p5+tilesize*p4))))] -= t1[p4+tilesize*h1] * v2[h3+tilesize*(h2+tilesize*(p6+tilesize*p5))];
}

void cuda_sd_t_s1_3(int tilesize, double * restrict t3, const double * restrict t1, const double * restrict v2)
{
    //t3(h1,h3,h2,p6,p5,p4)+=t1(p4,h1)*v2(h3,h2,p6,p5);
    t3[h1+tilesize*(h3+tilesize*(h2+tilesize*(p6+tilesize*(p5+tilesize*p4))))] += t1[p4+tilesize*h1] * v2[h3+tilesize*(h2+tilesize*(p6+tilesize*p5))];
}

void cuda_sd_t_s1_4(int tilesize, double * restrict t3, const double * restrict t1, const double * restrict v2)
{
    //t3(h3,h2,h1,p6,p4,p5)-=t1(p4,h1)*v2(h3,h2,p6,p5);
    t3[h3+tilesize*(h2+tilesize*(h1+tilesize*(p6+tilesize*(p4+tilesize*p5))))] -= t1[p4+tilesize*h1] * v2[h3+tilesize*(h2+tilesize*(p6+tilesize*p5))];
}

void cuda_sd_t_s1_5(int tilesize, double * restrict t3, const double * restrict t1, const double * restrict v2)
{
    //t3(h3,h1,h2,p6,p4,p5)+=t1(p4,h1)*v2(h3,h2,p6,p5);
    t3[h3+tilesize*(h1+tilesize*(h2+tilesize*(p6+tilesize*(p4+tilesize*p5))))] += t1[p4+tilesize*h1] * v2[h3+tilesize*(h2+tilesize*(p6+tilesize*p5))];
}

void cuda_sd_t_s1_6(int tilesize, double * restrict t3, const double * restrict t1, const double * restrict v2)
{
    //t3(h1,h3,h2,p6,p4,p5)-=t1(p4,h1)*v2(h3,h2,p6,p5);
    t3[h1+tilesize*(h3+tilesize*(h2+tilesize*(p6+tilesize*(p4+tilesize*p5))))] -= t1[p4+tilesize*h1] * v2[h3+tilesize*(h2+tilesize*(p6+tilesize*p5))];
}

void cuda_sd_t_s1_7(int tilesize, double * restrict t3, const double * restrict t1, const double * restrict v2)
{
    //t3(h3,h2,h1,p4,p6,p5)+=t1(p4,h1)*v2(h3,h2,p6,p5);
    t3[h3+tilesize*(h2+tilesize*(h1+tilesize*(p4+tilesize*(p6+tilesize*p5))))] += t1[p4+tilesize*h1] * v2[h3+tilesize*(h2+tilesize*(p6+tilesize*p5))];
}

void cuda_sd_t_s1_8(int tilesize, double * restrict t3, const double * restrict t1, const double * restrict v2)
{
    //t3(h3,h1,h2,p4,p6,p5)-=t1(p4,h1)*v2(h3,h2,p6,p5);
    t3[h3+tilesize*(h1+tilesize*(h2+tilesize*(p4+tilesize*(p6+tilesize*p5))))] -= t1[p4+tilesize*h1] * v2[h3+tilesize*(h2+tilesize*(p6+tilesize*p5))];
}

void cuda_sd_t_s1_9(int tilesize, double * restrict t3, const double * restrict t1, const double * restrict v2)
{
    //t3(h1,h3,h2,p4,p6,p5)+=t1(p4,h1)*v2(h3,h2,p6,p5);
    t3[h1+tilesize*(h3+tilesize*(h2+tilesize*(p4+tilesize*(p6+tilesize*p5))))] += t1[p4+tilesize*h1] * v2[h3+tilesize*(h2+tilesize*(p6+tilesize*p5))];
}

void cuda_sd_t_d1_1(int tilesize, double * restrict t3, const double * restrict t2, const double * restrict v2)
{
    for (int h7=0; h7<tilesize; h7++)
    //t3(h3,h2,h1,p6,p5,p4)-=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    t3[h3+tilesize*(h2+tilesize*(h1+tilesize*(p6+tilesize*(p5+tilesize*p4))))] -= t2[h7+tilesize*(p4+tilesize*(p5+tilesize*h1))] * v2[h3+tilesize*(h2+tilesize*(p6+tilesize*h7))];
}

void cuda_sd_t_d1_2(int tilesize, double * restrict t3, const double * restrict t2, const double * restrict v2)
{
    for (int h7=0; h7<tilesize; h7++)
    //t3(h3,h1,h2,p6,p5,p4)+=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    t3[h3+tilesize*(h1+tilesize*(h2+tilesize*(p6+tilesize*(p5+tilesize*p4))))] += t2[h7+tilesize*(p4+tilesize*(p5+tilesize*h1))] * v2[h3+tilesize*(h2+tilesize*(p6+tilesize*h7))];
}

void cuda_sd_t_d1_3(int tilesize, double * restrict t3, const double * restrict t2, const double * restrict v2)
{
    for (int h7=0; h7<tilesize; h7++)
    //t3(h1,h3,h2,p6,p5,p4)-=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    t3[h1+tilesize*(h3+tilesize*(h2+tilesize*(p6+tilesize*(p5+tilesize*p4))))] -= t2[h7+tilesize*(p4+tilesize*(p5+tilesize*h1))] * v2[h3+tilesize*(h2+tilesize*(p6+tilesize*h7))];
}

void cuda_sd_t_d1_4(int tilesize, double * restrict t3, const double * restrict t2, const double * restrict v2)
{
    for (int h7=0; h7<tilesize; h7++)
    //t3(h3,h2,h1,p5,p4,p6)-=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    t3[h3+tilesize*(h2+tilesize*(h1+tilesize*(p5+tilesize*(p4+tilesize*p6))))] -= t2[h7+tilesize*(p4+tilesize*(p5+tilesize*h1))] * v2[h3+tilesize*(h2+tilesize*(p6+tilesize*h7))];
}

void cuda_sd_t_d1_5(int tilesize, double * restrict t3, const double * restrict t2, const double * restrict v2)
{
    for (int h7=0; h7<tilesize; h7++)
    //t3(h3,h1,h2,p5,p4,p6)+=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    t3[h3+tilesize*(h1+tilesize*(h2+tilesize*(p5+tilesize*(p4+tilesize*p6))))] += t2[h7+tilesize*(p4+tilesize*(p5+tilesize*h1))] * v2[h3+tilesize*(h2+tilesize*(p6+tilesize*h7))];
}

void cuda_sd_t_d1_6(int tilesize, double * restrict t3, const double * restrict t2, const double * restrict v2)
{
    for (int h7=0; h7<tilesize; h7++)
    //t3(h1,h3,h2,p5,p4,p6)-=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    t3[h1+tilesize*(h3+tilesize*(h2+tilesize*(p5+tilesize*(p4+tilesize*p6))))] -= t2[h7+tilesize*(p4+tilesize*(p5+tilesize*h1))] * v2[h3+tilesize*(h2+tilesize*(p6+tilesize*h7))];
}

void cuda_sd_t_d1_7(int tilesize, double * restrict t3, const double * restrict t2, const double * restrict v2)
{
    for (int h7=0; h7<tilesize; h7++)
    //t3(h3,h2,h1,p5,p6,p4)+=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    t3[h3+tilesize*(h2+tilesize*(h1+tilesize*(p5+tilesize*(p6+tilesize*p4))))] += t2[h7+tilesize*(p4+tilesize*(p5+tilesize*h1))] * v2[h3+tilesize*(h2+tilesize*(p6+tilesize*h7))];
}

void cuda_sd_t_d1_8(int tilesize, double * restrict t3, const double * restrict t2, const double * restrict v2)
{
    for (int h7=0; h7<tilesize; h7++)
    //t3(h3,h1,h2,p5,p6,p4)-=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    t3[h3+tilesize*(h1+tilesize*(h2+tilesize*(p5+tilesize*(p6+tilesize*p4))))] -= t2[h7+tilesize*(p4+tilesize*(p5+tilesize*h1))] * v2[h3+tilesize*(h2+tilesize*(p6+tilesize*h7))];
}

void cuda_sd_t_d1_9(int tilesize, double * restrict t3, const double * restrict t2, const double * restrict v2)
{
    for (int h7=0; h7<tilesize; h7++)
    //t3(h1,h3,h2,p5,p6,p4)+=t2(h7,p4,p5,h1)*v2(h3,h2,p6,h7);
    t3[h1+tilesize*(h3+tilesize*(h2+tilesize*(p5+tilesize*(p6+tilesize*p4))))] += t2[h7+tilesize*(p4+tilesize*(p5+tilesize*h1))] * v2[h3+tilesize*(h2+tilesize*(p6+tilesize*h7))];
}

void cuda_sd_t_d2_1(int tilesize, double * restrict t3, const double * restrict t2, const double * restrict v2)
{
    for (int h7=0; h7<tilesize; h7++)
    //t3(h3,h2,h1,p6,p5,p4)-=t2(h7,p4,h1,h2)*v2(h7,h3,p6,p5);
    t3[h3+tilesize*(h2+tilesize*(h1+tilesize*(p6+tilesize*(p5+tilesize*p4))))] -= t2[h7+tilesize*(p4+tilesize*(h1+tilesize*h2))] * v2[h7+tilesize*(h3+tilesize*(p6+tilesize*p5))];
}

void cuda_sd_t_d2_2(int tilesize, double * restrict t3, const double * restrict t2, const double * restrict v2)
{
    for (int h7=0; h7<tilesize; h7++)
    //t3(h2,h1,h3,p6,p5,p4)-=t2(h7,p4,h1,h2)*v2(h7,h3,p6,p5);
    t3[h2+tilesize*(h1+tilesize*(h3+tilesize*(p6+tilesize*(p5+tilesize*p4))))] -= t2[h7+tilesize*(p4+tilesize*(h1+tilesize*h2))] * v2[h7+tilesize*(h3+tilesize*(p6+tilesize*p5))];
}

void cuda_sd_t_d2_3(int tilesize, double * restrict t3, const double * restrict t2, const double * restrict v2)
{
    for (int h7=0; h7<tilesize; h7++)
    //t3(h2,h3,h1,p6,p5,p4)+=t2(h7,p4,h1,h2)*v2(h7,h3,p6,p5);
    t3[h2+tilesize*(h3+tilesize*(h1+tilesize*(p6+tilesize*(p5+tilesize*p4))))] += t2[h7+tilesize*(p4+tilesize*(h1+tilesize*h2))] * v2[h7+tilesize*(h3+tilesize*(p6+tilesize*p5))];
}

void cuda_sd_t_d2_4(int tilesize, double * restrict t3, const double * restrict t2, const double * restrict v2)
{
    for (int h7=0; h7<tilesize; h7++)
    //t3(h3,h2,h1,p6,p4,p5)+=t2(h7,p4,h1,h2)*v2(h7,h3,p6,p5);
    t3[h3+tilesize*(h2+tilesize*(h1+tilesize*(p6+tilesize*(p4+tilesize*p5))))] += t2[h7+tilesize*(p4+tilesize*(h1+tilesize*h2))] * v2[h7+tilesize*(h3+tilesize*(p6+tilesize*p5))];
}

void cuda_sd_t_d2_5(int tilesize, double * restrict t3, const double * restrict t2, const double * restrict v2)
{
    for (int h7=0; h7<tilesize; h7++)
    //t3(h2,h1,h3,p6,p4,p5)+=t2(h7,p4,h1,h2)*v2(h7,h3,p6,p5);
    t3[h2+tilesize*(h1+tilesize*(h3+tilesize*(p6+tilesize*(p4+tilesize*p5))))] += t2[h7+tilesize*(p4+tilesize*(h1+tilesize*h2))] * v2[h7+tilesize*(h3+tilesize*(p6+tilesize*p5))];
}

void cuda_sd_t_d2_6(int tilesize, double * restrict t3, const double * restrict t2, const double * restrict v2)
{
    for (int h7=0; h7<tilesize; h7++)
    //t3(h2,h3,h1,p6,p4,p5)-=t2(h7,p4,h1,h2)*v2(h7,h3,p6,p5);
    t3[h2+tilesize*(h3+tilesize*(h1+tilesize*(p6+tilesize*(p4+tilesize*p5))))] -= t2[h7+tilesize*(p4+tilesize*(h1+tilesize*h2))] * v2[h7+tilesize*(h3+tilesize*(p6+tilesize*p5))];
}

void cuda_sd_t_d2_7(int tilesize, double * restrict t3, const double * restrict t2, const double * restrict v2)
{
    for (int h7=0; h7<tilesize; h7++)
    //t3(h3,h2,h1,p4,p6,p5)-=t2(h7,p4,h1,h2)*v2(h7,h3,p6,p5);
    t3[h3+tilesize*(h2+tilesize*(h1+tilesize*(p4+tilesize*(p6+tilesize*p5))))] -= t2[h7+tilesize*(p4+tilesize*(h1+tilesize*h2))] * v2[h7+tilesize*(h3+tilesize*(p6+tilesize*p5))];
}

void cuda_sd_t_d2_8(int tilesize, double * restrict t3, const double * restrict t2, const double * restrict v2)
{
    for (int h7=0; h7<tilesize; h7++)
    //t3(h2,h1,h3,p4,p6,p5)-=t2(h7,p4,h1,h2)*v2(h7,h3,p6,p5);
    t3[h2+tilesize*(h1+tilesize*(h3+tilesize*(p4+tilesize*(p6+tilesize*p5))))] -= t2[h7+tilesize*(p4+tilesize*(h1+tilesize*h2))] * v2[h7+tilesize*(h3+tilesize*(p6+tilesize*p5))];
}

void cuda_sd_t_d2_9(int tilesize, double * restrict t3, const double * restrict t2, const double * restrict v2)
{
    for (int h7=0; h7<tilesize; h7++)
    //t3(h2,h3,h1,p4,p6,p5)+=t2(h7,p4,h1,h2)*v2(h7,h3,p6,p5);
    t3[h2+tilesize*(h3+tilesize*(h1+tilesize*(p4+tilesize*(p6+tilesize*p5))))] += t2[h7+tilesize*(p4+tilesize*(h1+tilesize*h2))] * v2[h7+tilesize*(h3+tilesize*(p6+tilesize*p5))];
}


