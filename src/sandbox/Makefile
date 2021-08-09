FC      = nvfortran
FFLAGS  = -cpp
FFLAGS += -g
FFLAGS += -fast
FFLAGS += -acc
FFLAGS += -mp
FFLAGS += -stdpar=multicore
FFLAGS += -target=multicore
FFLAGS += -Minfo=accel,mp,vect
FFLAGS += -DOMP_COLLAPSE_LEVEL=3
FFLAGS += -DACC_COLLAPSE_LEVEL=6

all: test_stdpar_vs_openmp.x

test_stdpar_vs_openmp.x: test_stdpar_vs_openmp.F ccsd_t_kernels_acc.o ccsd_t_kernels_omp.o ccsd_t_kernels_ref.o ccsd_t_kernels_stdpar.o
	$(FC) -Mfree $(FFLAGS) $^ -o $@

%.o: %.f
	$(FC) $(FFLAGS) -c $< -o $@

%.o: %.F
	$(FC) $(FFLAGS) -c $< -o $@

clean:
	-rm -rf *.o
	-rm -rf *.x
	-rm -rf *.dSYM
