# frozen_string_literal: true

print('りんごの価格: ')
apple = gets.to_i

printf('りんごの個数: ')
apple_count = gets.to_i

puts("りんごを #{apple_count} 個買うには、#{apple * apple_count} 円必要です.")
