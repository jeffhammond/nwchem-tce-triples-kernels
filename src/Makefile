ACTIVE   = -DDO_S1 -DDO_D1 -DDO_D2
ACTIVE  += -DDO_C_KERNELS
#ACTIVE  += -DDEBUG

TARGET := MAC

# Intel Fortran throws the "cannot simd" warning for 3 and 4...
OPT = -DOMP_COLLAPSE_LEVEL=1

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
    OPT     += -O3 -qhot -qtune=qp -qarch=qp -qsmp=omp -qsimd -qreport -qsource -qlist
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
    CC       = /usr/vac/bin/xlc_r
    FC       = /usr/bin/xlf_r
    OPT     += -O3 -qhot -qsmp=omp -qtune=pwr7 -qarch=pwr7 -qreport -qsource -qlist
    CFLAGS   = $(OPT) -qlanglvl=stdc99 $(ACTIVE)
    FFLAGS   = $(OPT) -qextname -WF,-DIBMXLF
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = $(FC)
    LDFLAGS  = $(FFLAGS)
    LIBS     = /usr/lib/libesslsmp.a
endif

ifeq ($(TARGET),POWER7)
# Vesta login
    CC       = xlc_r
    FC       = xlf_r
    OPT     += -O3 -qhot -qsmp=omp -qsimd -qreport -qsource -qlist
    CFLAGS   = $(OPT) -qlanglvl=stdc99 $(ACTIVE)
    FFLAGS   = $(OPT) -qextname -WF,-DIBMXLF
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

# test_tce_sort6.x requires enlarged stack because Fortran
FAT_STACK = -Wl,-stack_size -Wl,100000000

ifeq ($(TARGET),MAC-CLANG)
    CC       = clang
    FC       = gfortran
    OPT     += -O3 -march=native -mno-avx
    CFLAGS   = $(OPT) -std=c99 $(ACTIVE)
    FFLAGS   = $(OPT) -fopenmp
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = clang -L/usr/local/Cellar/gfortran/4.8.2/gfortran/lib
    LDFLAGS  = $(CFLAGS) $(FAT_STACK)
    LIBS     = -framework Accelerate -lgfortran
endif

ifeq ($(TARGET),MAC)
    CC       = gcc
    FC       = gfortran
    OPT     += -O3 -fopenmp -ftree-vectorize -ffp-contract=fast -march=native -mno-avx
    CFLAGS   = $(OPT) -std=c99 $(ACTIVE)
    FFLAGS   = $(OPT)
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = clang -L/usr/local/Cellar/gfortran/4.8.2/gfortran/lib
    LDFLAGS  = $(CFLAGS) $(FAT_STACK)
    LIBS     = -framework Accelerate -lgfortran
endif

ifeq ($(TARGET),INTEL)
    CC       = icc
    FC       = ifort
    #OPT     += -O3 -openmp -fno-alias -multiple-processes=8 -msse4.2
    OPT     += -O3 -openmp -fno-alias -multiple-processes=8 -mavx
    ASM      = -S -fsource-asm -fcode-asm
    CFLAGS   = $(OPT) -std=c99 $(ACTIVE)
    FFLAGS   = $(OPT) -cpp -DINTEL_FORTRAN
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = $(FC)
    LDFLAGS  = $(FFLAGS) -nofor-main
    LIBS     = -mkl=parallel
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

TESTS   := test_ccsd_t.x test_fortran_math.x test_dgemm_shapes.x test_tce_sort6.x test_new_sort6.x
OBJECTS :=                  ccsd_t_kernels_omp.o ccsd_t_kernels_ref.o ccsd_t_kernels_f2c.o ccsd_t_kernels_c99.o ccsd_t_kernels_blas.o blas_flops.o tce_sort6.o new_sort6.o
HEADERS := ccsd_t_kernels.h ccsd_t_kernels_omp.h ccsd_t_kernels_ref.h ccsd_t_kernels_f2c.h ccsd_t_kernels_c99.h ccsd_t_kernels_blas.h safemalloc.h pragma_vendor.h pragma_openmp.h fake_omp.h blas.h

all: $(TESTS)

%.x: %.o $(OBJECTS)
	$(LD) $(LDFLAGS) $< $(OBJECTS) $(LIBS) -o $@

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

realclean: clean
	$(RM) $(RMFLAGS) $(TESTS)
