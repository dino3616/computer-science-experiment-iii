# frozen_string_literal: true

num = 0
while num >= 0 && num <= 100
  puts(num) if num.even? && num % 6 != 0

  num += 1
end
