      subroutine new_sort_6(u,s,a,b,c,d,e,f,i,j,k,l,m,n,factor)
      implicit none
      integer a,b,c,d,e,f
      integer i,j,k,l,m,n
      double precision s(a*b*c*d*e*f)
      double precision u(a*b*c*d*e*f)
      double precision factor
      integer id(6),jd(6)
      integer ia,ib
      integer j1,j2,j3,j4,j5,j6
      integer jdm,jdl,jdk,jdj
      integer ia12345,ib12345
      ia = 0
      jd(1) = a
      jd(2) = b
      jd(3) = c
      jd(4) = d
      jd(5) = e
      jd(6) = f
      jdm=jd(m)
      jdl=jd(l)
      jdk=jd(k)
      jdj=jd(j)
      if (n.eq.6) then
      do j1 = 1,a
       do j2 = 1,b
        do j3 = 1,c
         do j4 = 1,d
          do j5 = 1,e
           id(1) = j1
           id(2) = j2
           id(3) = j3
           id(4) = j4
           id(5) = j5
           !id(6) = j6 ! 123456 are only used once and we know n=6, hence ijklm must not be 6
           ia12345 = f*(j5-1+e*(j4-1+d*(j3-1+c*(j2-1+b*(j1-1)))))
           ib12345 = f*(id(m)-1+jdm*(id(l)-1+jdl*(id(k)-1+jdk
     &                *(id(j)-1+jdj*(id(i)-1)))))
           do j6 = 1,f
            ia = j6+ia12345
            ib = j6+ib12345
            s(ib) = u(ia) * factor
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      else if (n.eq.5) then
      do j1 = 1,a
       do j2 = 1,b
        do j3 = 1,c
         do j4 = 1,d
          do j6 = 1,f
           id(1) = j1
           id(2) = j2
           id(3) = j3
           id(4) = j4
           !id(5) = j5
           id(6) = j6
           do j5 = 1,e
            ia = j6+f*(j5-1+e*(j4-1+d*(j3-1+c*(j2-1+b*(j1-1)))))
            ib = j5+e*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     1         *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))
            s(ib) = u(ia) * factor
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      else if (n.eq.4) then
      do j1 = 1,a
       do j2 = 1,b
        do j3 = 1,c
         do j5 = 1,e
          do j6 = 1,f
           id(1) = j1
           id(2) = j2
           id(3) = j3
           !id(4) = j4
           id(5) = j5
           id(6) = j6
           do j4 = 1,d
            ia = j6+f*(j5-1+e*(j4-1+d*(j3-1+c*(j2-1+b*(j1-1)))))
            ib = j4+d*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     1         *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))
            s(ib) = u(ia) * factor
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      else if (n.eq.3) then
      do j1 = 1,a
       do j2 = 1,b
        do j4 = 1,d
         do j5 = 1,e
          do j6 = 1,f
           id(1) = j1
           id(2) = j2
           !id(3) = j3
           id(4) = j4
           id(5) = j5
           id(6) = j6
           do j3 = 1,c
            ia = j6+f*(j5-1+e*(j4-1+d*(j3-1+c*(j2-1+b*(j1-1)))))
            ib = j3+c*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     1         *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))
            s(ib) = u(ia) * factor
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      else if (n.eq.2) then
      do j1 = 1,a
       do j3 = 1,c
        do j4 = 1,d
         do j5 = 1,e
          do j6 = 1,f
           id(1) = j1
           !id(2) = j2
           id(3) = j3
           id(4) = j4
           id(5) = j5
           id(6) = j6
           do j2 = 1,b
            ia = j6+f*(j5-1+e*(j4-1+d*(j3-1+c*(j2-1+b*(j1-1)))))
            ib = j2+b*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     1         *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))
            s(ib) = u(ia) * factor
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      else ! if (n.eq.1) then
      do j2 = 1,b
       do j3 = 1,c
        do j4 = 1,d
         do j5 = 1,e
          do j6 = 1,f
           !id(1) = j1
           id(2) = j2
           id(3) = j3
           id(4) = j4
           id(5) = j5
           id(6) = j6
           do j1 = 1,a
            ia = j6+f*(j5-1+e*(j4-1+d*(j3-1+c*(j2-1+b*(j1-1)))))
            ib = j1+a*(id(m)-1+jd(m)*(id(l)-1+jd(l)
     1         *(id(k)-1+jd(k)*(id(j)-1+jd(j)*(id(i)-1)))))
            s(ib) = u(ia) * factor
           enddo
          enddo
         enddo
        enddo
       enddo
      enddo
      endif
      return
      end
