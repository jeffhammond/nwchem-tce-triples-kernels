ACTIVE   = -DDO_S1 -DDO_D1 -DDO_D2 #-DDO_C_KERNELS

ifeq ($(TARGET),CLANG)
    CC       = clang
    FC       = gfortran
    OPT      = -O3 -march=native -mno-avx
    CFLAGS   = $(OPT) -std=c99 $(ACTIVE)
    FFLAGS   = $(OPT)
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = clang -L/usr/local/Cellar/gfortran/4.8.2/gfortran/lib
    LDFLAGS  = $(CFLAGS)
    LIBS     = -framework Accelerate
endif

ifeq ($(TARGET),MAC)
    CC       = gcc
    FC       = gfortran
    OPT      = -O3 -fopenmp -march=native -mno-avx
    CFLAGS   = $(OPT) -std=c99 $(ACTIVE)
    FFLAGS   = $(OPT)
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = clang -L/usr/local/Cellar/gfortran/4.8.2/gfortran/lib
    LDFLAGS  = $(CFLAGS)
    LIBS     = -framework Accelerate
endif

ifeq ($(TARGET),INTEL)
    # INTEL WORKSTATION (protos.mcs.anl.gov)
    CC       = icc
    FC       = ifort
    OPT      = -O3 -openmp -fno-alias -mavx -multiple-processes=8
    ASM      = -S -fsource-asm -fcode-asm
    REPORT   = -guide -parallel
    REPORT   = -vec-report2 -opt-report2
    #TARGET_FLAGS = -mmic
    CFLAGS   = $(OPT) -std=c99 $(TARGET_FLAGS) $(ACTIVE) $(REPORT)
    FFLAGS   = $(OPT) $(TARGET_FLAGS) $(REPORT) $(GUIDE)
    CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
    LD       = $(CC)
    LDFLAGS  = $(CFLAGS)
    LIBS     = -mkl=parallel
endif

TESTS   := test_ccsd_t.x
OBJECTS := ccsd_t_kernels_omp.o ccsd_t_kernels_ref.o ccsd_t_kernels_f2c.o blas_flops.o
HEADERS := ccsd_t_kernels_omp.h ccsd_t_kernels_ref.h ccsd_t_kernels_f2c.h safemalloc.h

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
