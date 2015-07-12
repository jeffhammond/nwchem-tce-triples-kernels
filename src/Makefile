ACTIVE   =
ACTIVE  += -DDO_S1
ACTIVE  += -DDO_D1
ACTIVE  += -DDO_D2
ACTIVE  += -DDO_C_KERNELS
#ACTIVE  += -DDO_BLAS_KERNELS
#ACTIVE  += -DDEBUG

TARGET := INTEL

# Intel Fortran throws the "cannot simd" warning for 3 and 4...
OMP_COLLAPSE_LEVEL=3
OPT = -DOMP_COLLAPSE_LEVEL=$(OMP_COLLAPSE_LEVEL)

# test_tce_sort6.x requires enlarged stack because Fortran
FAT_STACK = -Wl,-stack_size -Wl,100000000

ifeq ($(TARGET),INTEL)
    CC       = icc
    FC       = ifort
    OPT     += -O3 -qopenmp -fno-alias -xHOST #-mavx
    OPT	    += -qopt-report
    ASM      = -S -fsource-asm -fcode-asm
    CFLAGS   = $(OPT) -std=c99 $(ACTIVE)
    FFLAGS   = $(OPT) -cpp -DINTEL_FORTRAN -heap-arrays 1000000
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = $(FC)
    LDFLAGS  = $(FFLAGS) -nofor-main
    LDFLAGS += #-Wl,-no_pie # debugging with IDB only
    LIBS     = -mkl=parallel
    #LIBS     = -mkl=sequential
endif

ifeq ($(TARGET),GCC)
    CC       = gcc
    FC       = gfortran
    OPT     += -O3 -fopenmp -march=native -ftree-vectorize -ffp-contract=fast
    CFLAGS   = $(OPT) -std=c99 $(ACTIVE)
    FFLAGS   = $(OPT) -cpp
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = $(FC)
    LDFLAGS  = $(FFLAGS)
    LIBS     = -L/usr/lib64/atlas/ -lptf77blas -latlas
endif

ifeq ($(TARGET),MAC-CLANG)
    CC       = clang
    FC       = gfortran
    OPT     += -O3 -march=native
    CFLAGS   = $(OPT) -std=c99 $(ACTIVE)
    FFLAGS   = $(OPT) -fopenmp
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = clang -L/usr/local/Cellar/gfortran/4.8.2/gfortran/lib
    LDFLAGS  = $(CFLAGS) $(FAT_STACK)
    LIBS     = -framework Accelerate -lgfortran
endif

ifeq ($(TARGET),MAC)
    CC       = gcc-4.8
    FC       = gfortran-4.8
    OPT     += -O2 -fopenmp #-ftree-vectorize -ffp-contract=fast -march=native -mno-avx
    CFLAGS   = $(OPT) -std=c99 $(ACTIVE)
    FFLAGS   = $(OPT)
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    #LD       = clang -L/usr/local/Cellar/gfortran/4.8.2/gfortran/lib
    #LDFLAGS  = $(CFLAGS) $(FAT_STACK)
    LD       = $(CC)
    LDFLAGS  = $(CFLAGS) $(FAT_STACK)
    LIBS     = -framework Accelerate -lgfortran
endif

ifeq ($(TARGET),MAC-INTEL)
    CC       = icc
    FC       = ifort
    OPT     += -O3 -qopenmp -fno-alias
    #OPT     += -g -O2 -fopenmp -fno-alias #-mavx
    ASM      = -S -fsource-asm -fcode-asm
    CFLAGS   = $(OPT) -std=c99 $(ACTIVE)
    FFLAGS   = $(OPT) -cpp -DINTEL_FORTRAN -heap-arrays
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = clang
    LDFLAGS  = -g -O2 -mavx $(FAT_STACK)
    #LD       = $(FC)
    #LDFLAGS  = $(FFLAGS) -nofor-main -static-intel
    #LDFLAGS += -Wl,-no_pie # debugging with IDB only
    #LIBS     = -mkl=parallel
endif

ifeq ($(TARGET),MIC)
    CC       = icc
    FC       = ifort
    OPT     += -O2 -openmp -mmic -multiple-processes=8
    ASM      = -S -fsource-asm -fcode-asm
    CFLAGS   = $(OPT) -std=c99 $(ACTIVE)
    FFLAGS   = $(OPT) -cpp -DINTEL_FORTRAN
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = $(FC)
    LDFLAGS  = $(FFLAGS) -nofor-main
    LIBS     = -mkl=parallel
endif

ifeq ($(TARGET),CRAY-INTEL)
    CC       = cc
    FC       = ftn
    OPT     += -O3 -openmp -fno-alias -multiple-processes=8 -mavx
    ASM      = -S -fsource-asm -fcode-asm
    CFLAGS   = $(OPT) -std=c99 $(ACTIVE)
    FFLAGS   = $(OPT) -cpp -DINTEL_FORTRAN
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = $(FC)
    LDFLAGS  = $(FFLAGS) -nofor-main
    LIBS     = -mkl=parallel
endif

ifeq ($(TARGET),CRAY-GCC)
    CC       = cc
    FC       = ftn
    OPT     += -O3 -fopenmp -march=native -ftree-vectorize -ffp-contract=fast
    CFLAGS   = $(OPT) -std=c99 $(ACTIVE)
    FFLAGS   = $(OPT) -cpp
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = $(FC)
    LDFLAGS  = $(FFLAGS)
    LIBS     = -lsci_gnu_48_mp
endif

ifeq ($(TARGET),CRAY)
    CC       = cc
    FC       = ftn
    OPT     += -O3 -h omp
    CFLAGS   = $(OPT) -h c99 $(ACTIVE)
    FFLAGS   = $(OPT) -e F -DCRAYFTN
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = $(FC)
    LDFLAGS  = $(FFLAGS)
    LIBS     = -lsci_cray_mp
endif

ifeq ($(TARGET),TUKEY-INTEL)
    CC       = icc
    FC       = ifort
    OPT     += -O3 -openmp -msse4.2 -fno-alias -multiple-processes=8
    CFLAGS   = $(OPT) -std=c99 $(ACTIVE)
    FFLAGS   = $(OPT) -cpp -DINTEL_FORTRAN
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = $(FC)
    LDFLAGS  = $(FFLAGS) -nofor-main
    LIBS     = /soft/libraries/acml/5.3.1/ifort64_mp/lib/libacml_mp.a
endif

ifeq ($(TARGET),TUKEY-GCC)
    CC       = gcc
    FC       = gfortran
    OPT     += -O3 -fopenmp -march=native -ftree-vectorize -ffp-contract=fast
    CFLAGS   = $(OPT) -std=c99 $(ACTIVE)
    FFLAGS   = $(OPT) -cpp
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = $(FC)
    LDFLAGS  = $(FFLAGS)
    LIBS     = /soft/libraries/acml/5.3.1/gfortran64_mp/lib/libacml_mp.a
endif

ifeq ($(TARGET),KAYLA)
    CC       = gcc
    FC       = gfortran
    OPT     += -O3 -fopenmp -march=native -ftree-vectorize -ffp-contract=fast
    CFLAGS   = $(OPT) -std=c99 $(ACTIVE)
    FFLAGS   = $(OPT)
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = $(FC)
    LDFLAGS  = $(FFLAGS)
    LIBS     = -L/usr/lib/atlas-base -lptf77blas -latlas
endif

ifeq ($(TARGET),BGQ)
    CC       = bgxlc_r
    FC       = bgxlf_r
    OPT     += -O3 -qhot -qtune=qp -qarch=qp -qsmp=omp -qsimd #-qreport -qsource -qlist -qsuppress=cmpmsg
    CFLAGS   = $(OPT) -qlanglvl=stdc99 $(ACTIVE)
    FFLAGS   = $(OPT) -qextname
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = $(FC)
    LDFLAGS  = $(FFLAGS)
    LIBS     = /soft/libraries/essl/current/essl/5.1/lib64/libesslsmpbg.a
    #CFLAGS  += -DBLAS_NO_UNDERSCORE
    #LIBS     = $(HOME)/BLIS/bgq/lib/libblis.a
endif

ifeq ($(TARGET),POWER7-AIX)
# Savba i.e. POWER775 AIX
    CC       = mpcc_r
    FC       = mpxlf_r
    OPT      = -WF,-DOMP_COLLAPSE_LEVEL=$(OMP_COLLAPSE_LEVEL)
    OPT     += -q64 -O3 -qhot -qsmp=omp -qtune=pwr7 -qarch=pwr7 -qstrict #-qreport -qsource -qlist #-qsuppress=cmpmsg
    CFLAGS   = $(OPT) -qlanglvl=stdc99 $(ACTIVE) -DOMP_COLLAPSE_LEVEL=$(OMP_COLLAPSE_LEVEL)
    FFLAGS   = $(OPT) -qextname -WF,-DIBMXLF -WF,-DOMP_COLLAPSE_LEVEL=$(OMP_COLLAPSE_LEVEL)
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = $(FC)
    LDFLAGS  = $(FFLAGS)
    LIBS     = /usr/lib/libesslsmp.a
endif

ifeq ($(TARGET),POWER7)
# Vesta login
    CC       = xlc_r
    FC       = xlf_r
    OPT      = -WF,-DOMP_COLLAPSE_LEVEL=$(OMP_COLLAPSE_LEVEL)
    OPT     += -O3 -qhot -qsmp=omp -qsimd -qreport -qsource -qlist -qsuppress=cmpmsg
    CFLAGS   = $(OPT) -qlanglvl=stdc99 $(ACTIVE) -DOMP_COLLAPSE_LEVEL=$(OMP_COLLAPSE_LEVEL)
    FFLAGS   = $(OPT) -qextname -WF,-DIBMXLF -WF,-DOMP_COLLAPSE_LEVEL=$(OMP_COLLAPSE_LEVEL)
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = $(FC)
    LDFLAGS  = $(FFLAGS)
    LIBS     = $(HOME)/BLIS/power7/lib/libblis.a
endif

ifeq ($(TARGET),POWER7-GCC)
    #GCC_PATH = $(HOME)/GCC/dowd/4.9-20140316/bin/
    GCC_PATH = $(HOME)/GCC/dowd/4.8.2/bin/
    #GCC_PATH = /usr/bin/
    CC       = $(GCC_PATH)gcc
    FC       = $(GCC_PATH)gfortran
    OPT     += -O3 -mtune=power7 -ftree-vectorize -fopenmp -mvsx -floop-interchange -ffp-contract=fast
    CFLAGS   = $(OPT) -std=c99 $(ACTIVE)
    FFLAGS   = $(OPT)
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = $(FC)
    LDFLAGS  = $(FFLAGS)
    # must build BLIS with 32b f77_int (not default)
    #LIBS     = $(HOME)/BLIS/dowd/install/lib/libblis.a
    LIBS     = -L/usr/lib64/atlas -lptf77blas -latlas
endif

TESTS   := test_ccsd_t.x test_new_sort6.x test_new_sort4.x test_new_sort2.x
EXTRATESTS := test_malloc.x test_fortran_math.x test_dgemm_shapes.x
CCOBJECTS := ccsd_t_kernels_omp.o ccsd_t_kernels_ref.o ccsd_t_kernels_1d.o ccsd_t_kernels_nd.o ccsd_t_kernels_blas.o
HEADERS := safemalloc.h pragma_vendor.h pragma_openmp.h fake_omp.h blas.h
CCHEADERS := ccsd_t_kernels.h ccsd_t_kernels_omp.h ccsd_t_kernels_ref.h ccsd_t_kernels_1d.h ccsd_t_kernels_nd.h ccsd_t_kernels_blas.h

all: $(TESTS)

test_ccsd_t.x: test_ccsd_t.o $(CCOBJECTS) blas_flops.o
	$(LD) $(LDFLAGS) $< $(CCOBJECTS) blas_flops.o $(LIBS) -o $@

test_new_sort2.x: test_new_sort2.o tce_sort2.o new_sort2.o
	$(LD) $(LDFLAGS) $< tce_sort2.o new_sort2.o $(LIBS) -o $@

test_new_sort4.x: test_new_sort4.o tce_sort4.o new_sort4.o
	$(LD) $(LDFLAGS) $< tce_sort4.o new_sort4.o $(LIBS) -o $@

test_new_sort6.x: test_new_sort6.o tce_sort6.o new_sort6.o
	$(LD) $(LDFLAGS) $< tce_sort6.o new_sort6.o $(LIBS) -o $@

test_dgemm_shapes.x: test_dgemm_shapes.o blas_flops.o
	$(LD) $(LDFLAGS) $< blas_flops.o $(LIBS) -o $@

test_malloc.x: test_malloc.o
	$(LD) $(LDFLAGS) $< $(LIBS) -o $@

test_fortran_math.x: test_fortran_math.o
	$(LD) $(LDFLAGS) $< $(LIBS) -o $@

#%.x: %.o
#	$(LD) $(LDFLAGS) $< $(OBJECTS) $(LIBS) -o $@

test_ccsd_t.o: test_ccsd_t.c $(HEADERS) $(CCHEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.f
	$(FC) $(FFLAGS) -c $< -o $@

%.o: %.F
	$(FC) $(FFLAGS) -c $< -o $@

%.s: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(ASM) -c $< -o $@

%.s: %.f
	$(FC) $(FFLAGS) $(ASM) -c $< -o $@

clean:
	$(RM) $(RMFLAGS) *.o
	$(RM) $(RMFLAGS) *.optrpt
	$(RM) $(RMFLAGS) $(TESTS)
	$(RM) $(RMFLAGS) $(EXTRATESTS)
	-rm -rf *.dSYM
