#@ job_type = parallel
#@ job_name = test_tce_sort6
#@ class = testing
#@ error = $(job_name).$(jobid).err
#@ output = $(job_name).$(jobid).out
#@ network.MPI = sn_all,shared,US
#@ node = 1
#@ total_tasks = 1
#@ environment = OMP_NUM_THREADS=64;OMP_STACKSIZE=1M
#@ queue
#@ resources = ConsumableMemory(220000)

#####################################################################################

env
mpiexec /gpfs/home/jhammond/NWCHEM/kernels/src/test_tce_sort6.x 10
mpiexec /gpfs/home/jhammond/NWCHEM/kernels/src/test_tce_sort6.x 11
mpiexec /gpfs/home/jhammond/NWCHEM/kernels/src/test_tce_sort6.x 12
mpiexec /gpfs/home/jhammond/NWCHEM/kernels/src/test_tce_sort6.x 13
mpiexec /gpfs/home/jhammond/NWCHEM/kernels/src/test_tce_sort6.x 14
mpiexec /gpfs/home/jhammond/NWCHEM/kernels/src/test_tce_sort6.x 15
mpiexec /gpfs/home/jhammond/NWCHEM/kernels/src/test_tce_sort6.x 16

#####################################################################################
