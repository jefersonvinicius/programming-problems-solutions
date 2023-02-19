#!/bin/ruby

require 'json'
require 'stringio'

def beautifulTriplets(d, arr)
    sequencies = create_sequencies(arr, d: d)
    sequencies.size
end

def create_sequencies(arr, d:)
    result = []
    arr.each_with_index do |value_i, i| 
        arr[i + 1, arr.size].each_with_index do |value_j, j|
            next if value_j - value_i != d
            arr[i + j + 2, arr.size].each do |value_k|
                next if value_k - value_j != d
                result << [value_i, value_j, value_k]
            end
        end
    end
    result
end

fptr = File.open(ENV['OUTPUT_PATH'], 'w')
first_multiple_input = gets.rstrip.split
n = first_multiple_input[0].to_i
d = first_multiple_input[1].to_i
arr = gets.rstrip.split.map(&:to_i)
result = beautifulTriplets d, arr
fptr.write result
fptr.write "\n"
fptr.close()
