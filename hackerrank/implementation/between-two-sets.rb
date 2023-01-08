#!/bin/ruby

require 'json'
require 'stringio'

def getTotalX(a, b)
    result = 0
    biggest = (a + b).max
    biggest.times do |n|
        n += 1
        if a.all? { |v| n % v == 0 } && b.all? { |v| v % n == 0 }
            result += 1
        end
    end
    result
end

fptr = File.open(ENV['OUTPUT_PATH'], 'w')
first_multiple_input = gets.rstrip.split
n = first_multiple_input[0].to_i
m = first_multiple_input[1].to_i
arr = gets.rstrip.split.map(&:to_i)
brr = gets.rstrip.split.map(&:to_i)
total = getTotalX arr, brr
fptr.write total
fptr.write "\n"
fptr.close()
