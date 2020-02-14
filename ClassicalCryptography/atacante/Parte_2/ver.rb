a = ".LymZkEJDrZO-D?y\"AqKxIzMVpqXhzS.;JYcm-WKvMRZ\"adcMh-EiXKVZQUYcNhnEXfJVZCeJSItqXdiC\"hHMVfdmh TqF\"gCZlRz?DWKe!Oc.fYRai,DgeM\"lIecRXnhEWi "
i = 0
j = 0



for j in 0..a.length
	count = 0
	s = " " * j
	print(s)
	for i in 0..(a.length-j-1)
		print("#{a[i]}")
		if a[i+j+2] == a[i]
			count +=1
		end
	end
	
	print("|")
	print("#{count}")
	print("\n")
end