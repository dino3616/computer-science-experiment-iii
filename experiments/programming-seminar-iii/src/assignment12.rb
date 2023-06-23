# frozen_string_literal: true

def max(x, y) # rubocop:disable Naming/MethodParameterName
  return x if x > y

  y
end

print('a = ')
a = gets.to_i

print('b = ')
b = gets.to_i

puts("bigger: #{max(a, b)}")
