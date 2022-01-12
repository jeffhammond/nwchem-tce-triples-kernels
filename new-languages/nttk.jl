#!/usr/bin/env julia
#
# Copyright (c) 2022, NVIDIA
#

#using InteractiveUtils
#using BenchmarkTools

function diff6d(d1,d2,d3,d4,d5,d6,x,y)
 r = 0.0
 for i1 in 1:d1, i2 in 1:d2, i3 in 1:d3, i4 in 1:d4, i5 in 1:d5, i6 in 1:d6
     @inbounds r += abs( x[i1,i2,i3,i4,i5,i6] - y[i1,i2,i3,i4,i5,i6] )
 end
 return r
end

function nttk_sd_t_s1_1(h3d,h2d,h1d,p6d,p5d,p4d,triplesx,t1sub,v2sub)
 for p4 in 1:p4d, p5 in 1:p5d, p6 in 1:p6d, h1 in 1:h1d, h2 in 1:h2d, h3 in 1:h3d
     @inbounds triplesx[h3,h2,h1,p6,p5,p4] += t1sub[p4,h1] * v2sub[h3,h2,p6,p5]
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

using TensorOperations

function tensor_sd_t_s1_1(h3d,h2d,h1d,p6d,p5d,p4d,triplesx,t1sub,v2sub)
    @tensor triplesx[h3,h2,h1,p6,p5,p4] += t1sub[p4,h1] * v2sub[h3,h2,p6,p5]
end

function tensor_sd_t_s1_2(h3d,h2d,h1d,p6d,p5d,p4d,triplesx,t1sub,v2sub)
    @tensor triplesx[h3,h1,h2,p6,p5,p4] -= t1sub[p4,h1] * v2sub[h3,h2,p6,p5]
end

function tensor_sd_t_s1_3(h3d,h2d,h1d,p6d,p5d,p4d,triplesx,t1sub,v2sub)
    @tensor triplesx[h1,h3,h2,p6,p5,p4] += t1sub[p4,h1] * v2sub[h3,h2,p6,p5]
end

function tensor_sd_t_s1_4(h3d,h2d,h1d,p6d,p5d,p4d,triplesx,t1sub,v2sub)
    @tensor triplesx[h3,h2,h1,p6,p4,p5] -=  t1sub[p4,h1] * v2sub[h3,h2,p6,p5]
end

function tensor_sd_t_s1_5(h3d,h2d,h1d,p6d,p5d,p4d,triplesx,t1sub,v2sub)
    @tensor triplesx[h3,h1,h2,p6,p4,p5] += t1sub[p4,h1] * v2sub[h3,h2,p6,p5]
end

function tensor_sd_t_s1_6(h3d,h2d,h1d,p6d,p5d,p4d,triplesx,t1sub,v2sub)
    @tensor triplesx[h1,h3,h2,p6,p4,p5] -=  t1sub[p4,h1] * v2sub[h3,h2,p6,p5]
end

function tensor_sd_t_s1_7(h3d,h2d,h1d,p6d,p5d,p4d,triplesx,t1sub,v2sub)
    @tensor triplesx[h3,h2,h1,p4,p6,p5] += t1sub[p4,h1] * v2sub[h3,h2,p6,p5]
end

function tensor_sd_t_s1_8(h3d,h2d,h1d,p6d,p5d,p4d,triplesx,t1sub,v2sub)
    @tensor triplesx[h3,h1,h2,p4,p6,p5] -=  t1sub[p4,h1] * v2sub[h3,h2,p6,p5]
end

function tensor_sd_t_s1_9(h3d,h2d,h1d,p6d,p5d,p4d,triplesx,t1sub,v2sub)
    @tensor triplesx[h1,h3,h2,p4,p6,p5] += t1sub[p4,h1] * v2sub[h3,h2,p6,p5]
end

function tensor_sd_t_d1_1(h3d,h2d,h1d,p6d,p5d,p4d,h7d,triplesx,t2sub,v2sub)
    @tensor triplesx[h3,h2,h1,p6,p5,p4] -= t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]
end

function tensor_sd_t_d1_2(h3d,h2d,h1d,p6d,p5d,p4d,h7d,triplesx,t2sub,v2sub)
    @tensor triplesx[h3,h1,h2,p6,p5,p4] += t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]
end

function tensor_sd_t_d1_3(h3d,h2d,h1d,p6d,p5d,p4d,h7d,triplesx,t2sub,v2sub)
    @tensor triplesx[h1,h3,h2,p6,p5,p4] -= t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]
end

function tensor_sd_t_d1_4(h3d,h2d,h1d,p6d,p5d,p4d,h7d,triplesx,t2sub,v2sub)
    @tensor triplesx[h3,h2,h1,p5,p4,p6] -= t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]
end

function tensor_sd_t_d1_5(h3d,h2d,h1d,p6d,p5d,p4d,h7d,triplesx,t2sub,v2sub)
    @tensor triplesx[h3,h1,h2,p5,p4,p6] += t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]
end

function tensor_sd_t_d1_6(h3d,h2d,h1d,p6d,p5d,p4d,h7d,triplesx,t2sub,v2sub)
    @tensor triplesx[h1,h3,h2,p5,p4,p6] -= t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]
end

function tensor_sd_t_d1_7(h3d,h2d,h1d,p6d,p5d,p4d,h7d,triplesx,t2sub,v2sub)
    @tensor triplesx[h3,h2,h1,p5,p6,p4] += t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]
end

function tensor_sd_t_d1_8(h3d,h2d,h1d,p6d,p5d,p4d,h7d,triplesx,t2sub,v2sub)
    @tensor triplesx[h3,h1,h2,p5,p6,p4] -= t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]
end

function tensor_sd_t_d1_9(h3d,h2d,h1d,p6d,p5d,p4d,h7d,triplesx,t2sub,v2sub)
    @tensor triplesx[h1,h3,h2,p5,p6,p4] += t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]
end

function tensor_sd_t_d2_1(h3d,h2d,h1d,p6d,p5d,p4d,p7d,triplesx,t2sub,v2sub)
    @tensor triplesx[h3,h2,h1,p6,p5,p4] -= t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]
end

function tensor_sd_t_d2_2(h3d,h2d,h1d,p6d,p5d,p4d,p7d,triplesx,t2sub,v2sub)
    @tensor triplesx[h2,h1,h3,p6,p5,p4] -= t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]
end

function tensor_sd_t_d2_3(h3d,h2d,h1d,p6d,p5d,p4d,p7d,triplesx,t2sub,v2sub)
    @tensor triplesx[h2,h3,h1,p6,p5,p4] += t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]
end

function tensor_sd_t_d2_4(h3d,h2d,h1d,p6d,p5d,p4d,p7d,triplesx,t2sub,v2sub)
    @tensor triplesx[h3,h2,h1,p6,p4,p5] += t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]
end

function tensor_sd_t_d2_5(h3d,h2d,h1d,p6d,p5d,p4d,p7d,triplesx,t2sub,v2sub)
    @tensor triplesx[h2,h1,h3,p6,p4,p5] += t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]
end

function tensor_sd_t_d2_6(h3d,h2d,h1d,p6d,p5d,p4d,p7d,triplesx,t2sub,v2sub)
    @tensor triplesx[h2,h3,h1,p6,p4,p5] -= t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]
end

function tensor_sd_t_d2_7(h3d,h2d,h1d,p6d,p5d,p4d,p7d,triplesx,t2sub,v2sub)
    @tensor triplesx[h3,h2,h1,p4,p6,p5] -= t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]
end

function tensor_sd_t_d2_8(h3d,h2d,h1d,p6d,p5d,p4d,p7d,triplesx,t2sub,v2sub)
    @tensor triplesx[h2,h1,h3,p4,p6,p5] -= t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]
end

function tensor_sd_t_d2_9(h3d,h2d,h1d,p6d,p5d,p4d,p7d,triplesx,t2sub,v2sub)
    @tensor triplesx[h2,h3,h1,p4,p6,p5] += t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]
end

using Random
using Printf

function main()
    println("NTTK Julia")

    precomp  = true
    reps     =  3
    tilesize = 16
    kernel   = -1

    argv = map(x->parse(Int64,x),ARGS)

    if length(ARGS) > 0
        tilesize = argv[1]
    end
    if length(ARGS) > 1
        kernel = argv[2]
    end

    tile6 = tilesize^6
    tile7 = tilesize^7

    println("testing NWChem CCSD(T) kernels with tilesize ", tilesize)

    tt0 = time_ns()
    t1  = rand(Float64,tilesize,tilesize)
    t2  = rand(Float64,tilesize,tilesize,tilesize,tilesize)
    v2  = rand(Float64,tilesize,tilesize,tilesize,tilesize)
    tt1 = time_ns()
    println("allocation and initialization time =",(tt1-tt0)*1e-9," seconds")

    if precomp
        tt0 = time_ns()
        # loops
        precompile(nttk_sd_t_s1_1,(Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
        precompile(nttk_sd_t_s1_2,(Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
        precompile(nttk_sd_t_s1_3,(Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
        precompile(nttk_sd_t_s1_4,(Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
        precompile(nttk_sd_t_s1_5,(Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
        precompile(nttk_sd_t_s1_6,(Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
        precompile(nttk_sd_t_s1_7,(Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
        precompile(nttk_sd_t_s1_8,(Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
        precompile(nttk_sd_t_s1_9,(Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
        precompile(nttk_sd_t_d1_1,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(nttk_sd_t_d1_2,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(nttk_sd_t_d1_3,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(nttk_sd_t_d1_4,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(nttk_sd_t_d1_5,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(nttk_sd_t_d1_6,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(nttk_sd_t_d1_7,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(nttk_sd_t_d1_8,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(nttk_sd_t_d1_9,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(nttk_sd_t_d2_1,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(nttk_sd_t_d2_2,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(nttk_sd_t_d2_3,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(nttk_sd_t_d2_4,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(nttk_sd_t_d2_5,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(nttk_sd_t_d2_6,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(nttk_sd_t_d2_7,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(nttk_sd_t_d2_8,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(nttk_sd_t_d2_9,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        # tensor
        precompile(tensor_sd_t_s1_1,(Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
        precompile(tensor_sd_t_s1_2,(Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
        precompile(tensor_sd_t_s1_3,(Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
        precompile(tensor_sd_t_s1_4,(Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
        precompile(tensor_sd_t_s1_5,(Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
        precompile(tensor_sd_t_s1_6,(Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
        precompile(tensor_sd_t_s1_7,(Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
        precompile(tensor_sd_t_s1_8,(Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
        precompile(tensor_sd_t_s1_9,(Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,2},Array{Float64,4}))
        precompile(tensor_sd_t_d1_1,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(tensor_sd_t_d1_2,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(tensor_sd_t_d1_3,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(tensor_sd_t_d1_4,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(tensor_sd_t_d1_5,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(tensor_sd_t_d1_6,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(tensor_sd_t_d1_7,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(tensor_sd_t_d1_8,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(tensor_sd_t_d1_9,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(tensor_sd_t_d2_1,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(tensor_sd_t_d2_2,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(tensor_sd_t_d2_3,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(tensor_sd_t_d2_4,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(tensor_sd_t_d2_5,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(tensor_sd_t_d2_6,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(tensor_sd_t_d2_7,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(tensor_sd_t_d2_8,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        precompile(tensor_sd_t_d2_9,(Int64,Int64,Int64,Int64,Int64,Int64,Int64,Array{Float64,6},Array{Float64,4},Array{Float64,4}))
        tt1 = time_ns()
        println("precompile time =",(tt1-tt0)*1e-9," seconds")
    end

    # LOOPS
    @printf("\nSTARTING LOOPS KERNELS \n");
    t3l = zeros(Float64,tilesize,tilesize,tilesize,tilesize,tilesize,tilesize)
    for i in 1:reps
        totalflops = 0
        ttt0 = time_ns()
        if kernel<0 || kernel==1 
            tt0 = time_ns()
            nttk_sd_t_s1_1(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_1", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6
        end
        if kernel<0 || kernel==2 
            tt0 = time_ns()
            nttk_sd_t_s1_2(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_2", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6
        end
        if kernel<0 || kernel==3 
            tt0 = time_ns()
            nttk_sd_t_s1_3(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_3", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6
        end
        if kernel<0 || kernel==4 
            tt0 = time_ns()
            nttk_sd_t_s1_4(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_4", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6
        end
        if kernel<0 || kernel==5 
            tt0 = time_ns()
            nttk_sd_t_s1_5(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_5", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6
        end
        if kernel<0 || kernel==6 
            tt0 = time_ns()
            nttk_sd_t_s1_6(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_6", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6
        end
        if kernel<0 || kernel==7 
            tt0 = time_ns()
            nttk_sd_t_s1_7(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_7", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6
        end
        if kernel<0 || kernel==8 
            tt0 = time_ns()
            nttk_sd_t_s1_8(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_8", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6
        end
        if kernel<0 || kernel==9 
            tt0 = time_ns()
            nttk_sd_t_s1_9(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_9", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6
        end
        if kernel<0 || kernel==1 
            tt0 = time_ns()
            nttk_sd_t_d1_1(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_1", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==2 
            tt0 = time_ns()
            nttk_sd_t_d1_2(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_2", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==3 
            tt0 = time_ns()
            nttk_sd_t_d1_3(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_3", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==4 
            tt0 = time_ns()
            nttk_sd_t_d1_4(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_4", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==5 
            tt0 = time_ns()
            nttk_sd_t_d1_5(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_5", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==6 
            tt0 = time_ns()
            nttk_sd_t_d1_6(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_6", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==7 
            tt0 = time_ns()
            nttk_sd_t_d1_7(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_7", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==8 
            tt0 = time_ns()
            nttk_sd_t_d1_8(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_8", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==9 
            tt0 = time_ns()
            nttk_sd_t_d1_9(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_9", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==1 
            tt0 = time_ns()
            nttk_sd_t_d2_1(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_1", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==2 
            tt0 = time_ns()
            nttk_sd_t_d2_2(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_2", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==3 
            tt0 = time_ns()
            nttk_sd_t_d2_3(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_3", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==4 
            tt0 = time_ns()
            nttk_sd_t_d2_4(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_4", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==5 
            tt0 = time_ns()
            nttk_sd_t_d2_5(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_5", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==6 
            tt0 = time_ns()
            nttk_sd_t_d2_6(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_6", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==7 
            tt0 = time_ns()
            nttk_sd_t_d2_7(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_7", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==8 
            tt0 = time_ns()
            nttk_sd_t_d2_8(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_8", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==9 
            tt0 = time_ns()
            nttk_sd_t_d2_9(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_9", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        ttt1 = time_ns()
        dt = ttt1-ttt0
        @printf("%d: total time = %lf s GF/s = %lf\n",i,dt*1e-9,totalflops/dt)
    end

    # TENSOR
    @printf("\nSTARTING TENSOR KERNELS \n");
    t3t = zeros(Float64,tilesize,tilesize,tilesize,tilesize,tilesize,tilesize)
    for i in 1:reps
        totalflops = 0
        ttt0 = time_ns()
        if kernel<0 || kernel==1 
            tt0 = time_ns()
            tensor_sd_t_s1_1(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_1", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6
        end
        if kernel<0 || kernel==2 
            tt0 = time_ns()
            tensor_sd_t_s1_2(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_2", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6
        end
        if kernel<0 || kernel==3 
            tt0 = time_ns()
            tensor_sd_t_s1_3(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_3", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6
        end
        if kernel<0 || kernel==4 
            tt0 = time_ns()
            tensor_sd_t_s1_4(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_4", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6
        end
        if kernel<0 || kernel==5 
            tt0 = time_ns()
            tensor_sd_t_s1_5(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_5", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6
        end
        if kernel<0 || kernel==6 
            tt0 = time_ns()
            tensor_sd_t_s1_6(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_6", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6
        end
        if kernel<0 || kernel==7 
            tt0 = time_ns()
            tensor_sd_t_s1_7(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_7", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6
        end
        if kernel<0 || kernel==8 
            tt0 = time_ns()
            tensor_sd_t_s1_8(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_8", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6
        end
        if kernel<0 || kernel==9 
            tt0 = time_ns()
            tensor_sd_t_s1_9(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t1, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_s1_9", dt*1e-9, (2*tile6)/dt )
            totalflops += 2*tile6
        end
        if kernel<0 || kernel==1 
            tt0 = time_ns()
            tensor_sd_t_d1_1(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_1", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==2 
            tt0 = time_ns()
            tensor_sd_t_d1_2(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_2", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==3 
            tt0 = time_ns()
            tensor_sd_t_d1_3(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_3", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==4 
            tt0 = time_ns()
            tensor_sd_t_d1_4(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_4", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==5 
            tt0 = time_ns()
            tensor_sd_t_d1_5(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_5", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==6 
            tt0 = time_ns()
            tensor_sd_t_d1_6(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_6", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==7 
            tt0 = time_ns()
            tensor_sd_t_d1_7(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_7", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==8 
            tt0 = time_ns()
            tensor_sd_t_d1_8(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_8", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==9 
            tt0 = time_ns()
            tensor_sd_t_d1_9(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d1_9", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==1 
            tt0 = time_ns()
            tensor_sd_t_d2_1(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_1", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==2 
            tt0 = time_ns()
            tensor_sd_t_d2_2(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_2", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==3 
            tt0 = time_ns()
            tensor_sd_t_d2_3(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_3", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==4 
            tt0 = time_ns()
            tensor_sd_t_d2_4(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_4", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==5 
            tt0 = time_ns()
            tensor_sd_t_d2_5(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_5", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==6 
            tt0 = time_ns()
            tensor_sd_t_d2_6(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_6", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==7 
            tt0 = time_ns()
            tensor_sd_t_d2_7(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_7", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==8 
            tt0 = time_ns()
            tensor_sd_t_d2_8(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_8", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        if kernel<0 || kernel==9 
            tt0 = time_ns()
            tensor_sd_t_d2_9(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3t, t2, v2)
            tt1 = time_ns()
            dt = tt1-tt0
            @printf("%d: %s time = %lf s GF/s = %lf \n", i, "sd_t_d2_9", dt*1e-9, (2*tile7)/dt )
            totalflops += 2*tile7
        end
        ttt1 = time_ns()
        dt = ttt1-ttt0
        @printf("%d: total time = %lf s GF/s = %lf\n",i,dt*1e-9,totalflops/dt)
    end

    error = diff6d(tilesize, tilesize, tilesize, tilesize, tilesize, tilesize, t3l, t3t)
    println("diff = ",error)

    println("END")
end

main()
