# frozen_string_literal: true

def fact(x, r) # rubocop:disable Naming/MethodParameterName
  if x.zero?
    r
  else
    fact(x - 1, r * x)
  end
end

puts(fact(5, 1))
