# frozen_string_literal: true

print('点数を入力してください: ')
score = gets.to_i

if score >= 0 && score < 60
  puts('不可')
elsif score >= 60 && score < 70
  puts('可')
elsif score >= 70 && score < 80
  puts('良')
elsif score >= 80 && score < 90
  puts('優')
elsif score >= 90 && score <= 100
  puts('特優')
else
  puts('不適切な点数です.')
end
