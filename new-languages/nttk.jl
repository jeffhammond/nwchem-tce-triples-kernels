#
# Copyright (c) 2022, NVIDIA
#

function nttk_sd_t_s1_1(h3d,h2d,h1d,p6d,p5d,p4d,triplesx,t1sub,v2sub)
 for p4 in 1:p4d
  for p5 in 1:p5d
   for p6 in 1:p6d
    for h1 in 1:h1d
     for h2 in 1:h2d
      for h3 in 1:h3d
       @inbounds triplesx[h3,h2,h1,p6,p5,p4] += t1sub[p4,h1] * v2sub[h3,h2,p6,p5]
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_s1_2(h3d,h2d,h1d,p6d,p5d,p4d,triplesx,t1sub,v2sub)
 for p4 in 1:p4d
  for p5 in 1:p5d
   for p6 in 1:p6d
    for h2 in 1:h2d
     for h1 in 1:h1d
      for h3 in 1:h3d
       @inbounds triplesx[h3,h1,h2,p6,p5,p4] -= t1sub[p4,h1] * v2sub[h3,h2,p6,p5]
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_s1_3(h3d,h2d,h1d,p6d,p5d,p4d,triplesx,t1sub,v2sub)
 for p4 in 1:p4d
  for p5 in 1:p5d
   for p6 in 1:p6d
    for h2 in 1:h2d
     for h3 in 1:h3d
      for h1 in 1:h1d
       @inbounds triplesx[h1,h3,h2,p6,p5,p4] += t1sub[p4,h1] * v2sub[h3,h2,p6,p5]
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_s1_4(h3d,h2d,h1d,p6d,p5d,p4d,triplesx,t1sub,v2sub)
 for p5 in 1:p5d
  for p4 in 1:p4d
   for p6 in 1:p6d
    for h1 in 1:h1d
     for h2 in 1:h2d
      for h3 in 1:h3d
       @inbounds triplesx[h3,h2,h1,p6,p4,p5] -=  t1sub[p4,h1] * v2sub[h3,h2,p6,p5]
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_s1_5(h3d,h2d,h1d,p6d,p5d,p4d,triplesx,t1sub,v2sub)
 for p5 in 1:p5d
  for p4 in 1:p4d
   for p6 in 1:p6d
    for h2 in 1:h2d
     for h1 in 1:h1d
      for h3 in 1:h3d
       @inbounds triplesx[h3,h1,h2,p6,p4,p5] += t1sub[p4,h1] * v2sub[h3,h2,p6,p5]
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_s1_6(h3d,h2d,h1d,p6d,p5d,p4d,triplesx,t1sub,v2sub)
 for p5 in 1:p5d
  for p4 in 1:p4d
   for p6 in 1:p6d
    for h2 in 1:h2d
     for h3 in 1:h3d
      for h1 in 1:h1d
       @inbounds triplesx[h1,h3,h2,p6,p4,p5] -=  t1sub[p4,h1] * v2sub[h3,h2,p6,p5]
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_s1_7(h3d,h2d,h1d,p6d,p5d,p4d,triplesx,t1sub,v2sub)
 for p5 in 1:p5d
  for p6 in 1:p6d
   for p4 in 1:p4d
    for h1 in 1:h1d
     for h2 in 1:h2d
      for h3 in 1:h3d
       @inbounds triplesx[h3,h2,h1,p4,p6,p5] += t1sub[p4,h1] * v2sub[h3,h2,p6,p5]
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_s1_8(h3d,h2d,h1d,p6d,p5d,p4d,triplesx,t1sub,v2sub)
 for p5 in 1:p5d
  for p6 in 1:p6d
   for p4 in 1:p4d
    for h2 in 1:h2d
     for h1 in 1:h1d
      for h3 in 1:h3d
       @inbounds triplesx[h3,h1,h2,p4,p6,p5] -=  t1sub[p4,h1] * v2sub[h3,h2,p6,p5]
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_s1_9(h3d,h2d,h1d,p6d,p5d,p4d,triplesx,t1sub,v2sub)
 for p5 in 1:p5d
  for p6 in 1:p6d
   for p4 in 1:p4d
    for h2 in 1:h2d
     for h3 in 1:h3d
      for h1 in 1:h1d
       @inbounds triplesx[h1,h3,h2,p4,p6,p5] += t1sub[p4,h1] * v2sub[h3,h2,p6,p5]
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_d1_1(h3d,h2d,h1d,p6d,p5d,p4d,h7d,triplesx,t2sub,v2sub)
 for p4 in 1:p4d
  for p5 in 1:p5d
   for p6 in 1:p6d
    for h1 in 1:h1d
     for h2 in 1:h2d
      for h3 in 1:h3d
       for h7 in 1:h7d
        @inbounds triplesx[h3,h2,h1,p6,p5,p4] -= t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]
       end
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_d1_2(h3d,h2d,h1d,p6d,p5d,p4d,h7d,triplesx,t2sub,v2sub)
 for p4 in 1:p4d
  for p5 in 1:p5d
   for p6 in 1:p6d
    for h2 in 1:h2d
     for h1 in 1:h1d
      for h3 in 1:h3d
       for h7 in 1:h7d
        @inbounds triplesx[h3,h1,h2,p6,p5,p4] += t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]
       end
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_d1_3(h3d,h2d,h1d,p6d,p5d,p4d,h7d,triplesx,t2sub,v2sub)
 for p4 in 1:p4d
  for p5 in 1:p5d
   for p6 in 1:p6d
    for h2 in 1:h2d
     for h3 in 1:h3d
      for h1 in 1:h1d
       for h7 in 1:h7d
        @inbounds triplesx[h1,h3,h2,p6,p5,p4] -= t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]
       end
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_d1_4(h3d,h2d,h1d,p6d,p5d,p4d,h7d,triplesx,t2sub,v2sub)
 for p6 in 1:p6d
  for p4 in 1:p4d
   for p5 in 1:p5d
    for h1 in 1:h1d
     for h2 in 1:h2d
      for h3 in 1:h3d
       for h7 in 1:h7d
        @inbounds triplesx[h3,h2,h1,p5,p4,p6] -= t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]
       end
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_d1_5(h3d,h2d,h1d,p6d,p5d,p4d,h7d,triplesx,t2sub,v2sub)
 for p6 in 1:p6d
  for p4 in 1:p4d
   for p5 in 1:p5d
    for h2 in 1:h2d
     for h1 in 1:h1d
      for h3 in 1:h3d
       for h7 in 1:h7d
        @inbounds triplesx[h3,h1,h2,p5,p4,p6] += t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]
       end
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_d1_6(h3d,h2d,h1d,p6d,p5d,p4d,h7d,triplesx,t2sub,v2sub)
 for p6 in 1:p6d
  for p4 in 1:p4d
   for p5 in 1:p5d
    for h2 in 1:h2d
     for h3 in 1:h3d
      for h1 in 1:h1d
       for h7 in 1:h7d
        @inbounds triplesx[h1,h3,h2,p5,p4,p6] -= t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]
       end
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_d1_7(h3d,h2d,h1d,p6d,p5d,p4d,h7d,triplesx,t2sub,v2sub)
 for p4 in 1:p4d
  for p6 in 1:p6d
   for p5 in 1:p5d
    for h1 in 1:h1d
     for h2 in 1:h2d
      for h3 in 1:h3d
       for h7 in 1:h7d
        @inbounds triplesx[h3,h2,h1,p5,p6,p4] += t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]
       end
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_d1_8(h3d,h2d,h1d,p6d,p5d,p4d,h7d,triplesx,t2sub,v2sub)
 for p4 in 1:p4d
  for p6 in 1:p6d
   for p5 in 1:p5d
    for h2 in 1:h2d
     for h1 in 1:h1d
      for h3 in 1:h3d
       for h7 in 1:h7d
        @inbounds triplesx[h3,h1,h2,p5,p6,p4] -= t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]
       end
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_d1_9(h3d,h2d,h1d,p6d,p5d,p4d,h7d,triplesx,t2sub,v2sub)
 for p4 in 1:p4d
  for p6 in 1:p6d
   for p5 in 1:p5d
    for h2 in 1:h2d
     for h3 in 1:h3d
      for h1 in 1:h1d
       for h7 in 1:h7d
        @inbounds triplesx[h1,h3,h2,p5,p6,p4] += t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]
       end
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_d2_1(h3d,h2d,h1d,p6d,p5d,p4d,p7d,triplesx,t2sub,v2sub)
 for p4 in 1:p4d
  for p5 in 1:p5d
   for p6 in 1:p6d
    for h1 in 1:h1d
     for h2 in 1:h2d
      for h3 in 1:h3d
       for p7 in 1:p7d
        @inbounds triplesx[h3,h2,h1,p6,p5,p4] -= t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]
       end
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_d2_2(h3d,h2d,h1d,p6d,p5d,p4d,p7d,triplesx,t2sub,v2sub)
 for p4 in 1:p4d
  for p5 in 1:p5d
   for p6 in 1:p6d
    for h3 in 1:h3d
     for h1 in 1:h1d
      for h2 in 1:h2d
       for p7 in 1:p7d
        @inbounds triplesx[h2,h1,h3,p6,p5,p4] -= t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]
       end
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_d2_3(h3d,h2d,h1d,p6d,p5d,p4d,p7d,triplesx,t2sub,v2sub)
 for p4 in 1:p4d
  for p5 in 1:p5d
   for p6 in 1:p6d
    for h1 in 1:h1d
     for h3 in 1:h3d
      for h2 in 1:h2d
       for p7 in 1:p7d
        @inbounds triplesx[h2,h3,h1,p6,p5,p4] += t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]
       end
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_d2_4(h3d,h2d,h1d,p6d,p5d,p4d,p7d,triplesx,t2sub,v2sub)
 for p5 in 1:p5d
  for p4 in 1:p4d
   for p6 in 1:p6d
    for h1 in 1:h1d
     for h2 in 1:h2d
      for h3 in 1:h3d
       for p7 in 1:p7d
        @inbounds triplesx[h3,h2,h1,p6,p4,p5] += t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]
       end
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_d2_5(h3d,h2d,h1d,p6d,p5d,p4d,p7d,triplesx,t2sub,v2sub)
 for p5 in 1:p5d
  for p4 in 1:p4d
   for p6 in 1:p6d
    for h3 in 1:h3d
     for h1 in 1:h1d
      for h2 in 1:h2d
       for p7 in 1:p7d
        @inbounds triplesx[h2,h1,h3,p6,p4,p5] += t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]
       end
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_d2_6(h3d,h2d,h1d,p6d,p5d,p4d,p7d,triplesx,t2sub,v2sub)
 for p5 in 1:p5d
  for p4 in 1:p4d
   for p6 in 1:p6d
    for h1 in 1:h1d
     for h3 in 1:h3d
      for h2 in 1:h2d
       for p7 in 1:p7d
        @inbounds triplesx[h2,h3,h1,p6,p4,p5] -= t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]
       end
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_d2_7(h3d,h2d,h1d,p6d,p5d,p4d,p7d,triplesx,t2sub,v2sub)
 for p5 in 1:p5d
  for p6 in 1:p6d
   for p4 in 1:p4d
    for h1 in 1:h1d
     for h2 in 1:h2d
      for h3 in 1:h3d
       for p7 in 1:p7d
        @inbounds triplesx[h3,h2,h1,p4,p6,p5] -= t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]
       end
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_d2_8(h3d,h2d,h1d,p6d,p5d,p4d,p7d,triplesx,t2sub,v2sub)
 for p5 in 1:p5d
  for p6 in 1:p6d
   for p4 in 1:p4d
    for h3 in 1:h3d
     for h1 in 1:h1d
      for h2 in 1:h2d
       for p7 in 1:p7d
        @inbounds triplesx[h2,h1,h3,p4,p6,p5] -= t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]
       end
      end
     end
    end
   end
  end
 end
end

function nttk_sd_t_d2_9(h3d,h2d,h1d,p6d,p5d,p4d,p7d,triplesx,t2sub,v2sub)
 for p5 in 1:p5d
  for p6 in 1:p6d
   for p4 in 1:p4d
    for h1 in 1:h1d
     for h3 in 1:h3d
      for h2 in 1:h2d
       for p7 in 1:p7d
        @inbounds triplesx[h2,h3,h1,p4,p6,p5] += t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]
       end
      end
     end
    end
   end
  end
 end
end

using Random

function main()
    println("NTTK Julia")

    reps     =  5
    tilesize = 16
    kernel   = -1

    tile6 = tilesize^6
    tile7 = tilesize^7

    argv = map(x->parse(Int32,x),ARGS)

    if length(ARGS) > 0
        tilesize = argv[1]
    end
    if length(ARGS) > 1
        kernel = argv[2]
    end

    println("testing NWChem CCSD(T) kernels with tilesize ", tilesize)

    tt0 = time_ns()
    t1  = rand(Float64,tilesize,tilesize)
    t2  = rand(Float64,tilesize,tilesize,tilesize,tilesize)
    v2  = rand(Float64,tilesize,tilesize,tilesize,tilesize)
    t3j = zeros(Float64,tilesize,tilesize,tilesize,tilesize,tilesize,tilesize)
    tt1 = time_ns()
    println("allocation and initialization time =",(tt1-tt0)*1e-9," seconds")

    tt0 = time_ns()
    precompile(nttk_sd_t_s1_1,(Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
    precompile(nttk_sd_t_s1_2,(Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
    precompile(nttk_sd_t_s1_3,(Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
    precompile(nttk_sd_t_s1_4,(Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
    precompile(nttk_sd_t_s1_5,(Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
    precompile(nttk_sd_t_s1_6,(Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
    precompile(nttk_sd_t_s1_7,(Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
    precompile(nttk_sd_t_s1_8,(Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
    precompile(nttk_sd_t_s1_9,(Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
    precompile(nttk_sd_t_d1_1,(Int32,Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
    precompile(nttk_sd_t_d1_2,(Int32,Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
    precompile(nttk_sd_t_d1_3,(Int32,Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
    precompile(nttk_sd_t_d1_4,(Int32,Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
    precompile(nttk_sd_t_d1_5,(Int32,Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
    precompile(nttk_sd_t_d1_6,(Int32,Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
    precompile(nttk_sd_t_d1_7,(Int32,Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
    precompile(nttk_sd_t_d1_8,(Int32,Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
    precompile(nttk_sd_t_d1_9,(Int32,Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
    precompile(nttk_sd_t_d2_1,(Int32,Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
    precompile(nttk_sd_t_d2_2,(Int32,Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
    precompile(nttk_sd_t_d2_3,(Int32,Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
    precompile(nttk_sd_t_d2_4,(Int32,Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
    precompile(nttk_sd_t_d2_5,(Int32,Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
    precompile(nttk_sd_t_d2_6,(Int32,Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
    precompile(nttk_sd_t_d2_7,(Int32,Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
    precompile(nttk_sd_t_d2_8,(Int32,Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
    precompile(nttk_sd_t_d2_9,(Int32,Int32,Int32,Int32,Int32,Int32,Int32,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
    tt1 = time_ns()
    println("precompile time =",(tt1-tt0)*1e-9," seconds")

    for i in 1:reps
        totalflops = 0
        ttt0 = time_ns()
        if (kernel<0 || kernel==1) 
            tt0 = time_ns()
            nttk_sd_t_s1_1(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_1", dt, (2e-9*tile6)/dt )
            totalflops += 2*tile6
        end
        if (kernel<0 || kernel==2) 
            tt0 = time_ns()
            nttk_sd_t_s1_2(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_2", dt, (2e-9*tile6)/dt )
            totalflops += 2*tile6
        end
        if (kernel<0 || kernel==3) 
            tt0 = time_ns()
            nttk_sd_t_s1_3(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_3", dt, (2e-9*tile6)/dt )
            totalflops += 2*tile6
        end
        if (kernel<0 || kernel==4) 
            tt0 = time_ns()
            nttk_sd_t_s1_4(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_4", dt, (2e-9*tile6)/dt )
            totalflops += 2*tile6
        end
        if (kernel<0 || kernel==5) 
            tt0 = time_ns()
            nttk_sd_t_s1_5(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_5", dt, (2e-9*tile6)/dt )
            totalflops += 2*tile6
        end
        if (kernel<0 || kernel==6) 
            tt0 = time_ns()
            nttk_sd_t_s1_6(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_6", dt, (2e-9*tile6)/dt )
            totalflops += 2*tile6
        end
        if (kernel<0 || kernel==7) 
            tt0 = time_ns()
            nttk_sd_t_s1_7(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_7", dt, (2e-9*tile6)/dt )
            totalflops += 2*tile6
        end
        if (kernel<0 || kernel==8) 
            tt0 = time_ns()
            nttk_sd_t_s1_8(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_8", dt, (2e-9*tile6)/dt )
            totalflops += 2*tile6
        end
        if (kernel<0 || kernel==9) 
            tt0 = time_ns()
            nttk_sd_t_s1_9(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_9", dt, (2e-9*tile6)/dt )
            totalflops += 2*tile6
        end
        if (kernel<0 || kernel==1) 
            tt0 = time_ns()
            nttk_sd_t_d1_1(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_1", dt, (2e-9*tile7)/dt )
            totalflops += 2*tile7
        end
        if (kernel<0 || kernel==2) 
            tt0 = time_ns()
            nttk_sd_t_d1_2(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_2", dt, (2e-9*tile7)/dt )
            totalflops += 2*tile7
        end
        if (kernel<0 || kernel==3) 
            tt0 = time_ns()
            nttk_sd_t_d1_3(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_3", dt, (2e-9*tile7)/dt )
            totalflops += 2*tile7
        end
        if (kernel<0 || kernel==4) 
            tt0 = time_ns()
            nttk_sd_t_d1_4(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_4", dt, (2e-9*tile7)/dt )
            totalflops += 2*tile7
        end
        if (kernel<0 || kernel==5) 
            tt0 = time_ns()
            nttk_sd_t_d1_5(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_5", dt, (2e-9*tile7)/dt )
            totalflops += 2*tile7
        end
        if (kernel<0 || kernel==6) 
            tt0 = time_ns()
            nttk_sd_t_d1_6(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_6", dt, (2e-9*tile7)/dt )
            totalflops += 2*tile7
        end
        if (kernel<0 || kernel==7) 
            tt0 = time_ns()
            nttk_sd_t_d1_7(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_7", dt, (2e-9*tile7)/dt )
            totalflops += 2*tile7
        end
        if (kernel<0 || kernel==8) 
            tt0 = time_ns()
            nttk_sd_t_d1_8(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_8", dt, (2e-9*tile7)/dt )
            totalflops += 2*tile7
        end
        if (kernel<0 || kernel==9) 
            tt0 = time_ns()
            nttk_sd_t_d1_9(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_9", dt, (2e-9*tile7)/dt )
            totalflops += 2*tile7
        end
        if (kernel<0 || kernel==1) 
            tt0 = time_ns()
            nttk_sd_t_d2_1(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_1", dt, (2e-9*tile7)/dt )
            totalflops += 2*tile7
        end
        if (kernel<0 || kernel==2) 
            tt0 = time_ns()
            nttk_sd_t_d2_2(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_2", dt, (2e-9*tile7)/dt )
            totalflops += 2*tile7
        end
        if (kernel<0 || kernel==3) 
            tt0 = time_ns()
            nttk_sd_t_d2_3(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_3", dt, (2e-9*tile7)/dt )
            totalflops += 2*tile7
        end
        if (kernel<0 || kernel==4) 
            tt0 = time_ns()
            nttk_sd_t_d2_4(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_4", dt, (2e-9*tile7)/dt )
            totalflops += 2*tile7
        end
        if (kernel<0 || kernel==5) 
            tt0 = time_ns()
            nttk_sd_t_d2_5(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_5", dt, (2e-9*tile7)/dt )
            totalflops += 2*tile7
        end
        if (kernel<0 || kernel==6) 
            tt0 = time_ns()
            nttk_sd_t_d2_6(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_6", dt, (2e-9*tile7)/dt )
            totalflops += 2*tile7
        end
        if (kernel<0 || kernel==7) 
            tt0 = time_ns()
            nttk_sd_t_d2_7(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_7", dt, (2e-9*tile7)/dt )
            totalflops += 2*tile7
        end
        if (kernel<0 || kernel==8) 
            tt0 = time_ns()
            nttk_sd_t_d2_8(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_8", dt, (2e-9*tile7)/dt )
            totalflops += 2*tile7
        end
        if (kernel<0 || kernel==9) 
            tt0 = time_ns()
            nttk_sd_t_d2_9(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3j, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            println("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_9", dt, (2e-9*tile7)/dt )
            totalflops += 2*tile7
        end
        ttt1 = time_ns()
        dt = ttt1-ttt0
        println("%d: %s time = %lf s GF/s = %lf \n", i, "total", dt, (1e-9*totalflops)/dt )
    end

    println("END")
end

main()
