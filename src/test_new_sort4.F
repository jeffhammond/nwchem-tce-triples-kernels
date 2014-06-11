#define T 16
      program test_new_sort4
      use omp_lib
      implicit none
      double precision f
      double precision u(T,T,T,T)
      double precision s(T,T,T,T)
      double precision r(T,T,T,T)
      double precision t0, t1, dt1, dt2
      double precision x
      integer d
      integer i,j,k,l
      integer num
      integer seed1,seed2
      double precision tmin,tmax,tavg
      double precision rmin,rmax,ravg
      double precision z
      double precision ddot
      external ddot
      print*,'{tce,new}_sort_4 test with tilesize = ',T
      seed1 = 1
      seed2 = 2
      do i = 1,T
      do j = 1,T
      do k = 1,T
      do l = 1,T
#if defined(IBMXLF) || defined(INTEL_FORTRAN)
        u(l,k,j,i) = 1.0*i+mod(j,k)+l
        s(l,k,j,i) = 0.0
        r(l,k,j,i) = 0.0
#else
! GNU extension
        u(l,k,j,i) = rand(seed1)
        s(l,k,j,i) = 0.0
        r(l,k,j,i) = 0.0
#endif
      enddo
      enddo
      enddo
      enddo
      num = 0
      tmin = 999999999.9
      tmax = -999999999.9
      x = 0.0
      write(6,*) '(i,j,k,l),time,time,speedup'
! This is not particularly efficient but other methods
! are harder to implement in Fortran 77.
      do i = 1,4
      do j = 1,4
      do k = 1,4
      do l = 1,4
      if ((((i.ne.j).and.(i.ne.k)).and.(i.ne.l)).and.
     &    (((j.ne.k).and.(j.ne.l)).and.(k.ne.l))) then
        num = num+1
        d = T
        f = 1.0
        t0 = omp_get_wtime()
        call new_sort_4(u,s,d,d,d,d,i,j,k,l,f)
        t1 = omp_get_wtime()
        dt1 = t1-t0
        x  = x+ddot(d*d*d*d,u,1,s,1)
        tavg = tavg + (dt1)
        tmin = min(tmin,(dt1))
        tmax = max(tmax,(dt1))
! reference
        t0 = omp_get_wtime()
        call tce_sort_4(u,r,d,d,d,d,i,j,k,l,f)
        t1 = omp_get_wtime()
        dt2 = t1-t0
        x  = ddot(d*d*d*d,u,1,s,1)
        write(6,9) i,j,k,l,dt1,dt2,dt2/dt1
        ravg = tavg + dt2
        rmin = min(rmin,dt2)
        rmax = max(rmax,dt2)
        call diff4d(d,s,r,z)
        if (z.gt.0.0) then
            print*,'WRONG'
            exit
        endif
      endif
      enddo
      enddo
      enddo
      enddo
      tavg = tavg/num
      write(6,1) tmin,tmax,tavg
      print*,'junk = ',x
   1  format('min = ',f10.5,' max = ',f10.5,' avg = ',f10.5)
   3  format(4a2,10x,10x,10x,10x)
   9  format('NEW,TCE ',4i2,' times = ',2f10.5,' (s) ',f10.5)
      end program
      subroutine diff4d(n,x,y,z)
      implicit none
      integer i,j,k,l,n
      double precision x(n,n,n,n)
      double precision y(n,n,n,n)
      double precision z
      z = 0.0
      do i = 1,n
      do j = 1,n
      do k = 1,n
      do l = 1,n
        z=z+abs(x(l,k,j,i)-y(l,k,j,i))
      enddo
      enddo
      enddo
      enddo
      end subroutine
