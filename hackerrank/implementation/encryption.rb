#!/bin/ruby

require 'json'
require 'stringio'

def encryption(s)
    normalized = s.split(' ').join('')
    rows, columns = find_matrix_dimensions(normalized)
    matrix = build_matrix(normalized, columns)
    encrypt_matrix(matrix, dimensions: { columns: columns, rows: rows })
end

def find_matrix_dimensions(normalized)
    radix = Math.sqrt(normalized.length)
    rows, columns = radix.floor, radix.ceil
    while rows * columns < normalized.length
        if rows < columns
            rows += 1
        else
            columns += 1
        end
    end
    [rows, columns]
end

def build_matrix(text, columns)
    matrix = []
    col, row = 0, 0
    text.split('').each do |letter| 
        if matrix[row].nil?
            matrix[row] = []
        end
    
        matrix[row] << letter
        if col < columns - 1
            col += 1
        else
            row += 1
            col = 0
        end
    end
    matrix
end

def encrypt_matrix(matrix, dimensions:) 
    result = ""
    columns = dimensions[:columns]
    rows = dimensions[:rows]
    columns.times do |col|
        rows.times do |row|
            result += matrix[row].nil? ? '' : matrix[row][col] || '' 
        end
        result += " "
    end
    result
end

fptr = File.open(ENV['OUTPUT_PATH'], 'w')
s = gets.chomp
result = encryption s
fptr.write result
fptr.write "\n"
fptr.close()
