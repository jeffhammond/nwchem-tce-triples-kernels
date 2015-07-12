      subroutine new_sort_2(u,s,a,b,i,j,f)
      implicit none
      integer a,b
      integer i,j
      integer ia,ib,j1,j2
      double precision s(a*b)
      double precision u(a*b)
      double precision f
      ia = 0
      if (i.eq.2) then ! transpose
       if (a.eq.b) then ! square
        call transpose2d(u,s,a,f)
       else ! rectangular
        do j1 = 1,a
         do j2 = 1,b
          ia = j2+b*(j1-1)
          ib = j1+a*(j2-1)
          s(ib) = u(ia) * f
         enddo
        enddo
       endif
      else ! i.eq.1 copy
       do ia = 1,a*b
         s(ia) = u(ia) * f
       enddo
      endif
      return
      end

      subroutine new_sortacc_2(u,s,a,b,i,j,f)
      implicit none
      integer a,b
      integer i,j
      integer ia,ib,j1,j2
      double precision s(a*b)
      double precision u(a*b)
      double precision f
      ia = 0
      if (i.eq.2) then ! transpose
       do j1 = 1,a
        do j2 = 1,b
         ia = j2+b*(j1-1)
         ib = j1+a*(j2-1)
         s(ib) = s(ib) + u(ia) * f
        enddo
       enddo
      else ! i.eq.1 copy
       do ia = 1,a*b
         s(ia) = s(ia) + u(ia) * f
       enddo
      endif
      return
      end

      subroutine transpose2d(u,s,d,f)
      implicit none
      integer i,j,d
      double precision s(d,d)
      double precision u(d,d)
      double precision f
      do i = 1,d
       do j = 1,d
        s(i,j) = u(j,i) * f
       enddo
      enddo
      return
      end
