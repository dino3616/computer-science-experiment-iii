# frozen_string_literal: true

print('> ')
input_num = gets.to_i
while input_num.negative? || input_num > 100
  puts('0 - 100 の整数を入力してください.')
  print('> ')
  input_num = gets.to_i
end

puts('Hello!') if input_num != 30
