# frozen_string_literal: true

def plus(a, b) # rubocop:disable Naming/MethodParameterName
  a.zip(b).map { |x, y| x + y }
end

print(plus([1, 2, 3, 4, 5, 6], [6, 5, 4, 3, 2, 1]), "\n")
