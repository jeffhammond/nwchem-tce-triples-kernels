#@ job_type = parallel
#@ job_name = test_ccsd_t
#@ class = testing
#@ error = $(job_name).$(jobid).err
#@ output = $(job_name).$(jobid).out
#@ network.MPI = sn_all,shared,US
#@ node = 1
#@ total_tasks = 1
#@ environment = OMP_NUM_THREADS=64;OMP_STACKSIZE=1M
#@ queue
#@ resources = ConsumableMemory(220gb)

#####################################################################################

#mpiexec /gpfs/home/jhammond/NWCHEM/kernels/src/test_ccsd_t.x 12
#mpiexec /gpfs/home/jhammond/NWCHEM/kernels/src/test_ccsd_t.x 13
#mpiexec /gpfs/home/jhammond/NWCHEM/kernels/src/test_ccsd_t.x 14
mpiexec /gpfs/home/jhammond/NWCHEM/kernels/src/test_ccsd_t.x 15
mpiexec /gpfs/home/jhammond/NWCHEM/kernels/src/test_ccsd_t.x 16
mpiexec /gpfs/home/jhammond/NWCHEM/kernels/src/test_ccsd_t.x 17
mpiexec /gpfs/home/jhammond/NWCHEM/kernels/src/test_ccsd_t.x 18
mpiexec /gpfs/home/jhammond/NWCHEM/kernels/src/test_ccsd_t.x 19
mpiexec /gpfs/home/jhammond/NWCHEM/kernels/src/test_ccsd_t.x 20

#####################################################################################
