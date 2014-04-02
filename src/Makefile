ACTIVE   = -DDO_S1 -DDO_D1 -DDO_D2
#ACTIVE  += -DDO_C_KERNELS
#ACTIVE  += -DDEBUG

TARGET := MAC

ifeq ($(TARGET),BW-CRAY)
    CC       = cc
    FC       = ftn
    OPT      = -O3 -h omp
    CFLAGS   = $(OPT) -g -h c99 $(ACTIVE)
    FFLAGS   = $(OPT) -e F -DCRAYFTN
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = $(FC)
    LDFLAGS  = $(FFLAGS)
    LIBS     = -lsci_cray
endif

ifeq ($(TARGET),TUKEY-INTEL)
    CC       = icc
    FC       = ifort
    OPT      = -O3 -openmp -msse4.2 -fno-alias -multiple-processes=8
    CFLAGS   = $(OPT) -std=c99 $(ACTIVE)
    FFLAGS   = $(OPT) -cpp -nofor-main
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = $(FC)
    LDFLAGS  = $(FFLAGS)
    LIBS     = /soft/libraries/acml/5.3.1/ifort64_mp/lib/libacml_mp.a
endif

ifeq ($(TARGET),TUKEY-GCC)
    CC       = gcc
    FC       = gfortran
    OPT      = -O3 -fopenmp -march=native -ftree-vectorize -ffp-contract=fast
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
    OPT      = -O3 -fopenmp -march=native -ftree-vectorize -ffp-contract=fast
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
    OPT      = -O3 -qhot -qtune=qp -qarch=qp -qsmp=omp -qsimd -qreport -qsource -qlist
    CFLAGS   = $(OPT) -qlanglvl=stdc99 $(ACTIVE)
    FFLAGS   = $(OPT) -qextname
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = $(FC)
    LDFLAGS  = $(FFLAGS)
    LIBS     =  /soft/libraries/essl/current/essl/5.1/lib64/libesslsmpbg.a
endif

ifeq ($(TARGET),POWER7)
    CC       = xlc_r
    FC       = xlf_r
    OPT      = -O3 -qhot -qsmp=omp -qsimd -qreport -qsource -qlist
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
    OPT      = -O3 -mtune=power7 -ftree-vectorize -fopenmp -mvsx -floop-interchange -ffp-contract=fast
    CFLAGS   = $(OPT) -std=c99 $(ACTIVE)
    FFLAGS   = $(OPT)
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = $(FC)
    LDFLAGS  = $(FFLAGS)
    # must build BLIS with 32b f77_int (not default)
    LIBS     = $(HOME)/BLIS/dowd/install/lib/libblis.a
endif

ifeq ($(TARGET),MAC-CLANG)
    CC       = clang
    FC       = gfortran
    OPT      = -O3 -march=native -mno-avx
    CFLAGS   = $(OPT) -std=c99 $(ACTIVE)
    FFLAGS   = $(OPT) -fopenmp
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = clang -L/usr/local/Cellar/gfortran/4.8.2/gfortran/lib
    LDFLAGS  = $(CFLAGS)
    LIBS     = -framework Accelerate
endif

ifeq ($(TARGET),MAC-PGI)
    CC       = pgcc
    FC       = pgf77
    OPT      = -O3
    CFLAGS   = $(OPT) $(ACTIVE) # -c99
    FFLAGS   = $(OPT)
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = $(CC)
    LDFLAGS  = $(CFLAGS)
    LIBS     = -framework Accelerate
endif

ifeq ($(TARGET),MAC)
    CC       = gcc
    FC       = gfortran
    OPT      = -O3 -fopenmp -march=native -mno-avx -ftree-vectorize -ffp-contract=fast
    CFLAGS   = $(OPT) -std=c99 $(ACTIVE)
    FFLAGS   = $(OPT)
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = clang -L/usr/local/Cellar/gfortran/4.8.2/gfortran/lib
    LDFLAGS  = $(CFLAGS)
    LIBS     = -framework Accelerate
endif

ifeq ($(TARGET),INTEL)
    CC       = icc
    FC       = ifort
    OPT      = -O3 -openmp -fno-alias -multiple-processes=8 -msse4.2
    #OPT      = -O3 -openmp -fno-alias -multiple-processes=8 -mavx
    ASM      = -S -fsource-asm -fcode-asm
    CFLAGS   = $(OPT) -std=c99 $(ACTIVE)
    FFLAGS   = $(OPT)
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = $(CC)
    LDFLAGS  = $(CFLAGS)
    LIBS     = -mkl=parallel
endif

ifeq ($(TARGET),MIC)
    CC       = icc
    FC       = ifort
    OPT      = -O2 -openmp -mmic -multiple-processes=8
    ASM      = -S -fsource-asm -fcode-asm
    CFLAGS   = $(OPT) -std=c99 $(ACTIVE)
    FFLAGS   = $(OPT)
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = $(CC)
    LDFLAGS  = $(CFLAGS)
    LIBS     = -mkl=parallel
endif

TESTS   := test_ccsd_t.x
OBJECTS := ccsd_t_kernels_omp.o ccsd_t_kernels_ref.o ccsd_t_kernels_f2c.o ccsd_t_kernels_c99.o blas_flops.o
HEADERS := ccsd_t_kernels_omp.h ccsd_t_kernels_ref.h ccsd_t_kernels_f2c.h ccsd_t_kernels_c99.h safemalloc.h pragmas.h

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
