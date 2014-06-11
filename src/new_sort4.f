      subroutine new_sort_4(u,s,a,b,c,d,i,j,k,l,f)
      implicit none
      integer a,b,c,d
      integer i,j,k,l
      integer id(4),jd(4),ia,ib,j1,j2,j3,j4
      double precision s(a*b*c*d)
      double precision u(a*b*c*d)
      double precision factor
      jd(1) = a
      jd(2) = b
      jd(3) = c
      jd(4) = d
      if (l.eq.4) then
      do j1 = 1,a
       do j2 = 1,b
        do j3 = 1,c
         do j4 = 1,d
          id(1) = j1
          id(2) = j2
          id(3) = j3
          !id(4) = j4 ! 1234 are only used once and we know l=4, hence ijk must not be 4
          ia = id(4)+d*(id(3)-1+c*(id(2)-1+b*(id(1)-1)))
          ib = id(4)+jd(4)*(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))
          s(ib) = u(ia) * factor
         enddo
        enddo
       enddo
      enddo
      else if (l.eq.3) then
      do j1 = 1,a
       do j2 = 1,b
        do j3 = 1,c
         do j4 = 1,d
          id(1) = j1
          id(2) = j2
          !id(3) = j3
          id(4) = j4
          ia = id(4)+d*(id(3)-1+c*(id(2)-1+b*(id(1)-1)))
          ib = id(3)+jd(3)*(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))
          s(ib) = u(ia) * factor
         enddo
        enddo
       enddo
      enddo
      else if (l.eq.2) then
      do j1 = 1,a
       do j3 = 1,c
        do j2 = 1,b
         do j4 = 1,d
          id(1) = j1
          !id(2) = j2
          id(3) = j3
          id(4) = j4
          ia = id(4)+d*(id(3)-1+c*(id(2)-1+b*(id(1)-1)))
          ib = id(2)+jd(2)*(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))
          s(ib) = u(ia) * factor
         enddo
        enddo
       enddo
      enddo
      else ! l.eq.1
      do j2 = 1,b
       do j3 = 1,c
        do j1 = 1,a
         do j4 = 1,d
          !id(1) = j1
          id(2) = j2
          id(3) = j3
          id(4) = j4
          ia = id(4)+d*(id(3)-1+c*(id(2)-1+b*(id(1)-1)))
          ib = id(1)+jd(1)*(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))
          s(ib) = u(ia) * factor
         enddo
        enddo
       enddo
      enddo
      endif
      return
      end
