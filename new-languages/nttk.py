#!/usr/bin/env python3
#
# Copyright (c) 2022, NVIDIA
#

import sys
if sys.version_info >= (3, 3):
    from time import process_time as timer
else:
    from timeit import default_timer as timer

import numpy as np

def diff6d(d1,d2,d3,d4,d5,d6,x,y):
    r = 0.0
    for i1,i2,i3,i4,i5,i6 in np.ndindex((d1,d2,d3,d4,d5,d6)):
        r += abs( x[i1,i2,i3,i4,i5,i6] - y[i1,i2,i3,i4,i5,i6] )
    return r

def nttk_sd_t_s1_1(d3,d2,d1,d6,d5,d4,triplesx,t1sub,v2sub):
    for h1,h2,h3,p4,p5,p6 in np.ndindex((d1,d2,d3,d4,d5,d6)):
        triplesx[h3,h2,h1,p6,p5,p4] += t1sub[p4,h1] * v2sub[h3,h2,p6,p5]

def nttk_sd_t_s1_2(d3,d2,d1,d6,d5,d4,triplesx,t1sub,v2sub):
    for h1,h2,h3,p4,p5,p6 in np.ndindex((d1,d2,d3,d4,d5,d6)):
        triplesx[h3,h1,h2,p6,p5,p4] -= t1sub[p4,h1] * v2sub[h3,h2,p6,p5]

def nttk_sd_t_s1_3(d3,d2,d1,d6,d5,d4,triplesx,t1sub,v2sub):
    for h1,h2,h3,p4,p5,p6 in np.ndindex((d1,d2,d3,d4,d5,d6)):
        triplesx[h1,h3,h2,p6,p5,p4] += t1sub[p4,h1] * v2sub[h3,h2,p6,p5]

def nttk_sd_t_s1_4(d3,d2,d1,d6,d5,d4,triplesx,t1sub,v2sub):
    for h1,h2,h3,p4,p5,p6 in np.ndindex((d1,d2,d3,d4,d5,d6)):
        triplesx[h3,h2,h1,p6,p4,p5] -=  t1sub[p4,h1] * v2sub[h3,h2,p6,p5]

def nttk_sd_t_s1_5(d3,d2,d1,d6,d5,d4,triplesx,t1sub,v2sub):
    for h1,h2,h3,p4,p5,p6 in np.ndindex((d1,d2,d3,d4,d5,d6)):
        triplesx[h3,h1,h2,p6,p4,p5] += t1sub[p4,h1] * v2sub[h3,h2,p6,p5]

def nttk_sd_t_s1_6(d3,d2,d1,d6,d5,d4,triplesx,t1sub,v2sub):
    for h1,h2,h3,p4,p5,p6 in np.ndindex((d1,d2,d3,d4,d5,d6)):
        triplesx[h1,h3,h2,p6,p4,p5] -=  t1sub[p4,h1] * v2sub[h3,h2,p6,p5]

def nttk_sd_t_s1_7(d3,d2,d1,d6,d5,d4,triplesx,t1sub,v2sub):
    for h1,h2,h3,p4,p5,p6 in np.ndindex((d1,d2,d3,d4,d5,d6)):
        triplesx[h3,h2,h1,p4,p6,p5] += t1sub[p4,h1] * v2sub[h3,h2,p6,p5]

def nttk_sd_t_s1_8(d3,d2,d1,d6,d5,d4,triplesx,t1sub,v2sub):
    for h1,h2,h3,p4,p5,p6 in np.ndindex((d1,d2,d3,d4,d5,d6)):
        triplesx[h3,h1,h2,p4,p6,p5] -=  t1sub[p4,h1] * v2sub[h3,h2,p6,p5]

def nttk_sd_t_s1_9(d3,d2,d1,d6,d5,d4,triplesx,t1sub,v2sub):
    for h1,h2,h3,p4,p5,p6 in np.ndindex((d1,d2,d3,d4,d5,d6)):
        triplesx[h1,h3,h2,p4,p6,p5] += t1sub[p4,h1] * v2sub[h3,h2,p6,p5]

def nttk_sd_t_d1_1(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
    for h1,h2,h3,p4,p5,p6,h7 in np.ndindex((d1,d2,d3,d4,d5,d6,d7)):
         triplesx[h3,h2,h1,p6,p5,p4] -= t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]

def nttk_sd_t_d1_2(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
    for h1,h2,h3,p4,p5,p6,h7 in np.ndindex((d1,d2,d3,d4,d5,d6,d7)):
         triplesx[h3,h1,h2,p6,p5,p4] += t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]

def nttk_sd_t_d1_3(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
    for h1,h2,h3,p4,p5,p6,h7 in np.ndindex((d1,d2,d3,d4,d5,d6,d7)):
         triplesx[h1,h3,h2,p6,p5,p4] -= t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]

def nttk_sd_t_d1_4(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
    for h1,h2,h3,p4,p5,p6,h7 in np.ndindex((d1,d2,d3,d4,d5,d6,d7)):
         triplesx[h3,h2,h1,p5,p4,p6] -= t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]

def nttk_sd_t_d1_5(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
    for h1,h2,h3,p4,p5,p6,h7 in np.ndindex((d1,d2,d3,d4,d5,d6,d7)):
         triplesx[h3,h1,h2,p5,p4,p6] += t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]

def nttk_sd_t_d1_6(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
    for h1,h2,h3,p4,p5,p6,h7 in np.ndindex((d1,d2,d3,d4,d5,d6,d7)):
         triplesx[h1,h3,h2,p5,p4,p6] -= t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]

def nttk_sd_t_d1_7(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
    for h1,h2,h3,p4,p5,p6,h7 in np.ndindex((d1,d2,d3,d4,d5,d6,d7)):
         triplesx[h3,h2,h1,p5,p6,p4] += t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]

def nttk_sd_t_d1_8(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
    for h1,h2,h3,p4,p5,p6,h7 in np.ndindex((d1,d2,d3,d4,d5,d6,d7)):
         triplesx[h3,h1,h2,p5,p6,p4] -= t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]


def nttk_sd_t_d1_9(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
    for h1,h2,h3,p4,p5,p6,h7 in np.ndindex((d1,d2,d3,d4,d5,d6,d7)):
         triplesx[h1,h3,h2,p5,p6,p4] += t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]

def nttk_sd_t_d2_1(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
    for h1,h2,h3,p4,p5,p6,p7 in np.ndindex((d1,d2,d3,d4,d5,d6,d7)):
         triplesx[h3,h2,h1,p6,p5,p4] -= t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]

def nttk_sd_t_d2_2(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
    for h1,h2,h3,p4,p5,p6,p7 in np.ndindex((d1,d2,d3,d4,d5,d6,d7)):
         triplesx[h2,h1,h3,p6,p5,p4] -= t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]

def nttk_sd_t_d2_3(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
    for h1,h2,h3,p4,p5,p6,p7 in np.ndindex((d1,d2,d3,d4,d5,d6,d7)):
         triplesx[h2,h3,h1,p6,p5,p4] += t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]

def nttk_sd_t_d2_4(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
    for h1,h2,h3,p4,p5,p6,p7 in np.ndindex((d1,d2,d3,d4,d5,d6,d7)):
         triplesx[h3,h2,h1,p6,p4,p5] += t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]

def nttk_sd_t_d2_5(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
    for h1,h2,h3,p4,p5,p6,p7 in np.ndindex((d1,d2,d3,d4,d5,d6,d7)):
         triplesx[h2,h1,h3,p6,p4,p5] += t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]

def nttk_sd_t_d2_6(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
    for h1,h2,h3,p4,p5,p6,p7 in np.ndindex((d1,d2,d3,d4,d5,d6,d7)):
         triplesx[h2,h3,h1,p6,p4,p5] -= t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]

def nttk_sd_t_d2_7(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
    for h1,h2,h3,p4,p5,p6,p7 in np.ndindex((d1,d2,d3,d4,d5,d6,d7)):
         triplesx[h3,h2,h1,p4,p6,p5] -= t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]

def nttk_sd_t_d2_8(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
    for h1,h2,h3,p4,p5,p6,p7 in np.ndindex((d1,d2,d3,d4,d5,d6,d7)):
         triplesx[h2,h1,h3,p4,p6,p5] -= t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]

def nttk_sd_t_d2_9(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
    for h1,h2,h3,p4,p5,p6,p7 in np.ndindex((d1,d2,d3,d4,d5,d6,d7)):
         triplesx[h2,h3,h1,p4,p6,p5] += t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]

def tensor_sd_t_s1_1(d3,d2,d1,d6,d5,d4,triplesx,t1sub,v2sub):
    # triplesx[h3,h2,h1,p6,p5,p4] += t1sub[p4,h1] * v2sub[h3,h2,p6,p5]
    triplesx += np.einsum(t1sub,[4,1],v2sub,[3,2,6,5],[3,2,1,6,5,4])


def tensor_sd_t_s1_2(d3,d2,d1,d6,d5,d4,triplesx,t1sub,v2sub):
     triplesx[h3,h1,h2,p6,p5,p4] -= t1sub[p4,h1] * v2sub[h3,h2,p6,p5]


def tensor_sd_t_s1_3(d3,d2,d1,d6,d5,d4,triplesx,t1sub,v2sub):
     triplesx[h1,h3,h2,p6,p5,p4] += t1sub[p4,h1] * v2sub[h3,h2,p6,p5]


def tensor_sd_t_s1_4(d3,d2,d1,d6,d5,d4,triplesx,t1sub,v2sub):
     triplesx[h3,h2,h1,p6,p4,p5] -=  t1sub[p4,h1] * v2sub[h3,h2,p6,p5]


def tensor_sd_t_s1_5(d3,d2,d1,d6,d5,d4,triplesx,t1sub,v2sub):
     triplesx[h3,h1,h2,p6,p4,p5] += t1sub[p4,h1] * v2sub[h3,h2,p6,p5]


def tensor_sd_t_s1_6(d3,d2,d1,d6,d5,d4,triplesx,t1sub,v2sub):
     triplesx[h1,h3,h2,p6,p4,p5] -=  t1sub[p4,h1] * v2sub[h3,h2,p6,p5]


def tensor_sd_t_s1_7(d3,d2,d1,d6,d5,d4,triplesx,t1sub,v2sub):
     triplesx[h3,h2,h1,p4,p6,p5] += t1sub[p4,h1] * v2sub[h3,h2,p6,p5]


def tensor_sd_t_s1_8(d3,d2,d1,d6,d5,d4,triplesx,t1sub,v2sub):
     triplesx[h3,h1,h2,p4,p6,p5] -=  t1sub[p4,h1] * v2sub[h3,h2,p6,p5]


def tensor_sd_t_s1_9(d3,d2,d1,d6,d5,d4,triplesx,t1sub,v2sub):
     triplesx[h1,h3,h2,p4,p6,p5] += t1sub[p4,h1] * v2sub[h3,h2,p6,p5]


def tensor_sd_t_d1_1(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
     triplesx[h3,h2,h1,p6,p5,p4] -= t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]


def tensor_sd_t_d1_2(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
     triplesx[h3,h1,h2,p6,p5,p4] += t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]


def tensor_sd_t_d1_3(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
     triplesx[h1,h3,h2,p6,p5,p4] -= t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]


def tensor_sd_t_d1_4(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
     triplesx[h3,h2,h1,p5,p4,p6] -= t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]


def tensor_sd_t_d1_5(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
     triplesx[h3,h1,h2,p5,p4,p6] += t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]


def tensor_sd_t_d1_6(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
     triplesx[h1,h3,h2,p5,p4,p6] -= t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]


def tensor_sd_t_d1_7(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
     triplesx[h3,h2,h1,p5,p6,p4] += t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]


def tensor_sd_t_d1_8(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
     triplesx[h3,h1,h2,p5,p6,p4] -= t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]


def tensor_sd_t_d1_9(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
     triplesx[h1,h3,h2,p5,p6,p4] += t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]


def tensor_sd_t_d2_1(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
     triplesx[h3,h2,h1,p6,p5,p4] -= t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]


def tensor_sd_t_d2_2(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
     triplesx[h2,h1,h3,p6,p5,p4] -= t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]


def tensor_sd_t_d2_3(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
     triplesx[h2,h3,h1,p6,p5,p4] += t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]


def tensor_sd_t_d2_4(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
     triplesx[h3,h2,h1,p6,p4,p5] += t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]


def tensor_sd_t_d2_5(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
     triplesx[h2,h1,h3,p6,p4,p5] += t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]


def tensor_sd_t_d2_6(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
     triplesx[h2,h3,h1,p6,p4,p5] -= t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]


def tensor_sd_t_d2_7(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
     triplesx[h3,h2,h1,p4,p6,p5] -= t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]


def tensor_sd_t_d2_8(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
     triplesx[h2,h1,h3,p4,p6,p5] -= t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]


def tensor_sd_t_d2_9(d3,d2,d1,d6,d5,d4,d7,triplesx,t2sub,v2sub):
     triplesx[h2,h3,h1,p4,p6,p5] += t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]


def main():
    print("NTTK Julia")

    reps     =  3
    tilesize = 16
    kernel   = -1

    tile6 = tilesize**6
    tile7 = tilesize**7

    if len(sys.argv) > 1:
        tilesize = int(sys.argv[1])

    if len(sys.argv) > 2:
        kernel = int(sys.argv[1])

    print("testing NWChem CCSD(T) kernels with tilesize ", tilesize)

    tt0 = timer()
    t1  = np.random.rand(tilesize,tilesize)
    t2  = np.random.rand(tilesize,tilesize,tilesize,tilesize)
    v2  = np.random.rand(tilesize,tilesize,tilesize,tilesize)
    tt1 = timer()
    print("allocation and initialization time =",(tt1-tt0)*1e-9," seconds")


    # LOOPS
    print("STARTING LOOPS KERNELS");
    t3l = np.zeros((tilesize,tilesize,tilesize,tilesize,tilesize,tilesize),dtype=np.float64)
    for i in range(reps):
        totalflops = 0
        ttt0 = timer()
        if kernel<0 or kernel==1 :
            tt0 = timer()
            nttk_sd_t_s1_1(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t1, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_1", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6

        if kernel<0 or kernel==2 :
            tt0 = timer()
            nttk_sd_t_s1_2(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t1, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_2", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6

        if kernel<0 or kernel==3 :
            tt0 = timer()
            nttk_sd_t_s1_3(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t1, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_3", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6

        if kernel<0 or kernel==4 :
            tt0 = timer()
            nttk_sd_t_s1_4(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t1, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_4", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6

        if kernel<0 or kernel==5 :
            tt0 = timer()
            nttk_sd_t_s1_5(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t1, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_5", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6

        if kernel<0 or kernel==6 :
            tt0 = timer()
            nttk_sd_t_s1_6(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t1, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_6", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6

        if kernel<0 or kernel==7 :
            tt0 = timer()
            nttk_sd_t_s1_7(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t1, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_7", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6

        if kernel<0 or kernel==8 :
            tt0 = timer()
            nttk_sd_t_s1_8(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t1, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_8", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6

        if kernel<0 or kernel==9 :
            tt0 = timer()
            nttk_sd_t_s1_9(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t1, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_9", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6

        if kernel<0 or kernel==1 :
            tt0 = timer()
            nttk_sd_t_d1_1(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_1", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==2 :
            tt0 = timer()
            nttk_sd_t_d1_2(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_2", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==3 :
            tt0 = timer()
            nttk_sd_t_d1_3(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_3", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==4 :
            tt0 = timer()
            nttk_sd_t_d1_4(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_4", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==5 :
            tt0 = timer()
            nttk_sd_t_d1_5(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_5", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==6 :
            tt0 = timer()
            nttk_sd_t_d1_6(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_6", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==7 :
            tt0 = timer()
            nttk_sd_t_d1_7(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_7", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==8 :
            tt0 = timer()
            nttk_sd_t_d1_8(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_8", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==9 :
            tt0 = timer()
            nttk_sd_t_d1_9(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_9", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==1 :
            tt0 = timer()
            nttk_sd_t_d2_1(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_1", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==2 :
            tt0 = timer()
            nttk_sd_t_d2_2(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_2", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==3 :
            tt0 = timer()
            nttk_sd_t_d2_3(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_3", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==4 :
            tt0 = timer()
            nttk_sd_t_d2_4(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_4", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==5 :
            tt0 = timer()
            nttk_sd_t_d2_5(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_5", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==6 :
            tt0 = timer()
            nttk_sd_t_d2_6(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_6", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==7 :
            tt0 = timer()
            nttk_sd_t_d2_7(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_7", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==8 :
            tt0 = timer()
            nttk_sd_t_d2_8(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_8", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==9 :
            tt0 = timer()
            nttk_sd_t_d2_9(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_9", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        ttt1 = timer()
        dt = ttt1-ttt0
        print("%d: total time = %lf s GF/s = %lf\n",i,dt*1e-9,totalflops/dt)


    # TENSOR
    print("STARTING TENSOR KERNELS");
    t3t = np.zeros((tilesize,tilesize,tilesize,tilesize,tilesize,tilesize),dtype=np.float64)
    for i in range(reps):
        totalflops = 0
        ttt0 = timer()
        if kernel<0 or kernel==1 :
            tt0 = timer()
            tensor_sd_t_s1_1(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t1, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_1", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6

        if kernel<0 or kernel==2 :
            tt0 = timer()
            tensor_sd_t_s1_2(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t1, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_2", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6

        if kernel<0 or kernel==3 :
            tt0 = timer()
            tensor_sd_t_s1_3(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t1, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_3", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6

        if kernel<0 or kernel==4 :
            tt0 = timer()
            tensor_sd_t_s1_4(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t1, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_4", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6

        if kernel<0 or kernel==5 :
            tt0 = timer()
            tensor_sd_t_s1_5(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t1, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_5", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6

        if kernel<0 or kernel==6 :
            tt0 = timer()
            tensor_sd_t_s1_6(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t1, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_6", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6

        if kernel<0 or kernel==7 :
            tt0 = timer()
            tensor_sd_t_s1_7(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t1, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_7", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6

        if kernel<0 or kernel==8 :
            tt0 = timer()
            tensor_sd_t_s1_8(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t1, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_8", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6

        if kernel<0 or kernel==9 :
            tt0 = timer()
            tensor_sd_t_s1_9(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t1, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_9", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6

        if kernel<0 or kernel==1 :
            tt0 = timer()
            tensor_sd_t_d1_1(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_1", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==2 :
            tt0 = timer()
            tensor_sd_t_d1_2(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_2", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==3 :
            tt0 = timer()
            tensor_sd_t_d1_3(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_3", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==4 :
            tt0 = timer()
            tensor_sd_t_d1_4(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_4", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==5 :
            tt0 = timer()
            tensor_sd_t_d1_5(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_5", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==6 :
            tt0 = timer()
            tensor_sd_t_d1_6(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_6", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==7 :
            tt0 = timer()
            tensor_sd_t_d1_7(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_7", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==8 :
            tt0 = timer()
            tensor_sd_t_d1_8(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_8", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==9 :
            tt0 = timer()
            tensor_sd_t_d1_9(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_9", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==1 :
            tt0 = timer()
            tensor_sd_t_d2_1(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_1", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==2 :
            tt0 = timer()
            tensor_sd_t_d2_2(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_2", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==3 :
            tt0 = timer()
            tensor_sd_t_d2_3(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_3", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==4 :
            tt0 = timer()
            tensor_sd_t_d2_4(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_4", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==5 :
            tt0 = timer()
            tensor_sd_t_d2_5(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_5", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==6 :
            tt0 = timer()
            tensor_sd_t_d2_6(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_6", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==7 :
            tt0 = timer()
            tensor_sd_t_d2_7(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_7", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==8 :
            tt0 = timer()
            tensor_sd_t_d2_8(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_8", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        if kernel<0 or kernel==9 :
            tt0 = timer()
            tensor_sd_t_d2_9(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = timer()
            dt = tt1-tt0
            print("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_9", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7

        ttt1 = timer()
        dt = ttt1-ttt0
        print("%d: total time = %lf s GF/s = %lf\n",i,dt*1e-9,totalflops/dt)


    error = diff6d(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t3t)
    print("diff = ",error)

    print("END")


if __name__ == '__main__':
    main()
