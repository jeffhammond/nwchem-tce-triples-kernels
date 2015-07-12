!
! On Mac, if T is any larger, one will observe segfaults and then SIGBUS
! (illegal instruction), the latter of which is confusing.
!
#define T 8
      program test_new_sort6
      use omp_lib
      implicit none
      double precision f
      double precision u(T,T,T,T,T,T)
      double precision s(T,T,T,T,T,T)
      double precision r(T,T,T,T,T,T)
      double precision t0, t1, dt1, dt2
      double precision x
      integer d
      integer i,j,k,l,m,n
      integer num
      integer seed1,seed2
      double precision tmin,tmax,tavg
      double precision rmin,rmax,ravg
      double precision z
      double precision ddot
      external ddot
      print*,'{tce,new}_sort_6 test with tilesize = ',T
      seed1 = 1
      seed2 = 2
      do i = 1,T
      do j = 1,T
      do k = 1,T
      do l = 1,T
      do m = 1,T
      do n = 1,T
#if defined(IBMXLF) || defined(INTEL_FORTRAN)
        u(n,m,l,k,j,i) = 1.0*i+mod(j,k)+l*m/n
        s(n,m,l,k,j,i) = 0.0
        r(n,m,l,k,j,i) = 0.0
#else
! GNU extension
        u(n,m,l,k,j,i) = rand(seed1)
        s(n,m,l,k,j,i) = 0.0
        r(n,m,l,k,j,i) = 0.0
#endif
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      num = 0
      tmin = 999999999.9
      tmax = -999999999.9
      x = 0.0
      write(6,*) '(i,j,k,l,m,n),time,time,speedup'
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
        call new_sort_6(u,s,d,d,d,d,d,d,i,j,k,l,m,n,f)
        t1 = omp_get_wtime()
        dt1 = t1-t0
        x  = x+ddot(d*d*d*d*d*d,u,1,s,1)
        tavg = tavg + (dt1)
        tmin = min(tmin,(dt1))
        tmax = max(tmax,(dt1))
! reference
        t0 = omp_get_wtime()
        call tce_sort_6(u,r,d,d,d,d,d,d,i,j,k,l,m,n,f)
        t1 = omp_get_wtime()
        dt2 = t1-t0
        x  = ddot(d*d*d*d*d*d,u,1,s,1)
        write(6,9) i,j,k,l,m,n,dt1,dt2,dt2/dt1
        ravg = tavg + dt2
        rmin = min(rmin,dt2)
        rmax = max(rmax,dt2)
        call diff6d(d,s,r,z)
        if (z.gt.0.0) then
            print*,'WRONG'
            exit
        endif
      endif
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      tavg = tavg/num
      write(6,1) tmin,tmax,tavg
      print*,'junk = ',x
   1  format('min = ',f10.5,' max = ',f10.5,' avg = ',f10.5)
   3  format(6a2,10x,10x,10x,10x)
   9  format('NEW,TCE ',6i2,' times = ',2f10.5,' (s) ',f10.5)
      end program
      subroutine diff6d(n,x,y,z)
      implicit none
      integer i,j,k,l,m,p,n
      double precision x(n,n,n,n,n,n)
      double precision y(n,n,n,n,n,n)
      double precision z
      z = 0.0
      do i = 1,n
      do j = 1,n
      do k = 1,n
      do l = 1,n
      do m = 1,n
      do p = 1,n
        z=z+abs(x(p,m,l,k,j,i)-y(p,m,l,k,j,i))
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      end subroutine
