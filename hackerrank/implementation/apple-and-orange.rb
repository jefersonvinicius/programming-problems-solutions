#!/bin/ruby

require 'json'
require 'stringio'

class Solution 
    def initialize(start_sam_house, end_sam_house, apple_tree_location, orange_tree_location, apples_distances, oranges_distances)
        @start_sam_house = start_sam_house
        @end_sam_house = end_sam_house
        @apple_tree_location = apple_tree_location
        @orange_tree_location = orange_tree_location
        @fallen_apples_distances = apples_distances
        @fallen_oranges_distances = oranges_distances
    end

    def solve
        apples_positions = @fallen_apples_distances.map(&calc_distance(from_position: @apple_tree_location))
        oranges_positions = @fallen_oranges_distances.map(&calc_distance(from_position: @orange_tree_location))
        apples = apples_positions.select(&method(:within_sam_house?))
        oranges = oranges_positions.select(&method(:within_sam_house?))
        puts apples.length, oranges.length
    end

    private 

    def within_sam_house?(position)
        position >= @start_sam_house && position <= @end_sam_house
    end
    
    def calc_distance(from_position:)
        -> (distance) { from_position + distance }
    end
end

def countApplesAndOranges(start_sam_house, end_sam_house, apple_tree_location, orange_tree_location, apples_distances, oranges_distances)
    Solution.new(start_sam_house, end_sam_house, apple_tree_location, orange_tree_location, apples_distances, oranges_distances).solve
end

first_multiple_input = gets.rstrip.split
s = first_multiple_input[0].to_i
t = first_multiple_input[1].to_i
second_multiple_input = gets.rstrip.split
a = second_multiple_input[0].to_i
b = second_multiple_input[1].to_i
third_multiple_input = gets.rstrip.split
m = third_multiple_input[0].to_i
n = third_multiple_input[1].to_i
apples = gets.rstrip.split.map(&:to_i)
oranges = gets.rstrip.split.map(&:to_i)
countApplesAndOranges s, t, a, b, apples, oranges
