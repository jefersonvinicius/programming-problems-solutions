#!/bin/bash

file=$1
in_qty=${2:-1}

g++ -o exec $file

for i in $(seq 1 $in_qty); do 
    ./exec < in$i.txt > ./tmp.txt
    result=`diff ./tmp.txt out$i.txt`
    if [[ $result != "" ]]; then
        echo "Difference found at in$i.txt"
        echo "Expected:"
        echo $(cat out$i.txt)
        echo 
        echo "But got:"
        echo $(cat tmp.txt)
        exit 1
    fi
done