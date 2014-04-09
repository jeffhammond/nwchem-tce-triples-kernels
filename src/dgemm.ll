#@ job_type = parallel
#@ job_name = test_dgemm_shapes
#@ class = testing
#@ error = $(job_name).$(jobid).err
#@ output = $(job_name).$(jobid).out
#@ network.MPI = sn_all,shared,US
#@ node = 1
#@ total_tasks = 1
#@ environment = OMP_NUM_THREADS=64;OMP_STACKSIZE=1M
#@ queue
#@ resources = ConsumableMemory(200000)

#####################################################################################

env
mpiexec /gpfs/home/jhammond/NWCHEM/kernels/src/test_dgemm_shapes.x 4000 400 2000 400

#####################################################################################
