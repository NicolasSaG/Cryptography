require 'set'
f = File.new("alphabet.vig", "r")
f2 = File.new("menssage2.vig", "r")
f3 = File.new("MessageOne.txt.vig", "r")
f4 = File.new("MessageTwo.txt.vig", "r")


s1 = Set["a"];
s2 = Set["a"];
s3 = Set["a"];
s4 = Set["a"];

f.each_line do |line|
 	line.each_char do |c|
 		s1.add(c)
 	end
end

f2.each_line do |line|
 	line.each_char do |c|
 		s2.add(c)
 	end
end

f3.each_line do |line|
 	line.each_char do |c|
 		s3.add(c)
 	end
end

f4.each_line do |line|
 	line.each_char do |c|
 		s4.add(c)
 	end
end

puts("Alfabeto message1.vig: #{s1}")
puts("Alfabeto size: #{s1.length()}")
puts ("===================")
puts("Alfabeto message2.vig: #{s2}")
puts("Alfabeto size: #{s2.length()}")
puts ("===================")
puts("Alfabeto MessageOne.txt.vig: #{s3}")
puts("Alfabeto size: #{s3.length()}")
puts ("===================")
puts("Alfabeto MessageTwo.txt.vig: #{s4}")
puts("Alfabeto size: #{s4.length()}")

english = Set["a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"]
numeros = Set["1", "2", "3", "4", "5", "6", "7", "8", "9", "0"]
mayus = Set["B", "C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q", "R", "S", "T", "U","V", "W","X", "Y", "Z"]
others = Set[",","."," ","-", "_", "+", "*", "â","€","™", "\""]
others2 = Set["(", ")", "{", "}", "[","]"]

s5 = s1 - english
s5 = s5 - numeros
s5 = s5 - mayus
s5 = s5 - others
s5 = s5 - others2
puts ("===================")
puts("Alfabeto resta de s1 - ingles - numeros - mayus - others - others2: ")
puts("#{s5}")
puts("Alfabeto size: #{s5.length()}")

