# frozen_string_literal: true

def fibonacci(num)
  return 0 if num.zero?
  return 1 if num == 1

  fibonacci(num - 1) + fibonacci(num - 2)
end

print('整数を入力してください: ')
input_num = gets.to_i
while input_num.negative?
  print('0以上の整数を入力してください: ')
  input_num = gets.to_i
end

(0..input_num).each do |i|
  print(fibonacci(i), ' ')
end
puts
