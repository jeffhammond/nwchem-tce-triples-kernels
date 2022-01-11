function nttk_sd_t_s1_1(h3d,h2d,h1d,p6d,p5d,p4d,triplesx,t1sub,v2sub)
      for p4 in 1:p4d
      for p5 in 1:p5d
      for p6 in 1:p6d
      for h1 in 1:h1d
      for h2 in 1:h2d
      for h3 in 1:h3d
       @inbounds triplesx[h3,h2,h1,p6,p5,p4] += t1sub(p4,h1] * v2sub[h3,h2,p6,p5]
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
       @inbounds triplesx[h3,h1,h2,p6,p5,p4] -= t1sub(p4,h1] * v2sub[h3,h2,p6,p5]
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
       @inbounds triplesx[h1,h3,h2,p6,p5,p4] += t1sub(p4,h1] * v2sub[h3,h2,p6,p5]
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
       @inbounds triplesx[h3,h2,h1,p6,p4,p5)-= t1sub(p4,h1] * v2sub[h3,h2,p6,p5]
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
       @inbounds triplesx[h3,h1,h2,p6,p4,p5] += t1sub(p4,h1] * v2sub[h3,h2,p6,p5]
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
       @inbounds triplesx[h1,h3,h2,p6,p4,p5)-= t1sub(p4,h1] * v2sub[h3,h2,p6,p5]
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
       @inbounds triplesx[h3,h2,h1,p4,p6,p5] += t1sub(p4,h1] * v2sub[h3,h2,p6,p5]
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
       @inbounds triplesx[h3,h1,h2,p4,p6,p5)-= t1sub(p4,h1] * v2sub[h3,h2,p6,p5]
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
       @inbounds triplesx[h1,h3,h2,p4,p6,p5] += t1sub(p4,h1] * v2sub[h3,h2,p6,p5]
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
       @inbounds triplesx[h3,h2,h1,p6,p5,p4)-=t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]
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
      endfor  
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
       @inbounds triplesx[h1,h3,h2,p6,p5,p4)-=t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]
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
       @inbounds triplesx[h3,h2,h1,p5,p4,p6)-=t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]
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
       @inbounds triplesx[h1,h3,h2,p5,p4,p6)-=t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]
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
       @inbounds triplesx[h3,h1,h2,p5,p6,p4)-=t2sub[h7,p4,p5,h1] * v2sub[h3,h2,p6,h7]
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
       @inbounds triplesx[h3,h2,h1,p6,p5,p4)-=t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]
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
       @inbounds triplesx[h2,h1,h3,p6,p5,p4)-=t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]
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
       @inbounds triplesx[h2,h3,h1,p6,p4,p5)-=t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]
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
       @inbounds triplesx[h3,h2,h1,p4,p6,p5)-=t2sub[p7,p4,h1,h2] * v2sub[p7,h3,p6,p5]
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
