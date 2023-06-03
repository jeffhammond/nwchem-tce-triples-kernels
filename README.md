nwchem-tce-triples-kernels
==========================

NWChem TCE CCSD(T) loop-driven kernels for performance optimization experiments

# Compiling

```
make TARGET=? -j8
```

Set TARGET to one of the following:

* CRAY-INTEL
* CRAY-GCC
* CRAY (Cray compilers)
* TUKEY-INTEL
* TUKEY-GCC
* KAYLA (GCC on ARM)
* BGQ (BGXLC)
* POWER7-AIX
* POWER7 (XLC)
* POWER7-GCC
* MAC-CLANG
* MAC (GCC)
* INTEL
* MIC (Intel)
* NVHPC
* ROCM

Or just define your own new TARGET using the existing ones as a template.

# Running

## CCSD(T) Kernels

```
Jeffs-MacBook-Pro:src jhammond$ OMP_NUM_THREADS=8 ./test_ccsd_t.x 16
testing NWChem CCSD(T) kernels on 8 threads with tilesize 16
MEMCPY gigabytes/s of your processor is 5.540682
DAXPY GF/s of your processor is 1.307957
DGER  GF/s of your processor is 2.109818
DGEMM (k=t) GF/s of your processor is 20.871256
DGEMM (k=t^2) GF/s of your processor is 43.129097
randomized initialization took 0.001193 s

STARTING FORTRAN OPENMP KERNELS
0: sd_t_s1_1 time = 0.045883 s GF/s = 0.731305
0: sd_t_s1_2 time = 0.016226 s GF/s = 2.067936
0: sd_t_s1_3 time = 0.015528 s GF/s = 2.160904
0: sd_t_s1_4 time = 0.018180 s GF/s = 1.845689
0: sd_t_s1_5 time = 0.017175 s GF/s = 1.953683
0: sd_t_s1_6 time = 0.015956 s GF/s = 2.102945
0: sd_t_s1_7 time = 0.016046 s GF/s = 2.091134
0: sd_t_s1_8 time = 0.017487 s GF/s = 1.918816
0: sd_t_s1_9 time = 0.016471 s GF/s = 2.037194
...
```

## Other Tests

Just read the first few lines of ``main()`` to see what arguments,
if any, these programs take.  The Fortran tests have hard-coded
dimensions that must be edited by hand prior to compilation.
