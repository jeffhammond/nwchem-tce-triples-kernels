#TARGET_FLAGS = -mmic 

#OPT      = -O2 -fopenmp
#CC       = gcc
#FC       = gfortran
#LIBS     = -framework Accelerate
OPT 	 = -O3 -openmp -fno-alias -mavx -multiple-processes=8
ASM      = -S -fsource-asm -fcode-asm
#REPORT   = -guide -parallel
#REPORT   = -vec-report2 -opt-report2
CC       = icc
FC       = ifort
LIBS	 = -mkl=parallel

LD       = $(CC)

ACTIVE   = -DDO_S1 -DDO_D1 -DDO_D2 #-DDO_C_KERNELS

CFLAGS   = $(OPT) -std=c99 $(TARGET_FLAGS) $(ACTIVE) $(REPORT)
FFLAGS   = $(OPT) $(TARGET_FLAGS) $(REPORT) $(GUIDE)
CFLAGS  += -DFORTRAN_INTEGER_SIZE=4
LDFLAGS  = $(CFLAGS)

TESTS   := test_ccsd_t.x
OBJECTS := ccsd_t_kernels_omp.o ccsd_t_kernels_clean.o ccsd_t_kernels_f2c.o blas_flops.o
HEADERS := ccsd_t_kernels.h safemalloc.h

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
