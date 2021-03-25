      subroutine acc_zero(h3d,h2d,h1d,p6d,p5d,p4d,triplesx)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d
      integer h3,h2,h1,p6,p5,p4
      double precision triplesx(h3d,h2d,h1d,p6d,p5d,p4d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6)
!$omp& is_device_ptr(triplesx)
      do p4=1,p4d
      do p5=1,p5d
      do p6=1,p6d
      do h1=1,h1d
      do h2=1,h2d
      do h3=1,h3d
       triplesx(h3,h2,h1,p6,p5,p4)=0.0d0
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
!$omp end target teams distribute parallel do
      return
      end
c
c These have been separated out from ccsd_t_singles_l.F and ccsd_t_doubles_l.F
c
      subroutine acc_sd_t_s1_1(h3d,h2d,h1d,p6d,p5d,p4d,
     2                     triplesx,t1sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d
      integer h3,h2,h1,p6,p5,p4
      double precision triplesx(h3d,h2d,h1d,p6d,p5d,p4d)
      double precision t1sub(p4d,h1d)
      double precision v2sub(h3d,h2d,p6d,p5d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6)
!$omp& is_device_ptr(triplesx,v2sub,t1sub)
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
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_s1_2(h3d,h2d,h1d,p6d,p5d,p4d,
     2                     triplesx,t1sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d
      integer h3,h2,h1,p6,p5,p4
      double precision triplesx(h3d,h1d,h2d,p6d,p5d,p4d)
      double precision t1sub(p4d,h1d)
      double precision v2sub(h3d,h2d,p6d,p5d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6)
!$omp& is_device_ptr(triplesx,v2sub,t1sub)
      do p4=1,p4d
      do p5=1,p5d
      do p6=1,p6d
      do h1=1,h1d
      do h2=1,h2d ! interchanging h1 and h2 was a huge win with Cray+OpenMP
      do h3=1,h3d
       triplesx(h3,h1,h2,p6,p5,p4)=triplesx(h3,h1,h2,p6,p5,p4)
     1   - t1sub(p4,h1)*v2sub(h3,h2,p6,p5)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_s1_3(h3d,h2d,h1d,p6d,p5d,p4d,
     2                     triplesx,t1sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d
      integer h3,h2,h1,p6,p5,p4
      double precision triplesx(h1d,h3d,h2d,p6d,p5d,p4d)
      double precision t1sub(p4d,h1d)
      double precision v2sub(h3d,h2d,p6d,p5d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6)
!$omp& is_device_ptr(triplesx,v2sub,t1sub)
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
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_s1_4(h3d,h2d,h1d,p6d,p5d,p4d,
     2                     triplesx,t1sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d
      integer h3,h2,h1,p6,p5,p4
      double precision triplesx(h3d,h2d,h1d,p6d,p4d,p5d)
      double precision t1sub(p4d,h1d)
      double precision v2sub(h3d,h2d,p6d,p5d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6)
!$omp& is_device_ptr(triplesx,v2sub,t1sub)
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
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_s1_5(h3d,h2d,h1d,p6d,p5d,p4d,
     2                     triplesx,t1sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d
      integer h3,h2,h1,p6,p5,p4
      double precision triplesx(h3d,h1d,h2d,p6d,p4d,p5d)
      double precision t1sub(p4d,h1d)
      double precision v2sub(h3d,h2d,p6d,p5d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6)
!$omp& is_device_ptr(triplesx,v2sub,t1sub)
      do p5=1,p5d
      do p4=1,p4d
      do p6=1,p6d
      do h1=1,h1d
      do h2=1,h2d
      do h3=1,h3d
       triplesx(h3,h1,h2,p6,p4,p5)=triplesx(h3,h1,h2,p6,p4,p5)
     1   + t1sub(p4,h1)*v2sub(h3,h2,p6,p5)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_s1_6(h3d,h2d,h1d,p6d,p5d,p4d,
     2                     triplesx,t1sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d
      integer h3,h2,h1,p6,p5,p4
      double precision triplesx(h1d,h3d,h2d,p6d,p4d,p5d)
      double precision t1sub(p4d,h1d)
      double precision v2sub(h3d,h2d,p6d,p5d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6)
!$omp& is_device_ptr(triplesx,v2sub,t1sub)
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
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_s1_7(h3d,h2d,h1d,p6d,p5d,p4d,
     2                     triplesx,t1sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d
      integer h3,h2,h1,p6,p5,p4
      double precision triplesx(h3d,h2d,h1d,p4d,p6d,p5d)
      double precision t1sub(p4d,h1d)
      double precision v2sub(h3d,h2d,p6d,p5d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6)
!$omp& is_device_ptr(triplesx,v2sub,t1sub)
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
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_s1_8(h3d,h2d,h1d,p6d,p5d,p4d,
     2                     triplesx,t1sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d
      integer h3,h2,h1,p6,p5,p4
      double precision triplesx(h3d,h1d,h2d,p4d,p6d,p5d)
      double precision t1sub(p4d,h1d)
      double precision v2sub(h3d,h2d,p6d,p5d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6)
!$omp& is_device_ptr(triplesx,v2sub,t1sub)
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
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_s1_9(h3d,h2d,h1d,p6d,p5d,p4d,
     2                     triplesx,t1sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d
      integer h3,h2,h1,p6,p5,p4
      double precision triplesx(h1d,h3d,h2d,p4d,p6d,p5d)
      double precision t1sub(p4d,h1d)
      double precision v2sub(h3d,h2d,p6d,p5d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6)
!$omp& is_device_ptr(triplesx,v2sub,t1sub)
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
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_d1_1(h3d,h2d,h1d,p6d,p5d,p4d,h7d,
     2                     triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,h7d
      integer h3,h2,h1,p6,p5,p4,h7
      double precision triplesx(h3d,h2d,h1d,p6d,p5d,p4d)
      double precision t2sub(h7d,p4d,p5d,h1d)
      double precision v2sub(h3d,h2d,p6d,h7d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6,h7)
!$omp& is_device_ptr(triplesx,v2sub,t2sub)
      do p4=1,p4d
      do p5=1,p5d
      do p6=1,p6d
      do h1=1,h1d
      do h2=1,h2d
      do h3=1,h3d
      do h7=1,h7d
       triplesx(h3,h2,h1,p6,p5,p4)=triplesx(h3,h2,h1,p6,p5,p4)
     1  -t2sub(h7,p4,p5,h1)*v2sub(h3,h2,p6,h7)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_d1_2(h3d,h2d,h1d,p6d,p5d,p4d,h7d,
     2                     triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,h7d
      integer h3,h2,h1,p6,p5,p4,h7
      double precision triplesx(h3d,h1d,h2d,p6d,p5d,p4d)
      double precision t2sub(h7d,p4d,p5d,h1d)
      double precision v2sub(h3d,h2d,p6d,h7d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6,h7)
!$omp& is_device_ptr(triplesx,v2sub,t2sub)
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
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_d1_3(h3d,h2d,h1d,p6d,p5d,p4d,h7d,
     2                     triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,h7d
      integer h3,h2,h1,p6,p5,p4,h7
      double precision triplesx(h1d,h3d,h2d,p6d,p5d,p4d)
      double precision t2sub(h7d,p4d,p5d,h1d)
      double precision v2sub(h3d,h2d,p6d,h7d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6,h7)
!$omp& is_device_ptr(triplesx,v2sub,t2sub)
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
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_d1_4(h3d,h2d,h1d,p6d,p5d,p4d,h7d,
     2                     triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,h7d
      integer h3,h2,h1,p6,p5,p4,h7
      double precision triplesx(h3d,h2d,h1d,p5d,p4d,p6d)
      double precision t2sub(h7d,p4d,p5d,h1d)
      double precision v2sub(h3d,h2d,p6d,h7d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6,h7)
!$omp& is_device_ptr(triplesx,v2sub,t2sub)
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
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_d1_5(h3d,h2d,h1d,p6d,p5d,p4d,h7d,
     2                     triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,h7d
      integer h3,h2,h1,p6,p5,p4,h7
      double precision triplesx(h3d,h1d,h2d,p5d,p4d,p6d)
      double precision t2sub(h7d,p4d,p5d,h1d)
      double precision v2sub(h3d,h2d,p6d,h7d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6,h7)
!$omp& is_device_ptr(triplesx,v2sub,t2sub)
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
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_d1_6(h3d,h2d,h1d,p6d,p5d,p4d,h7d,
     2                     triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,h7d
      integer h3,h2,h1,p6,p5,p4,h7
      double precision triplesx(h1d,h3d,h2d,p5d,p4d,p6d)
      double precision t2sub(h7d,p4d,p5d,h1d)
      double precision v2sub(h3d,h2d,p6d,h7d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6,h7)
!$omp& is_device_ptr(triplesx,v2sub,t2sub)
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
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_d1_7(h3d,h2d,h1d,p6d,p5d,p4d,h7d,
     2                     triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,h7d
      integer h3,h2,h1,p6,p5,p4,h7
      double precision triplesx(h3d,h2d,h1d,p5d,p6d,p4d)
      double precision t2sub(h7d,p4d,p5d,h1d)
      double precision v2sub(h3d,h2d,p6d,h7d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6,h7)
!$omp& is_device_ptr(triplesx,v2sub,t2sub)
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
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_d1_8(h3d,h2d,h1d,p6d,p5d,p4d,h7d,
     2                     triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,h7d
      integer h3,h2,h1,p6,p5,p4,h7
      double precision triplesx(h3d,h1d,h2d,p5d,p6d,p4d)
      double precision t2sub(h7d,p4d,p5d,h1d)
      double precision v2sub(h3d,h2d,p6d,h7d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6,h7)
!$omp& is_device_ptr(triplesx,v2sub,t2sub)
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
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_d1_9(h3d,h2d,h1d,p6d,p5d,p4d,h7d,
     2                     triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,h7d
      integer h3,h2,h1,p6,p5,p4,h7
      double precision triplesx(h1d,h3d,h2d,p5d,p6d,p4d)
      double precision t2sub(h7d,p4d,p5d,h1d)
      double precision v2sub(h3d,h2d,p6d,h7d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6,h7)
!$omp& is_device_ptr(triplesx,v2sub,t2sub)
      do p4=1,p4d
      do p6=1,p6d
      do p5=1,p5d
      do h2=1,h2d
      do h3=1,h3d
      do h1=1,h1d
      do h7=1,h7d
       triplesx(h1,h3,h2,p5,p6,p4)=triplesx(h1,h3,h2,p5,p6,p4)
     1   + t2sub(h7,p4,p5,h1)*v2sub(h3,h2,p6,h7)
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
      enddo
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_d2_1(h3d,h2d,h1d,p6d,p5d,p4d,p7d,
     2                     triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,p7d
      integer h3,h2,h1,p6,p5,p4,p7
      double precision triplesx(h3d,h2d,h1d,p6d,p5d,p4d)
      double precision t2sub(p7d,p4d,h1d,h2d)
      double precision v2sub(p7d,h3d,p6d,p5d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6,p7)
!$omp& is_device_ptr(triplesx,v2sub,t2sub)
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
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_d2_2(h3d,h2d,h1d,p6d,p5d,p4d,p7d,
     2                     triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,p7d
      integer h3,h2,h1,p6,p5,p4,p7
      double precision triplesx(h2d,h1d,h3d,p6d,p5d,p4d)
      double precision t2sub(p7d,p4d,h1d,h2d)
      double precision v2sub(p7d,h3d,p6d,p5d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6,p7)
!$omp& is_device_ptr(triplesx,v2sub,t2sub)
      do p5=1,p5d
      do p6=1,p6d
      do h1=1,h1d
      do p4=1,p4d
      do h3=1,h3d
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
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_d2_3(h3d,h2d,h1d,p6d,p5d,p4d,p7d,
     2                     triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,p7d
      integer h3,h2,h1,p6,p5,p4,p7
      double precision triplesx(h2d,h3d,h1d,p6d,p5d,p4d)
      double precision t2sub(p7d,p4d,h1d,h2d)
      double precision v2sub(p7d,h3d,p6d,p5d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6,p7)
!$omp& is_device_ptr(triplesx,v2sub,t2sub)
      do p5=1,p5d
      do p6=1,p6d
      do h1=1,h1d
      do p4=1,p4d
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
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_d2_4(h3d,h2d,h1d,p6d,p5d,p4d,p7d,
     2                     triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,p7d
      integer h3,h2,h1,p6,p5,p4,p7
      double precision triplesx(h3d,h2d,h1d,p6d,p4d,p5d)
      double precision t2sub(p7d,p4d,h1d,h2d)
      double precision v2sub(p7d,h3d,p6d,p5d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6,p7)
!$omp& is_device_ptr(triplesx,v2sub,t2sub)
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
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_d2_5(h3d,h2d,h1d,p6d,p5d,p4d,p7d,
     2                     triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,p7d
      integer h3,h2,h1,p6,p5,p4,p7
      double precision triplesx(h2d,h1d,h3d,p6d,p4d,p5d)
      double precision t2sub(p7d,p4d,h1d,h2d)
      double precision v2sub(p7d,h3d,p6d,p5d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6,p7)
!$omp& is_device_ptr(triplesx,v2sub,t2sub)
      do p5=1,p5d
      do p4=1,p4d
      do p6=1,p6d
      do h1=1,h1d
      do h3=1,h3d
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
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_d2_6(h3d,h2d,h1d,p6d,p5d,p4d,p7d,
     2                     triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,p7d
      integer h3,h2,h1,p6,p5,p4,p7
      double precision triplesx(h2d,h3d,h1d,p6d,p4d,p5d)
      double precision t2sub(p7d,p4d,h1d,h2d)
      double precision v2sub(p7d,h3d,p6d,p5d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6,p7)
!$omp& is_device_ptr(triplesx,v2sub,t2sub)
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
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_d2_7(h3d,h2d,h1d,p6d,p5d,p4d,p7d,
     2                     triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,p7d
      integer h3,h2,h1,p6,p5,p4,p7
      double precision triplesx(h3d,h2d,h1d,p4d,p6d,p5d)
      double precision t2sub(p7d,p4d,h1d,h2d)
      double precision v2sub(p7d,h3d,p6d,p5d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6,p7)
!$omp& is_device_ptr(triplesx,v2sub,t2sub)
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
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_d2_8(h3d,h2d,h1d,p6d,p5d,p4d,p7d,
     2                     triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,p7d
      integer h3,h2,h1,p6,p5,p4,p7
      double precision triplesx(h2d,h1d,h3d,p4d,p6d,p5d)
      double precision t2sub(p7d,p4d,h1d,h2d)
      double precision v2sub(p7d,h3d,p6d,p5d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6,p7)
!$omp& is_device_ptr(triplesx,v2sub,t2sub)
      do p5=1,p5d
      do p6=1,p6d
      do p4=1,p4d
!      do h3=1,h3d ! this loop order drops Edison from 80 to 50
      do h1=1,h1d
      do h3=1,h3d
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
!$omp end target teams distribute parallel do
      return
      end
c
      subroutine acc_sd_t_d2_9(h3d,h2d,h1d,p6d,p5d,p4d,p7d,
     2                     triplesx,t2sub,v2sub)
      IMPLICIT NONE
      integer h3d,h2d,h1d,p6d,p5d,p4d,p7d
      integer h3,h2,h1,p6,p5,p4,p7
      double precision triplesx(h2d,h3d,h1d,p4d,p6d,p5d)
      double precision t2sub(p7d,p4d,h1d,h2d)
      double precision v2sub(p7d,h3d,p6d,p5d)
!$omp target teams distribute
!$omp& parallel do collapse(6)
!$omp& default(shared) schedule(static)
!$omp& private(h1,h2,h3,p4,p5,p6,p7)
!$omp& is_device_ptr(triplesx,v2sub,t2sub)
      do p5=1,p5d
      do p6=1,p6d
      do h1=1,h1d
      do h2=1,h2d
      do p4=1,p4d
      do h3=1,h3d
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
!$omp end target teams distribute parallel do
      return
      end
