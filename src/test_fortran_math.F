#define M 400
#define N 300
#define K 500
      program math
      use omp_lib
      implicit none
      double precision t0, t1
      double precision c(M,N)
      double precision a(M,K)
      double precision b(K,N)
      double precision z
      double precision x(M*N)
      double precision y(M*N)
      c = 0
      a = 1
      b = 1
      print*,'MATMUL'
      t0 = omp_get_wtime()
      c = matmul(a,b)
      t1 = omp_get_wtime()
      print*,'time = ',t1-t0,'seconds'
      print*,'perf = ',1.e-9*M*N*K/(t1-t0),'GF/s'
      x = 1
      y = 1
      print*,'DOT_PRODUCT'
      t0 = omp_get_wtime()
      z = dot_product(x,y)
      t1 = omp_get_wtime()
      print*,'time = ',t1-t0,'seconds'
      print*,'perf = ',1.e-9*M*N/(t1-t0),'GF/s'
! this is required to keep compiler from optimizing away z
      print*,'<x|y> = ',z
      end program
