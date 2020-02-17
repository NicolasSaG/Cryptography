f = File.new("MessageTwo.txt.vig", "r")
f2 =File.new("MessageTwo.txt", "r")
i = 0
k0 = ""
k1 = ""
k2 = ""
k3 = ""
k4 = ""
k5 = ""
k6 = ""
k7 = ""
k8 = ""
k9 = ""
k10 = ""
k11 = ""
k12 = ""

m0 = ""
m1 = ""
m2 = ""
m3 = ""
m4 = ""
m5 = ""
m6 = ""
m7 = ""
m8 = ""
m9 = ""
m10 = ""
m11 = ""
m12 = ""

f.each_line do |line|
  line.each_char do |c|
    i += 1
    if((i-1)%13 == 0)
      k0 += c
    elsif((i-1)%13 == 1)
      k1 += c
    elsif((i-1)%13 == 2)
      k2 += c
    elsif((i-1)%13 == 3)
      k3 += c
    elsif((i-1)%13 == 4)
      k4 += c
    elsif((i-1)%13 == 5)
      k5 += c
    elsif((i-1)%13 == 6)
      k6 += c
    elsif((i-1)%13 == 7)
      k7 += c
    elsif((i-1)%13 == 8)
      k8 += c
    elsif((i-1)%13 == 9)
      k9 += c
    elsif((i-1)%13 == 10)
      k10 += c 
    elsif((i-1)%13 == 11)
      k11 += c 
    elsif((i-1)%13 == 12)
      k12 += c    
    end
  end
end
i =0
f2.each_line do |line|
  line.each_char do |c|
    i += 1
    if((i-1)%13 == 0)
      m0 += c
    elsif((i-1)%13 == 1)
      m1 += c
    elsif((i-1)%13 == 2)
      m2 += c
    elsif((i-1)%13 == 3)
      m3 += c
    elsif((i-1)%13 == 4)
      m4 += c
    elsif((i-1)%13 == 5)
      m5 += c
    elsif((i-1)%13 == 6)
      m6 += c
    elsif((i-1)%13 == 7)
      m7 += c
    elsif((i-1)%13 == 8)
      m8 += c
    elsif((i-1)%13 == 9)
      m9 += c
    elsif((i-1)%13 == 10)
      m10 += c 
    elsif((i-1)%13 == 11)
      m11 += c 
    elsif((i-1)%13 == 12)
      m12 += c    
    end
  end
end


r0 = ""
r1 = ""
r2 = ""
r3 = ""
r4 = ""
r5 = ""
r6 = ""
r7 = ""
r8 = ""
r9 = ""
r0 = ""
r11 = ""
r12 = ""

x = k12.length
k12.split
m12.split

for j in 0..x-1
  m = k12[j]
  n = m12[j]
  #r0 += m + n
  puts m + n
  puts ""
  
  # r0 += auxi 
end

#puts r0
