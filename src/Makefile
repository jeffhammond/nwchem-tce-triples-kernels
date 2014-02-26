#TARGET_FLAGS = -mmic

OPT = -O2 -fopenmp 

CC       = gcc
#CC       = icc
ACTIVE   = -DDO_S1 -DDO_D1 -DDO_D2
#ACTIVE   = -DDO_D1
CFLAGS   = $(OPT) -std=c99 $(TARGET_FLAGS) $(REPORT) $(ACTIVE)
#CFLAGS   = -O2 -openmp -std=c99 $(TARGET_FLAGS) $(REPORT) $(ACTIVE)

CFLAGS += -DFORTRAN_INTEGER_SIZE=4

FC       = gfortran
#FC       = ifort
FOPT     = $(OPT)
FFLAGS   = $(FOPT) $(TARGET_FLAGS) $(REPORT) $(GUIDE)

LD       = $(CC)
LDFLAGS  = $(COPT) $(CFLAGS)
LIBS     = -framework Accelerate
#LIBS	 = -mkl

TESTS := test_ccsd_t.x
OBJECTS := ccsd_t_kernels_omp.o ccsd_t_kernels_clean.o ccsd_t_kernels_f2c.o safemalloc.o test_dgemm.o
HEADERS := ccsd_t_kernels.h safemalloc.h

all: $(TESTS)

test_dgemm.x: test_dgemm.o safemalloc.o
	$(LD) $(LDFLAGS) $< safemalloc.o $(LIBS) -o $@

%.x: %.o $(OBJECTS)
	$(LD) $(LDFLAGS) $< $(OBJECTS) $(LIBS) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.f
	$(FC) $(FFLAGS) -c $< -o $@

%.o: %.F
	$(FC) $(FFLAGS) -c $< -o $@

clean:
	$(RM) $(RMFLAGS) *.o

realclean: clean
	$(RM) $(RMFLAGS) $(TESTS)
