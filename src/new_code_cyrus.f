c
c These have been separated out from ccsd_t_singles_l.F and ccsd_t_doubles_l.F
c
      subroutine sd_t_s1_1(h3d,h2d,h1d,p6d,p5d,p4d,
     2               triplesx,t1sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d
      integer h3,h2,h1,p6,p5,p4
      double precision triplesx(h3d,h2d,h1d,p6d,p5d,p4d)
      double precision t1sub(p4d,h1d)
      double precision v2sub(h3d,h2d,p6d,p5d)
      do p4=1,p4d
      do p5=1,p5d
      do p6=1,p6d
      do h1=1,h1d
      do h2=1,h2d
      do h3=1,h3d
       triplesx(h3,h2,h1,p6,p5,p4)=triplesx(h3,h2,h1,p6,p5,p4)
     1   + t1sub(p4,h1)*v2sub(h3,h2,p6,p5)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      return
      end
c
      subroutine sd_t_s1_2(h3d,h2d,h1d,p6d,p5d,p4d,
     2               triplesx,t1sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d
      integer h3,h2,h1,p6,p5,p4
      double precision triplesx(h3d,h1d,h2d,p6d,p5d,p4d)
      double precision t1sub(p4d,h1d)
      double precision v2sub(h3d,h2d,p6d,p5d)
      do p4=1,p4d
      do p5=1,p5d
      do p6=1,p6d
      do h2=1,h2d
      do h1=1,h1d
      do h3=1,h3d
       triplesx(h3,h1,h2,p6,p5,p4)=triplesx(h3,h1,h2,p6,p5,p4)
     1   - t1sub(p4,h1)*v2sub(h3,h2,p6,p5)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      return
      end
c
      subroutine sd_t_s1_3(h3d,h2d,h1d,p6d,p5d,p4d,
     2               triplesx,t1sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d
      integer h3,h2,h1,p6,p5,p4
      double precision triplesx(h1d,h3d,h2d,p6d,p5d,p4d)
      double precision t1sub(p4d,h1d)
      double precision v2sub(h3d,h2d,p6d,p5d)
      do p4=1,p4d
      do p5=1,p5d
      do p6=1,p6d
      do h2=1,h2d
      do h3=1,h3d
      do h1=1,h1d
       triplesx(h1,h3,h2,p6,p5,p4)=triplesx(h1,h3,h2,p6,p5,p4)
     1   + t1sub(p4,h1)*v2sub(h3,h2,p6,p5)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      return
      end
c
      subroutine sd_t_s1_4(h3d,h2d,h1d,p6d,p5d,p4d,
     2               triplesx,t1sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d
      integer h3,h2,h1,p6,p5,p4
      double precision triplesx(h3d,h2d,h1d,p6d,p4d,p5d)
      double precision t1sub(p4d,h1d)
      double precision v2sub(h3d,h2d,p6d,p5d)
      do p5=1,p5d
      do p4=1,p4d
      do p6=1,p6d
      do h1=1,h1d
      do h2=1,h2d
      do h3=1,h3d
       triplesx(h3,h2,h1,p6,p4,p5)=triplesx(h3,h2,h1,p6,p4,p5)
     1   - t1sub(p4,h1)*v2sub(h3,h2,p6,p5)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      return
      end
c
      subroutine sd_t_s1_5(h3d,h2d,h1d,p6d,p5d,p4d,
     2               triplesx,t1sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d
      integer h3,h2,h1,p6,p5,p4
      double precision triplesx(h3d,h1d,h2d,p6d,p4d,p5d)
      double precision t1sub(p4d,h1d)
      double precision v2sub(h3d,h2d,p6d,p5d)
      do p5=1,p5d
      do p4=1,p4d
      do p6=1,p6d
      do h2=1,h2d
      do h1=1,h1d
      do h3=1,h3d
       triplesx(h3,h1,h2,p6,p4,p5)=triplesx(h3,h1,h2,p6,p4,p5)
     1   + t1sub(p4,h1)*v2sub(h3,h2,p6,p5)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      return
      end
c
      subroutine sd_t_s1_6(h3d,h2d,h1d,p6d,p5d,p4d,
     2               triplesx,t1sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d
      integer h3,h2,h1,p6,p5,p4
      double precision triplesx(h1d,h3d,h2d,p6d,p4d,p5d)
      double precision t1sub(p4d,h1d)
      double precision v2sub(h3d,h2d,p6d,p5d)
      do p5=1,p5d
      do p4=1,p4d
      do p6=1,p6d
      do h2=1,h2d
      do h3=1,h3d
      do h1=1,h1d
       triplesx(h1,h3,h2,p6,p4,p5)=triplesx(h1,h3,h2,p6,p4,p5)
     1   - t1sub(p4,h1)*v2sub(h3,h2,p6,p5)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      return
      end
c
      subroutine sd_t_s1_7(h3d,h2d,h1d,p6d,p5d,p4d,
     2               triplesx,t1sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d
      integer h3,h2,h1,p6,p5,p4
      double precision triplesx(h3d,h2d,h1d,p4d,p6d,p5d)
      double precision t1sub(p4d,h1d)
      double precision v2sub(h3d,h2d,p6d,p5d)
      do p5=1,p5d
      do p6=1,p6d
      do p4=1,p4d
      do h1=1,h1d
      do h2=1,h2d
      do h3=1,h3d
       triplesx(h3,h2,h1,p4,p6,p5)=triplesx(h3,h2,h1,p4,p6,p5)
     1   + t1sub(p4,h1)*v2sub(h3,h2,p6,p5)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      return
      end
c
      subroutine sd_t_s1_8(h3d,h2d,h1d,p6d,p5d,p4d,
     2               triplesx,t1sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d
      integer h3,h2,h1,p6,p5,p4
      double precision triplesx(h3d,h1d,h2d,p4d,p6d,p5d)
      double precision t1sub(p4d,h1d)
      double precision v2sub(h3d,h2d,p6d,p5d)
      do p5=1,p5d
      do p6=1,p6d
      do p4=1,p4d
      do h2=1,h2d
      do h1=1,h1d
      do h3=1,h3d
       triplesx(h3,h1,h2,p4,p6,p5)=triplesx(h3,h1,h2,p4,p6,p5)
     1   - t1sub(p4,h1)*v2sub(h3,h2,p6,p5)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      return
      end
c
      subroutine sd_t_s1_9(h3d,h2d,h1d,p6d,p5d,p4d,
     2               triplesx,t1sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d
      integer h3,h2,h1,p6,p5,p4
      double precision triplesx(h1d,h3d,h2d,p4d,p6d,p5d)
      double precision t1sub(p4d,h1d)
      double precision v2sub(h3d,h2d,p6d,p5d)
      do p5=1,p5d
      do p6=1,p6d
      do p4=1,p4d
      do h2=1,h2d
      do h3=1,h3d
      do h1=1,h1d
       triplesx(h1,h3,h2,p4,p6,p5)=triplesx(h1,h3,h2,p4,p6,p5)
     1   + t1sub(p4,h1)*v2sub(h3,h2,p6,p5)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      return
      end
c
c Cyrus: Start with this one.
c
      subroutine sd_t_d1_1(h3d,h2d,h1d,p6d,p5d,p4d,h7d,
     2               triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer mod_val
      integer h3d,h2d,h1d,p6d,p5d,p4d,h7d
      integer h3,h2,h1,p6,p5,p4,h7
      double precision triplesx(h3d,h2d,h1d,p6d,p5d,p4d)
      double precision t2sub(h7d,p4d,p5d,h1d)
      double precision v2sub(h3d,h2d,p6d,h7d)
        WRITE*,'
       mod_val = mod(h7d,4)

       do p5=1,p5d
       do p6=1,p6d
       do h1=1,h1d
       do p4=1,p4d
       do h2=1,h2d
       do h3=1,h3d
       do h7=1,mod_val
        triplesx(h3,h2,h1,p6,p5,p4)=triplesx(h3,h2,h1,p6,p5,p4)
     1  -t2sub(h7,p4,p5,h1)*v2sub(h3,h2,p6,h7)
       enddo
       enddo
       enddo
       enddo
       enddo
       enddo
       enddo'


       do p5=1,p5d
       do p6=1,p6d
       do h1=1,h1d
       do p4=1,p4d
       do h2=1,h2d
       do h7=1,h7d/2,4
       do h3=1,h3d,4

        triplesx(h3+0,h2,h1,p6,p5,p4)=triplesx(h3+0,h2,h1,p6,p5,p4)
     1  -t2sub(h7+0,p4,p5,h1)*v2sub(h3+0,h2,p6,h7+0)
        triplesx(h3+0,h2,h1,p6,p5,p4)=triplesx(h3+0,h2,h1,p6,p5,p4)
     1  -t2sub(h7+1,p4,p5,h1)*v2sub(h3+0,h2,p6,h7+1)
        triplesx(h3+0,h2,h1,p6,p5,p4)=triplesx(h3+0,h2,h1,p6,p5,p4)
     1  -t2sub(h7+2,p4,p5,h1)*v2sub(h3+0,h2,p6,h7+2)
        triplesx(h3+0,h2,h1,p6,p5,p4)=triplesx(h3+0,h2,h1,p6,p5,p4)
     1  -t2sub(h7+3,p4,p5,h1)*v2sub(h3+0,h2,p6,h7+3)

        triplesx(h3+1,h2,h1,p6,p5,p4)=triplesx(h3+1,h2,h1,p6,p5,p4)
     1  -t2sub(h7+0,p4,p5,h1)*v2sub(h3+1,h2,p6,h7+0)
        triplesx(h3+1,h2,h1,p6,p5,p4)=triplesx(h3+1,h2,h1,p6,p5,p4)
     1  -t2sub(h7+1,p4,p5,h1)*v2sub(h3+1,h2,p6,h7+1)
        triplesx(h3+1,h2,h1,p6,p5,p4)=triplesx(h3+1,h2,h1,p6,p5,p4)
     1  -t2sub(h7+2,p4,p5,h1)*v2sub(h3+1,h2,p6,h7+2)
        triplesx(h3+1,h2,h1,p6,p5,p4)=triplesx(h3+1,h2,h1,p6,p5,p4)
     1  -t2sub(h7+3,p4,p5,h1)*v2sub(h3+1,h2,p6,h7+3)

        triplesx(h3+2,h2,h1,p6,p5,p4)=triplesx(h3+2,h2,h1,p6,p5,p4)
     1  -t2sub(h7+0,p4,p5,h1)*v2sub(h3+2,h2,p6,h7+0)       
        triplesx(h3+2,h2,h1,p6,p5,p4)=triplesx(h3+2,h2,h1,p6,p5,p4)
     1  -t2sub(h7+1,p4,p5,h1)*v2sub(h3+2,h2,p6,h7+1)
        triplesx(h3+2,h2,h1,p6,p5,p4)=triplesx(h3+2,h2,h1,p6,p5,p4)
     1  -t2sub(h7+2,p4,p5,h1)*v2sub(h3,h2,p6,h7+2)
        triplesx(h3+2,h2,h1,p6,p5,p4)=triplesx(h3+2,h2,h1,p6,p5,p4)
     1  -t2sub(h7+3,p4,p5,h1)*v2sub(h3,h2,p6,h7+3)

        triplesx(h3+3,h2,h1,p6,p5,p4)=triplesx(h3+3,h2,h1,p6,p5,p4)
     1  -t2sub(h7+0,p4,p5,h1)*v2sub(h3+3,h2,p6,h7+0)
        triplesx(h3+3,h2,h1,p6,p5,p4)=triplesx(h3+3,h2,h1,p6,p5,p4)
     1  -t2sub(h7+1,p4,p5,h1)*v2sub(h3+3,h2,p6,h7+1)
        triplesx(h3+3,h2,h1,p6,p5,p4)=triplesx(h3+3,h2,h1,p6,p5,p4)
     1  -t2sub(h7+2,p4,p5,h1)*v2sub(h3+3,h2,p6,h7+2)
        triplesx(h3+3,h2,h1,p6,p5,p4)=triplesx(h3+3,h2,h1,p6,p5,p4)
     1  -t2sub(h7+3,p4,p5,h1)*v2sub(h3+3,h2,p6,h7+3)
       enddo
       enddo
       enddo
       enddo
       enddo
       enddo
       enddo


       do p5=1,p5d
       do p6=1,p6d
       do h1=1,h1d
       do p4=1,p4d
       do h2=1,h2d
       do h7=(h7d/2)+1,h7d,4
       do h3=1,h3d,4

        triplesx(h3+0,h2,h1,p6,p5,p4)=triplesx(h3+0,h2,h1,p6,p5,p4)
     1  -t2sub(h7+0,p4,p5,h1)*v2sub(h3+0,h2,p6,h7+0)
        triplesx(h3+0,h2,h1,p6,p5,p4)=triplesx(h3+0,h2,h1,p6,p5,p4)
     1  -t2sub(h7+1,p4,p5,h1)*v2sub(h3+0,h2,p6,h7+1)
        triplesx(h3+0,h2,h1,p6,p5,p4)=triplesx(h3+0,h2,h1,p6,p5,p4)
     1  -t2sub(h7+2,p4,p5,h1)*v2sub(h3+0,h2,p6,h7+2)
        triplesx(h3+0,h2,h1,p6,p5,p4)=triplesx(h3+0,h2,h1,p6,p5,p4)
     1  -t2sub(h7+3,p4,p5,h1)*v2sub(h3+0,h2,p6,h7+3)

        triplesx(h3+1,h2,h1,p6,p5,p4)=triplesx(h3+1,h2,h1,p6,p5,p4)
     1  -t2sub(h7+0,p4,p5,h1)*v2sub(h3+1,h2,p6,h7+0)
        triplesx(h3+1,h2,h1,p6,p5,p4)=triplesx(h3+1,h2,h1,p6,p5,p4)
     1  -t2sub(h7+1,p4,p5,h1)*v2sub(h3+1,h2,p6,h7+1)
        triplesx(h3+1,h2,h1,p6,p5,p4)=triplesx(h3+1,h2,h1,p6,p5,p4)
     1  -t2sub(h7+2,p4,p5,h1)*v2sub(h3+1,h2,p6,h7+2)
        triplesx(h3+1,h2,h1,p6,p5,p4)=triplesx(h3+1,h2,h1,p6,p5,p4)
     1  -t2sub(h7+3,p4,p5,h1)*v2sub(h3+1,h2,p6,h7+3)

        triplesx(h3+2,h2,h1,p6,p5,p4)=triplesx(h3+2,h2,h1,p6,p5,p4)
     1  -t2sub(h7+0,p4,p5,h1)*v2sub(h3+2,h2,p6,h7+0)       
        triplesx(h3+2,h2,h1,p6,p5,p4)=triplesx(h3+2,h2,h1,p6,p5,p4)
     1  -t2sub(h7+1,p4,p5,h1)*v2sub(h3+2,h2,p6,h7+1)
        triplesx(h3+2,h2,h1,p6,p5,p4)=triplesx(h3+2,h2,h1,p6,p5,p4)
     1  -t2sub(h7+2,p4,p5,h1)*v2sub(h3,h2,p6,h7+2)
        triplesx(h3+2,h2,h1,p6,p5,p4)=triplesx(h3+2,h2,h1,p6,p5,p4)
     1  -t2sub(h7+3,p4,p5,h1)*v2sub(h3,h2,p6,h7+3)

        triplesx(h3+3,h2,h1,p6,p5,p4)=triplesx(h3+3,h2,h1,p6,p5,p4)
     1  -t2sub(h7+0,p4,p5,h1)*v2sub(h3+3,h2,p6,h7+0)
        triplesx(h3+3,h2,h1,p6,p5,p4)=triplesx(h3+3,h2,h1,p6,p5,p4)
     1  -t2sub(h7+1,p4,p5,h1)*v2sub(h3+3,h2,p6,h7+1)
        triplesx(h3+3,h2,h1,p6,p5,p4)=triplesx(h3+3,h2,h1,p6,p5,p4)
     1  -t2sub(h7+2,p4,p5,h1)*v2sub(h3+3,h2,p6,h7+2)
        triplesx(h3+3,h2,h1,p6,p5,p4)=triplesx(h3+3,h2,h1,p6,p5,p4)
     1  -t2sub(h7+3,p4,p5,h1)*v2sub(h3+3,h2,p6,h7+3)
       enddo
       enddo
       enddo
       enddo
       enddo
       enddo
       enddo
        
      return
      end

c
      subroutine sd_t_d1_2(h3d,h2d,h1d,p6d,p5d,p4d,h7d,
     2               triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,h7d
      integer h3,h2,h1,p6,p5,p4,h7
      double precision triplesx(h3d,h1d,h2d,p6d,p5d,p4d)
      double precision t2sub(h7d,p4d,p5d,h1d)
      double precision v2sub(h3d,h2d,p6d,h7d)
      do p4=1,p4d
      do p5=1,p5d
      do p6=1,p6d
      do h2=1,h2d
      do h1=1,h1d
      do h3=1,h3d
      do h7=1,h7d
       triplesx(h3,h1,h2,p6,p5,p4)=triplesx(h3,h1,h2,p6,p5,p4)
     1   + t2sub(h7,p4,p5,h1)*v2sub(h3,h2,p6,h7)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo  
      enddo
      return
      end
c
      subroutine sd_t_d1_3(h3d,h2d,h1d,p6d,p5d,p4d,h7d,
     2               triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,h7d
      integer h3,h2,h1,p6,p5,p4,h7
      double precision triplesx(h1d,h3d,h2d,p6d,p5d,p4d)
      double precision t2sub(h7d,p4d,p5d,h1d)
      double precision v2sub(h3d,h2d,p6d,h7d)
      do p4=1,p4d
      do p5=1,p5d
      do p6=1,p6d
      do h2=1,h2d
      do h3=1,h3d
      do h1=1,h1d
      do h7=1,h7d
       triplesx(h1,h3,h2,p6,p5,p4)=triplesx(h1,h3,h2,p6,p5,p4)
     1  -t2sub(h7,p4,p5,h1)*v2sub(h3,h2,p6,h7)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      return
      end
c
      subroutine sd_t_d1_4(h3d,h2d,h1d,p6d,p5d,p4d,h7d,
     2               triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,h7d
      integer h3,h2,h1,p6,p5,p4,h7
      double precision triplesx(h3d,h2d,h1d,p5d,p4d,p6d)
      double precision t2sub(h7d,p4d,p5d,h1d)
      double precision v2sub(h3d,h2d,p6d,h7d)
      do p6=1,p6d
      do p4=1,p4d
      do p5=1,p5d
      do h1=1,h1d
      do h2=1,h2d
      do h3=1,h3d
      do h7=1,h7d
       triplesx(h3,h2,h1,p5,p4,p6)=triplesx(h3,h2,h1,p5,p4,p6)
     1  -t2sub(h7,p4,p5,h1)*v2sub(h3,h2,p6,h7)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      return
      end
c
      subroutine sd_t_d1_5(h3d,h2d,h1d,p6d,p5d,p4d,h7d,
     2               triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,h7d
      integer h3,h2,h1,p6,p5,p4,h7
      double precision triplesx(h3d,h1d,h2d,p5d,p4d,p6d)
      double precision t2sub(h7d,p4d,p5d,h1d)
      double precision v2sub(h3d,h2d,p6d,h7d)
      do p6=1,p6d
      do p4=1,p4d
      do p5=1,p5d
      do h2=1,h2d
      do h1=1,h1d
      do h3=1,h3d
      do h7=1,h7d
       triplesx(h3,h1,h2,p5,p4,p6)=triplesx(h3,h1,h2,p5,p4,p6)
     1   + t2sub(h7,p4,p5,h1)*v2sub(h3,h2,p6,h7)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      return
      end
c
      subroutine sd_t_d1_6(h3d,h2d,h1d,p6d,p5d,p4d,h7d,
     2               triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,h7d
      integer h3,h2,h1,p6,p5,p4,h7
      double precision triplesx(h1d,h3d,h2d,p5d,p4d,p6d)
      double precision t2sub(h7d,p4d,p5d,h1d)
      double precision v2sub(h3d,h2d,p6d,h7d)
      do p6=1,p6d
      do p4=1,p4d
      do p5=1,p5d
      do h2=1,h2d
      do h3=1,h3d
      do h1=1,h1d
      do h7=1,h7d
       triplesx(h1,h3,h2,p5,p4,p6)=triplesx(h1,h3,h2,p5,p4,p6)
     1  -t2sub(h7,p4,p5,h1)*v2sub(h3,h2,p6,h7)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      return
      end
c
      subroutine sd_t_d1_7(h3d,h2d,h1d,p6d,p5d,p4d,h7d,
     2               triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,h7d
      integer h3,h2,h1,p6,p5,p4,h7
      double precision triplesx(h3d,h2d,h1d,p5d,p6d,p4d)
      double precision t2sub(h7d,p4d,p5d,h1d)
      double precision v2sub(h3d,h2d,p6d,h7d)
      do p4=1,p4d
      do p6=1,p6d
      do p5=1,p5d
      do h1=1,h1d
      do h2=1,h2d
      do h3=1,h3d
      do h7=1,h7d
       triplesx(h3,h2,h1,p5,p6,p4)=triplesx(h3,h2,h1,p5,p6,p4)
     1   + t2sub(h7,p4,p5,h1)*v2sub(h3,h2,p6,h7)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      return
      end
c
      subroutine sd_t_d1_8(h3d,h2d,h1d,p6d,p5d,p4d,h7d,
     2               triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,h7d
      integer h3,h2,h1,p6,p5,p4,h7
      double precision triplesx(h3d,h1d,h2d,p5d,p6d,p4d)
      double precision t2sub(h7d,p4d,p5d,h1d)
      double precision v2sub(h3d,h2d,p6d,h7d)
      do p4=1,p4d
      do p6=1,p6d
      do p5=1,p5d
      do h2=1,h2d
      do h1=1,h1d
      do h3=1,h3d
      do h7=1,h7d
       triplesx(h3,h1,h2,p5,p6,p4)=triplesx(h3,h1,h2,p5,p6,p4)
     1  -t2sub(h7,p4,p5,h1)*v2sub(h3,h2,p6,h7)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      return
      end
c
      subroutine sd_t_d1_9(h3d,h2d,h1d,p6d,p5d,p4d,h7d,
     2               triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,h7d
      integer h3,h2,h1,p6,p5,p4,h7
      double precision triplesx(h1d,h3d,h2d,p5d,p6d,p4d)
      double precision txtmp(h1d,h3d)
      double precision t2sub(h7d,p4d,p5d,h1d)
      double precision v2sub(h3d,h2d,p6d,h7d)
      do p4=1,p4d
      do p6=1,p6d
      do p5=1,p5d
      do h2=1,h2d

      do h1=1,h1d
      do h3=1,h3d
       txtmp(h3,h1) = triplesx(h1,h3,h2,p5,p6,p4)
      enddo
      enddo

      do h1=1,h1d
      do h3=1,h3d
      do h7=1,h7d
       txtmp(h3,h1)=txtmp(h3,h1)
     1   + t2sub(h7,p4,p5,h1)*v2sub(h3,h2,p6,h7)
      enddo
      enddo
      enddo

      do h3=1,h3d
      do h1=1,h1d
       triplesx(h1,h3,h2,p5,p6,p4)=triplesx(h1,h3,h2,p5,p6,p4)
     1   + txtmp(h3,h1)
      enddo
      enddo

      enddo
      enddo
      enddo
      enddo
      return
      end
c
      subroutine sd_t_d2_1(h3d,h2d,h1d,p6d,p5d,p4d,p7d,
     2               triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,p7d
      integer h3,h2,h1,p6,p5,p4,p7
      double precision triplesx(h3d,h2d,h1d,p6d,p5d,p4d)
      double precision t2sub(p7d,p4d,h1d,h2d)
      double precision v2sub(p7d,h3d,p6d,p5d)
      do p4=1,p4d
      do p5=1,p5d
      do p6=1,p6d
      do h1=1,h1d
      do h2=1,h2d
      do h3=1,h3d
      do p7=1,p7d
       triplesx(h3,h2,h1,p6,p5,p4)=triplesx(h3,h2,h1,p6,p5,p4)
     1  -t2sub(p7,p4,h1,h2)*v2sub(p7,h3,p6,p5)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      return
      end
c
      subroutine sd_t_d2_2(h3d,h2d,h1d,p6d,p5d,p4d,p7d,
     2               triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,p7d
      integer h3,h2,h1,p6,p5,p4,p7
      double precision triplesx(h2d,h1d,h3d,p6d,p5d,p4d)
      double precision t2sub(p7d,p4d,h1d,h2d)
      double precision v2sub(p7d,h3d,p6d,p5d)
      do p4=1,p4d
      do p5=1,p5d
      do p6=1,p6d
      do h3=1,h3d
      do h1=1,h1d
      do h2=1,h2d
      do p7=1,p7d
       triplesx(h2,h1,h3,p6,p5,p4)=triplesx(h2,h1,h3,p6,p5,p4)
     1  -t2sub(p7,p4,h1,h2)*v2sub(p7,h3,p6,p5)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      return
      end
c
      subroutine sd_t_d2_3(h3d,h2d,h1d,p6d,p5d,p4d,p7d,
     2               triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,p7d
      integer h3,h2,h1,p6,p5,p4,p7
      double precision triplesx(h2d,h3d,h1d,p6d,p5d,p4d)
      double precision t2sub(p7d,p4d,h1d,h2d)
      double precision v2sub(p7d,h3d,p6d,p5d)
      do p4=1,p4d
      do p5=1,p5d
      do p6=1,p6d
      do h1=1,h1d
      do h3=1,h3d
      do h2=1,h2d
      do p7=1,p7d
       triplesx(h2,h3,h1,p6,p5,p4)=triplesx(h2,h3,h1,p6,p5,p4)
     1   + t2sub(p7,p4,h1,h2)*v2sub(p7,h3,p6,p5)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      return
      end
c
      subroutine sd_t_d2_4(h3d,h2d,h1d,p6d,p5d,p4d,p7d,
     2               triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,p7d
      integer h3,h2,h1,p6,p5,p4,p7
      double precision triplesx(h3d,h2d,h1d,p6d,p4d,p5d)
      double precision t2sub(p7d,p4d,h1d,h2d)
      double precision v2sub(p7d,h3d,p6d,p5d)
      do p5=1,p5d
      do p4=1,p4d
      do p6=1,p6d
      do h1=1,h1d
      do h2=1,h2d
      do h3=1,h3d
      do p7=1,p7d
       triplesx(h3,h2,h1,p6,p4,p5)=triplesx(h3,h2,h1,p6,p4,p5)
     1   + t2sub(p7,p4,h1,h2)*v2sub(p7,h3,p6,p5)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      return
      end
c
      subroutine sd_t_d2_5(h3d,h2d,h1d,p6d,p5d,p4d,p7d,
     2               triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,p7d
      integer h3,h2,h1,p6,p5,p4,p7
      double precision triplesx(h2d,h1d,h3d,p6d,p4d,p5d)
      double precision t2sub(p7d,p4d,h1d,h2d)
      double precision v2sub(p7d,h3d,p6d,p5d)
      do p5=1,p5d
      do p4=1,p4d
      do p6=1,p6d
      do h3=1,h3d
      do h1=1,h1d
      do h2=1,h2d
      do p7=1,p7d
       triplesx(h2,h1,h3,p6,p4,p5)=triplesx(h2,h1,h3,p6,p4,p5)
     1   + t2sub(p7,p4,h1,h2)*v2sub(p7,h3,p6,p5)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      return
      end
c
      subroutine sd_t_d2_6(h3d,h2d,h1d,p6d,p5d,p4d,p7d,
     2               triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,p7d
      integer h3,h2,h1,p6,p5,p4,p7
      double precision triplesx(h2d,h3d,h1d,p6d,p4d,p5d)
      double precision t2sub(p7d,p4d,h1d,h2d)
      double precision v2sub(p7d,h3d,p6d,p5d)
      do p5=1,p5d
      do p4=1,p4d
      do p6=1,p6d
      do h1=1,h1d
      do h3=1,h3d
      do h2=1,h2d
      do p7=1,p7d
       triplesx(h2,h3,h1,p6,p4,p5)=triplesx(h2,h3,h1,p6,p4,p5)
     1  -t2sub(p7,p4,h1,h2)*v2sub(p7,h3,p6,p5)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      return
      end
c
      subroutine sd_t_d2_7(h3d,h2d,h1d,p6d,p5d,p4d,p7d,
     2               triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,p7d
      integer h3,h2,h1,p6,p5,p4,p7
      double precision triplesx(h3d,h2d,h1d,p4d,p6d,p5d)
      double precision t2sub(p7d,p4d,h1d,h2d)
      double precision v2sub(p7d,h3d,p6d,p5d)
      do p5=1,p5d
      do p6=1,p6d
      do p4=1,p4d
      do h1=1,h1d
      do h2=1,h2d
      do h3=1,h3d
      do p7=1,p7d
       triplesx(h3,h2,h1,p4,p6,p5)=triplesx(h3,h2,h1,p4,p6,p5)
     1  -t2sub(p7,p4,h1,h2)*v2sub(p7,h3,p6,p5)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      return
      end
c
      subroutine sd_t_d2_8(h3d,h2d,h1d,p6d,p5d,p4d,p7d,
     2               triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,p7d
      integer h3,h2,h1,p6,p5,p4,p7
      double precision triplesx(h2d,h1d,h3d,p4d,p6d,p5d)
      double precision t2sub(p7d,p4d,h1d,h2d)
      double precision v2sub(p7d,h3d,p6d,p5d)
      do p5=1,p5d
      do p6=1,p6d
      do p4=1,p4d
      do h3=1,h3d
      do h1=1,h1d
      do h2=1,h2d
      do p7=1,p7d
       triplesx(h2,h1,h3,p4,p6,p5)=triplesx(h2,h1,h3,p4,p6,p5)
     1  -t2sub(p7,p4,h1,h2)*v2sub(p7,h3,p6,p5)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      return
      end
c
      subroutine sd_t_d2_9(h3d,h2d,h1d,p6d,p5d,p4d,p7d,
     2               triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,p7d
      integer h3,h2,h1,p6,p5,p4,p7
      double precision triplesx(h2d,h3d,h1d,p4d,p6d,p5d)
      double precision t2sub(p7d,p4d,h1d,h2d)
      double precision v2sub(p7d,h3d,p6d,p5d)
      do p5=1,p5d
      do p6=1,p6d
      do p4=1,p4d
      do h1=1,h1d
      do h3=1,h3d
      do h2=1,h2d
      do p7=1,p7d
       triplesx(h2,h3,h1,p4,p6,p5)=triplesx(h2,h3,h1,p4,p6,p5)
     1   + t2sub(p7,p4,h1,h2)*v2sub(p7,h3,p6,p5)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      return
      end
