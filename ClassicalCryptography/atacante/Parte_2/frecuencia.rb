class LetterHistogram
  attr_accessor :text
  
  def initialize(t)
    @text = t
    @letters = { "a" => 0.08167, "b" => 0.01492, "c" => 0.0202, "d" => 0.04253,"e" => 0.12702, "f" => 0.0228,"g" => 0.02015, "h" => 0.06094,"i" => 0.06966, "j" => 0.0153,"k" => 0.01292, "l" => 0.04025,"m" => 0.02406, "n" => 0.06749,"o" => 0.07507, "p" => 0.01929,"q" => 0.0095, "r" => 0.05987,"s" => 0.06327, "t" => 0.09356,"u" => 0.02578, "v" => 0.00978,"w" => 0.0256, "x" => 0.0015,"y" => 0.01994, "z" => 0.00077 }
    @letters.default = 0
  end

  def display
    sum = 0
    i = 0
    arrayAux = Array.new
    calculate_frequencies.each { 
      |letter, freq| 
      s = letter.downcase
      arrayAux[i] = freq.to_f/@text.length;
      i += 1 
      #puts "#{letter}: #{freq.round(5)}, frecTotal: #{(freq.to_f/@text.length).round(5)} * frecLetra:#{@letters[s]} = #{((freq.to_f/@text.length)*@letters[s]).round(5)}" 
      sum += (freq.to_f/@text.length)*@letters[s]
    }
    for j in 0..i
      auxFrec = arrayAux[0]
      arrayAux.delete_at(0)
      arrayAux.push(auxFrec)
      
    end
    puts("total: #{@text.length} \t\t \t\t \t\t  \t\t\t\t\t\t\t\t sum: #{sum.round(5)}")
    #puts("#{arrayAux}")
  end

  private

  def calculate_frequencies
    freq = @text.each_char.with_object(Hash.new(0)) { |letter, freq| freq[letter] += 1 }
    freq.sort_by{ |letter, freq| freq }.reverse # mayor a menor frecuencia
  end
end

f = File.new("MessageTwo.txt.vig", "r")
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


puts("0")
senctence = LetterHistogram.new(k0)
senctence.display
puts("")
puts("1")
senctence = LetterHistogram.new(k1)
senctence.display
puts("")
puts("2")
senctence = LetterHistogram.new(k2)
senctence.display
puts("")
puts("3")
senctence = LetterHistogram.new(k3)
senctence.display
puts("")
puts("4")
senctence = LetterHistogram.new(k4)
senctence.display
puts("")
puts("5")
senctence = LetterHistogram.new(k5)
senctence.display
puts("")
puts("6")
senctence = LetterHistogram.new(k6)
senctence.display
puts("")
puts("7")
senctence = LetterHistogram.new(k7)
senctence.display
puts("")
puts("8")
senctence = LetterHistogram.new(k8)
senctence.display
puts("")
puts("9")
senctence = LetterHistogram.new(k9)
senctence.display
puts("")
puts("10")
senctence = LetterHistogram.new(k10)
senctence.display
puts("")
puts("11")
senctence = LetterHistogram.new(k11)
senctence.display
puts("")
puts("12")
senctence = LetterHistogram.new(k12)
senctence.display
puts("")

