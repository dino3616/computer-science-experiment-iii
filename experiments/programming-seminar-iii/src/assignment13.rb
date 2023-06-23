# frozen_string_literal: true

def max(arr)
  max = arr[0]
  arr.each { |x| max = x if x > max }

  max
end

arr = []
i = 0
while i < 4
  print('整数を入力してください: ')
  arr.push(gets.to_i)

  i += 1
end

puts("bigger: #{max(arr)}")
