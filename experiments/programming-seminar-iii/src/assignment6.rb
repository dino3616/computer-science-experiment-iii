# frozen_string_literal: true

print('降水確率を入力してください: ')
input_num = gets.to_i
while input_num.negative? || input_num > 100
  print('0 - 100 の整数を入力してください: ')
  input_num = gets.to_i
end

if input_num >= 50
  puts('傘を持って行ったほうがいいですね.')
elsif input_num < 50
  puts('傘を持たなくてもいいでしょう.')
end
