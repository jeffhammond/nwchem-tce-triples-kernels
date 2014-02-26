#TARGET_FLAGS = -mmic 

#OPT      = -O2 -fopenmp
#CC       = gcc
#FC       = gfortran
#LIBS     = -framework Accelerate
OPT 	 = -O3 -openmp -fno-alias
ASM      = -S -fsource-asm -fcode-asm
REPORT   = -vec-report2 -opt-report2
CC       = icc
FC       = ifort
LIBS	 = -mkl=parallel

ACTIVE   = -DDO_S1 -DDO_D1 -DDO_D2 -DDO_C_KERNELS
CFLAGS   = $(OPT) -std=c99 $(TARGET_FLAGS) $(REPORT) $(ACTIVE)
#CFLAGS   = -O2 -openmp -std=c99 $(TARGET_FLAGS) $(REPORT) $(ACTIVE)

CFLAGS += -DFORTRAN_INTEGER_SIZE=4

FOPT     = $(OPT)
FFLAGS   = $(FOPT) $(TARGET_FLAGS) $(REPORT) $(GUIDE)

LD       = $(CC)
LDFLAGS  = $(COPT) $(CFLAGS)

TESTS := test_ccsd_t.x
OBJECTS := ccsd_t_kernels_omp.o ccsd_t_kernels_clean.o ccsd_t_kernels_f2c.o blas_flops.o
HEADERS := ccsd_t_kernels.h safemalloc.h

all: $(TESTS)

%.x: %.o $(OBJECTS)
	$(LD) $(LDFLAGS) $< $(OBJECTS) $(LIBS) -o $@

%.s: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(ASM) -c $< -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ | tee $<.report

%.s: %.f
	$(FC) $(FFLAGS) $(ASM) -c $< -o $@

%.o: %.f
	$(FC) $(FFLAGS) -c $< -o $@ | tee $<.report

%.o: %.F
	$(FC) $(FFLAGS) -c $< -o $@ | tee $<.report

clean:
	$(RM) $(RMFLAGS) *.o

realclean: clean
	$(RM) $(RMFLAGS) $(TESTS)
