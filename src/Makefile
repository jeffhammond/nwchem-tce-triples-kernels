ACTIVE   = -DDO_FORTRAN 
ACTIVE  += -DDO_S1 #-DDO_D1 -DDO_D2

OMPFLAGS = #-fopenmp
OPTFLAGS = -g -O2
#OPTFLAGS = -O3

CC       = gcc
CFLAGS   = $(OPTFLAGS) $(OMPFLAGS) -std=c99 $(ACTIVE) -DFORTRAN_INTEGER_SIZE=8
         
FC       = gfortran
FFLAGS   = $(OPTFLAGS) $(OMPFLAGS) -fdefault-integer-8

LD       = $(CC)
LDFLAGS  = $(OPTFLAGS) $(CFLAGS) 
LIBS     = -lm 
# This is only required if one is using the Kernighan debugger in the Fortran code
#LIBS    += -lgfortran

TESTS    = test_ccsd_t.x 
HEADERS  = ccsd_t_kernels.h
OBJECTS  = ccsd_t_kernels_clean.o ccsd_t_kernels_omp.o ccsd_t_kernels_f2c.o

all: $(TESTS)

%.x: %.o $(OBJECTS)
	$(LD) $(LDFLAGS) $< $(OBJECTS) $(LIBS) -o $@

%.o: %.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.f Makefile
	$(FC) $(FFLAGS) -c $< -o $@

%.o: %.F Makefile
	$(FC) $(FFLAGS) $(ACTIVE) -c $< -o $@

clean:
	$(RM) $(RMFLAGS) *.o

realclean: clean
	$(RM) $(RMFLAGS) $(TESTS)
