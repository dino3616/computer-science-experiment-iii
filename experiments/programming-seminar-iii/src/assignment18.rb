# frozen_string_literal: true

def rev(arr)
  reversed = []
  arr.each { |x| reversed.unshift(x) }
end

print(rev(%w[りんご オレンジ 梨]), "\n")
