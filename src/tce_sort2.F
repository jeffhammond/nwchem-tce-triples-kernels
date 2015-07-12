      subroutine tce_sort_2(u,s,a,b,i,j,f)
      implicit none
      integer a,b
      integer i,j
      integer id(2),jd(2),ia,ib,j1,j2
      double precision s(a*b)
      double precision u(a*b)
      double precision f
      ia = 0
      jd(1) = a
      jd(2) = b
      do j1 = 1,a
       id(1) = j1
       do j2 = 1,b
        id(2) = j2
        ia = ia + 1
!        ia = id(2)+jd(2)*(id(1)-1)
        ib = id(j)+jd(j)*(id(i)-1)
        s(ib) = u(ia) * f
       enddo
      enddo
      return
      end
