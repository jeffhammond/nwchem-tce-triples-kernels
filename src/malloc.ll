#@ job_type = parallel
#@ job_name = test_malloc
#@ class = short
#@ error = $(job_name).$(jobid).err
#@ output = $(job_name).$(jobid).out
#@ network.MPI = sn_all,shared,US
#@ node = 1
#@ total_tasks = 1
#@ queue
#@ resources = ConsumableMemory(200gb)

#####################################################################################

mpiexec /gpfs/home/jhammond/NWCHEM/kernels/src/test_malloc.x

#####################################################################################
