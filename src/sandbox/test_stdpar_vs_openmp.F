      function wtime() result(t)
        use iso_fortran_env
        implicit none
        real(kind=REAL64) ::  t
        integer(kind=INT64) :: c, r
        call system_clock(count = c, count_rate = r)
        t = real(c,REAL64) / real(r,REAL64)
      end function wtime

      program perf
        use iso_fortran_env
        implicit none
        real(kind=REAL64) :: wtime
        ! for argument parsing
        integer :: err
        integer :: arglen
        character(len=32) :: argtmp
        ! problem definition
        integer(kind=INT64) :: tile
        integer(kind=INT64) :: tile2
        integer(kind=INT64) :: tile4
        integer(kind=INT64) :: tile6
        integer(kind=INT64) :: tile7
        real(kind=REAL64), allocatable ::  T(:)
        real(kind=REAL64), allocatable ::  S(:)
        real(kind=REAL64), allocatable ::  D(:)
        real(kind=REAL64), allocatable ::  V(:)
        integer(kind=INT32) :: r, reps=5
        real(kind=REAL64) :: timers(30,4), t0, t1

        tile = 20
        call get_command_argument(1,argtmp,arglen,err)
        if (err.eq.0) read(argtmp,'(i32)') tile
        if (tile .lt. 1) then
          write(*,'(a,i5)') 'ERROR: tile must be >= 1 : ', tile
          stop 1
        endif
        print*,'tile=',tile

        tile2 = tile**2
        tile4 = tile**4
        tile6 = tile**6
        tile7 = tile**7

        allocate( T(tile6), S(tile2), D(tile4), V(tile4), stat=err)
        if (err .ne. 0) then
          write(*,'(a,i3)') 'allocation failed: ',err
          stop 1
        endif 

        call random_number(S)
        call random_number(D)
        call random_number(V)
        T = 0

        timers = 0

        do r=1,reps
          t0 = wtime()
          call omp_sd_t_s1_1(tile,tile,tile,tile,tile,tile,T,S,V)
          t1 = wtime()
          timers(1,1) = t1-t0
          t0 = wtime()
          call omp_sd_t_s1_2(tile,tile,tile,tile,tile,tile,T,S,V)
          t1 = wtime()
          timers(2,1) = t1-t0
          t0 = wtime()
          call omp_sd_t_s1_3(tile,tile,tile,tile,tile,tile,T,S,V)
          t1 = wtime()
          timers(3,1) = t1-t0
          t0 = wtime()
          call omp_sd_t_s1_4(tile,tile,tile,tile,tile,tile,T,S,V)
          t1 = wtime()
          timers(4,1) = t1-t0
          t0 = wtime()
          call omp_sd_t_s1_5(tile,tile,tile,tile,tile,tile,T,S,V)
          t1 = wtime()
          timers(5,1) = t1-t0
          t0 = wtime()
          call omp_sd_t_s1_6(tile,tile,tile,tile,tile,tile,T,S,V)
          t1 = wtime()
          timers(6,1) = t1-t0
          t0 = wtime()
          call omp_sd_t_s1_7(tile,tile,tile,tile,tile,tile,T,S,V)
          t1 = wtime()
          timers(7,1) = t1-t0
          t0 = wtime()
          call omp_sd_t_s1_8(tile,tile,tile,tile,tile,tile,T,S,V)
          t1 = wtime()
          timers(8,1) = t1-t0
          t0 = wtime()
          call omp_sd_t_s1_9(tile,tile,tile,tile,tile,tile,T,S,V)
          t1 = wtime()
          timers(9,1) = t1-t0

          timers(10,1) = sum(timers(1:9,1))

          t0 = wtime()
          call omp_sd_t_d1_1(tile,tile,tile,tile,tile,tile,tile,T,D,V)
          t1 = wtime()
          timers(11,1) = t1-t0
          t0 = wtime()
          call omp_sd_t_d1_2(tile,tile,tile,tile,tile,tile,tile,T,D,V)
          t1 = wtime()
          timers(12,1) = t1-t0
          t0 = wtime()
          call omp_sd_t_d1_3(tile,tile,tile,tile,tile,tile,tile,T,D,V)
          t1 = wtime()
          timers(13,1) = t1-t0
          t0 = wtime()
          call omp_sd_t_d1_4(tile,tile,tile,tile,tile,tile,tile,T,D,V)
          t1 = wtime()
          timers(14,1) = t1-t0
          t0 = wtime()
          call omp_sd_t_d1_5(tile,tile,tile,tile,tile,tile,tile,T,D,V)
          t1 = wtime()
          timers(15,1) = t1-t0
          t0 = wtime()
          call omp_sd_t_d1_6(tile,tile,tile,tile,tile,tile,tile,T,D,V)
          t1 = wtime()
          timers(16,1) = t1-t0
          t0 = wtime()
          call omp_sd_t_d1_7(tile,tile,tile,tile,tile,tile,tile,T,D,V)
          t1 = wtime()
          timers(17,1) = t1-t0
          t0 = wtime()
          call omp_sd_t_d1_8(tile,tile,tile,tile,tile,tile,tile,T,D,V)
          t1 = wtime()
          timers(18,1) = t1-t0
          t0 = wtime()
          call omp_sd_t_d1_9(tile,tile,tile,tile,tile,tile,tile,T,D,V)
          t1 = wtime()
          timers(19,1) = t1-t0

          timers(20,1) = sum(timers(11:19,1))

          t0 = wtime()
          call omp_sd_t_d1_1(tile,tile,tile,tile,tile,tile,tile,T,D,V)
          t1 = wtime()
          timers(21,1) = t1-t0
          t0 = wtime()
          call omp_sd_t_d1_2(tile,tile,tile,tile,tile,tile,tile,T,D,V)
          t1 = wtime()
          timers(22,1) = t1-t0
          t0 = wtime()
          call omp_sd_t_d1_3(tile,tile,tile,tile,tile,tile,tile,T,D,V)
          t1 = wtime()
          timers(23,1) = t1-t0
          t0 = wtime()
          call omp_sd_t_d1_4(tile,tile,tile,tile,tile,tile,tile,T,D,V)
          t1 = wtime()
          timers(24,1) = t1-t0
          t0 = wtime()
          call omp_sd_t_d1_5(tile,tile,tile,tile,tile,tile,tile,T,D,V)
          t1 = wtime()
          timers(25,1) = t1-t0
          t0 = wtime()
          call omp_sd_t_d1_6(tile,tile,tile,tile,tile,tile,tile,T,D,V)
          t1 = wtime()
          timers(26,1) = t1-t0
          t0 = wtime()
          call omp_sd_t_d1_7(tile,tile,tile,tile,tile,tile,tile,T,D,V)
          t1 = wtime()
          timers(27,1) = t1-t0
          t0 = wtime()
          call omp_sd_t_d1_8(tile,tile,tile,tile,tile,tile,tile,T,D,V)
          t1 = wtime()
          timers(28,1) = t1-t0
          t0 = wtime()
          call omp_sd_t_d1_9(tile,tile,tile,tile,tile,tile,tile,T,D,V)
          t1 = wtime()
          timers(29,1) = t1-t0

          timers(30,1) = sum(timers(21:29,1))

        enddo

        do r=1,30
          write(6,'(i2,1x,e10.5,1x,e10.5,1x,e10.5,1x,e10.5)') &
     &          r,timers(r,1),timers(r,2),timers(r,3),timers(r,4)
        enddo


      end program perf
