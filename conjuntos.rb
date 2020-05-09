require 'set'

n = 431
s1 = Set.new()

for i in 1..(n-1)
	s1.add(i)
end


puts s1
resultados = Set.new()

for i in 1..n
	aux = Set.new()
	for j in 1..n
		aux.add(i**j % n)
	end
	if aux == s1
		resultados.add(i)
	end	
	puts "#{i}: #{aux}"
end

puts "generadores: "
puts resultados