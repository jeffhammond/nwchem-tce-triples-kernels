#define T 12
      program test_tce_sort6
      use omp_lib
      implicit none
      double precision f
      double precision u(T,T,T,T,T,T)
      double precision s(T,T,T,T,T,T)
      double precision t0, t1
      double precision x
      integer d
      integer i,j,k,l,m,n
      integer num
      integer seed1,seed2
      double precision tmin,tmax,tavg
      double precision ddot
      external ddot
      seed1 = 1
      seed2 = 2
      do i = 1,T
      do j = 1,T
      do k = 1,T
      do l = 1,T
      do m = 1,T
      do n = 1,T
        u(n,m,l,k,j,i) = rand(seed1)
        s(n,m,l,k,j,i) = rand(seed2)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      num = 0
      tmin = 999999999.9
      tmax = -999999999.9
      write(6,*) '(i,j,k,l,m,n),time'
! This is not particularly efficient but other methods
! are harder to implement in Fortran 77.
      do i = 1,6
      do j = 1,6
      do k = 1,6
      do l = 1,6
      do m = 1,6
      do n = 1,6
      if (((((i.ne.j).and.(i.ne.k)).and.((i.ne.l).and.(i.ne.m))) .and.
     &     (((i.ne.n).and.(j.ne.k)).and.((j.ne.l).and.(j.ne.m)))).and.
     &    ((((j.ne.n).and.(k.ne.l)).and.((k.ne.m).and.(k.ne.n))) .and.
     &     (((l.ne.m).and.(l.ne.n)).and.((m.ne.n)            )))) then
        num = num+1
        d = T
        f = 1.0
        t0 = omp_get_wtime()
        call tce_sort_6(u,s,d,d,d,d,d,d,i,j,k,l,m,n,f)
        t1 = omp_get_wtime()
        x  = ddot(d*d*d*d*d*d,u,1,s,1)
        write(6,2) i,j,k,l,m,n,t1-t0,x
        tavg = tavg + (t1-t0)
        tmin = min(tmin,(t1-t0))
        tmax = max(tmax,(t1-t0))
      endif
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      tavg = tavg/num
      write(6,1) tmin,tmax,tavg
   1  format('min = ',f10.5,' max = ',f10.5,' avg = ',f10.5)
   2  format(6i2,' time = ',f10.5,' (s) junk = ',e10.5)
   3  format(6a2,10x,10x,10x,10x)
      end program
